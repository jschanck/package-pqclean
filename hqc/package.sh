PYTHON=/usr/bin/python3

BASE=`dirname $0`
BASE=`cd ${BASE} && pwd`
cd ${BASE}

VERSION=$(cat ${BASE}/VERSION)
PACKAGER=$(git rev-parse HEAD)
ARCHIVE=hqc-submission_${VERSION}.zip

BUILD=${BASE}/build
BUILD_UPSTREAM=${BUILD}/upstream
BUILD_CRYPTO_KEM=${BUILD}/crypto_kem
BUILD_TEST=${BUILD}/test

SCRIPTS=${BASE}/scripts

function task {
  echo -e "[ ]" $1
}

function endtask {
  echo -e "\e[1A[x]"
}

function cleanup {
  rm -rf ${BUILD}
}
trap cleanup EXIT

if [ -e "${BUILD_CRYPTO_KEM}" ]
then
  read -p "${BUILD_CRYPTO_KEM} directory already exists. Delete it? " yn
  if [ "${yn:-n}" != "y" ]
  then
    exit -1
  fi
  rm -rf ${BUILD_CRYPTO_KEM} ${BUILD_TEST}
fi
mkdir -p ${BUILD_CRYPTO_KEM} ${BUILD_TEST}

if [ ! -f ${BASE}/${ARCHIVE} ]
then
  wget -P ${BASE} https://pqc-hqc.org/doc/${ARCHIVE}
fi

task "Unpacking ${ARCHIVE}"
unzip -qq -d ${BUILD_UPSTREAM} ${BASE}/${ARCHIVE}
endtask

task 'Applying patches to upstream source code'
( cd ${BUILD_UPSTREAM}

for X in ${BASE}/patches/*
do
  patch -s -p1 < ${X}
done
)
endtask

task 'Copying files'
for PARAM in {hqc,hqc-rmrs}-{128,192,256}
do
  mkdir -p ${BUILD_CRYPTO_KEM}/${PARAM}/{clean,avx2}
  cp -Lp ${BUILD_UPSTREAM}/Reference_Implementation/${PARAM}/src/*.{c,h} ${BUILD_CRYPTO_KEM}/${PARAM}/clean/
  cp -Lp ${BUILD_UPSTREAM}/Optimized_Implementation/${PARAM}/src/*.{c,h} ${BUILD_CRYPTO_KEM}/${PARAM}/avx2/
  rm -f ${BUILD_CRYPTO_KEM}/${PARAM}/{clean,avx2}/main_*
done
endtask

task 'Renaming hash, rng, and intrinsic includes'
for PARAM in {hqc,hqc-rmrs}-{128,192,256}
do
  sed -s -i 's/hash\.h/sha2.h/' ${BUILD_CRYPTO_KEM}/${PARAM}/{clean,avx2}/*.{c,h}
  sed -s -i 's/#include "rng\.h"/#include "nistseedexpander\.h"\n#include "randombytes\.h"/' ${BUILD_CRYPTO_KEM}/${PARAM}/{clean,avx2}/*.{c,h}
  sed -s -i 's/nmmintrin\.h/immintrin.h/' ${BUILD_CRYPTO_KEM}/${PARAM}/avx2/*.{c,h}
  sed -s -i 's/wmmintrin\.h/immintrin.h/' ${BUILD_CRYPTO_KEM}/${PARAM}/avx2/*.{c,h}
  sed -s -i 's/x86intrin\.h/immintrin.h/' ${BUILD_CRYPTO_KEM}/${PARAM}/avx2/*.{c,h}
done
endtask

task 'Removing ifdefs'
unifdef -m -UVERBOSE -UALIGNVECTORS -U__STDC_LIB_EXT1__ ${BUILD_CRYPTO_KEM}/*/*/*.{c,h}
endtask

task 'Checking include guards'
for PARAM in {hqc,hqc-rmrs}-{128,192,256}
do
  for IMPL in clean avx2
  do
    for F in ${BUILD_CRYPTO_KEM}/${PARAM}/${IMPL}/*.h
    do
      START=$(grep -n -m 1 '^#ifndef' ${F} | cut -d: -f1)
      [ x${START} == x ] && START=0
      if [ x${START} == x ]
      then
        DEF=$(echo ${F} | tr [:lower:] [:upper:] | tr '.' '_')
        GUARD="#ifndef ${DEF}\n#define ${DEF}\n"
        echo -n ${GUARD} | cat - ${F} > ${F}
      else
        PRELUDE=$(head -n $((${START}-1)) ${F})
        GUARD=$(tail -n+$((${START})) ${F} | head -n 2)
        REST=$(tail -n+$((${START}+2)) ${F})
        echo "${GUARD}\n${PRELUDE}\n${REST}" | sed 's/\\n/\n/g' > ${F}
      fi
    done
  done
done
endtask

task 'Sorting #includes'
for PARAM in {hqc,hqc-rmrs}-{128,192,256}
do
  for IMPL in clean avx2
  do
    for F in ${BUILD_CRYPTO_KEM}/${PARAM}/${IMPL}/*.h
    do
      START=$(grep -n -m 1 '^#include' ${F} | cut -d: -f1)
      if [ x${START} == x ]; then continue; fi
      GUARD=$(head -n $((${START}-1)) ${F})
      INCL1=$(grep '^#include \"' ${F} | sort -u)
      INCL2=$(grep '^#include <' ${F} | sort -u)
      REST=$(tail -n+$((${START}+1)) ${F} | sed '/^#include/d')
      echo "${GUARD}\n${INCL1}\n${INCL2}\n${REST}" | sed 's/\\n/\n/g' > ${F}
    done
    for F in ${BUILD_CRYPTO_KEM}/${PARAM}/${IMPL}/*.c
    do
      INCL1=$(grep '^#include \"' ${F} | sort -u)
      INCL2=$(grep '^#include <' ${F} | sort -u)
      REST=$(sed '/^#include/d' ${F})
      echo "${INCL1}\n${INCL2}\n${REST}" | sed 's/\\n/\n/g' > ${F}
    done
  done
done
endtask

MANIFEST=${BUILD_TEST}/duplicate_consistency
mkdir -p ${MANIFEST}
task "Preparing for duplicate consistency"
( cd ${MANIFEST}
for P1 in hqc-{,rmrs-}{128,192,256}
do
  for OUT in clean avx2
  do
    sha1sum ${BUILD_CRYPTO_KEM}/${P1}/${OUT}/*.{h,c} > ${P1}_${OUT}.xxx
  done
done
)
endtask

( cd ${MANIFEST}
for P1 in hqc-{,rmrs-}{128,192,256}
do
  for OUT in clean avx2
  do
    task "${P1}/${OUT} duplicate consistency"
    echo "\
consistency_checks:" > ${P1}_${OUT}.yml
    for P2 in hqc-{,rmrs-}{128,192,256}

    do
      for IN in clean avx2
      do
        if ([ "${P1}" == "${P2}" ] && [ "${IN}" == "${OUT}" ]) || [ "${P1}" \> "${P2}" ]; then continue; fi
        FIRST=1
        for HASH in $(cat ${P2}_${IN}.xxx | cut -d ' ' -f 1)
        do
          X=$(grep $HASH ${P1}_${OUT}.xxx | cut -d ' ' -f 3)
          if [ x${X} != 'x' ]
          then
            [ $FIRST == '1' ] && FIRST=0 &&
            echo "\
    - source:
        scheme: ${P2}
        implementation: ${IN}
      files:" >> ${P1}_${OUT}.yml
            [ -e ${BUILD_CRYPTO_KEM}/${P2}/${OUT}/$(basename $X) ] &&
            echo "\
      - $(basename $X)" >> ${P1}_${OUT}.yml
          fi
        done
      done
    done
    endtask
  done
done
)
rm -rf ${MANIFEST}/*.xxx

task 'Namespacing' 
# Insert hooks for namespacing. These will be removed later.
sed -i -s 's/^\(size_t\|int\|uint.._t\|uint8_t\|void\) \([^(]*\)(.*);/#define \2 CRYPTO_NAMESPACE(\2)\n&\n/' ${BUILD_CRYPTO_KEM}/*/*/*.h

for PARAM in {hqc,hqc-rmrs}-{128,192,256}
do
  for IMPL in clean avx2
  do
    ( cd ${BUILD_CRYPTO_KEM}/${PARAM}/${IMPL}
    NAMESPACE=$(echo PQCLEAN_${PARAM//-/}_${IMPL} | tr [:lower:] [:upper:])
    for X in $(grep CRYPTO_NAMESPACE *.{c,h} | cut -f2 -d' ' | sort -u); do
      sed -i -s "/\\b${X}\\b\.[ch]"'/!s/'"\\b${X}\\b/${NAMESPACE}_${X}/g" *.c *.h
    done
    sed -i -s '/CRYPTO_NAMESPACE/d' *.{c,h}
    sed -i -s "s/CRYPTO_/${NAMESPACE}_CRYPTO_/" *.h
    sed -i "s/API_H/${NAMESPACE}_API_H/" api.h
    )
  done
done
endtask

task 'Copying metadata'
# Makefiles and other metadata
for PARAM in {hqc,hqc-rmrs}-{128,192,256}
do
  ( cd ${BUILD_CRYPTO_KEM}/${PARAM}/

  echo "Public Domain" > clean/LICENSE
  cp -Lp clean/LICENSE avx2/LICENSE
  cp -Lp ${BASE}/meta/crypto_kem_${PARAM}_META.yml META.yml
  echo "\
principal-submitters:
  - Carlos Aguilar Melchor
  - Nicolas Aragon
  - Slim Bettaieb
  - Olivier Blazy
  - Jurjen Bos
  - Jean-Christophe Deneuville
  - Philippe Gaborit
  - Edoardo Persichetti
  - Jean-Marc Robert
  - Pascal Véron
  - Gilles Zémor
  - Loïc Bidoux
implementations:
    - name: clean
      version: ${ARCHIVE/.zip/} via https://github.com/jschanck/package-pqclean/tree/${PACKAGER:0:8}/hqc
    - name: avx2
      version: ${ARCHIVE/.zip/} via https://github.com/jschanck/package-pqclean/tree/${PACKAGER:0:8}/hqc
      supported_platforms:
          - architecture: x86_64
            operating_systems:
                - Linux
                - Darwin
            required_flags:
                - avx2
                - bmi1
                - pclmul" >> META.yml

  echo "\
# This Makefile can be used with GNU Make or BSD Make

LIB=lib${PARAM}_clean.a
HEADERS=$(basename -a clean/*.h | tr '\n' ' ')
OBJECTS=$(basename -a clean/*.c | sed 's/\.c/.o/' | tr '\n' ' ')

CFLAGS=-O3 -Wall -Wextra -Wpedantic -Wshadow -Wvla -Werror -Wredundant-decls -Wmissing-prototypes -std=c99 -I../../../common \$(EXTRAFLAGS)

all: \$(LIB)

%.o: %.c \$(HEADERS)
	\$(CC) \$(CFLAGS) -c -o \$@ $<

\$(LIB): \$(OBJECTS)
	\$(AR) -r \$@ \$(OBJECTS)

clean:
	\$(RM) \$(OBJECTS)
	\$(RM) \$(LIB)" > clean/Makefile

echo "\
# This Makefile can be used with Microsoft Visual Studio's nmake using the command:
#    nmake /f Makefile.Microsoft_nmake

LIBRARY=lib${PARAM}_clean.lib
OBJECTS=$(basename -a clean/*.c | sed 's/\.c/.obj/' | tr '\n' ' ')

CFLAGS=/nologo /O2 /I ..\..\..\common /W4 /WX

all: \$(LIBRARY)

# Make sure objects are recompiled if headers change.
\$(OBJECTS): *.h

\$(LIBRARY): \$(OBJECTS)
    LIB.EXE /NOLOGO /WX /OUT:\$@ \$**

clean:
    -DEL \$(OBJECTS)
    -DEL \$(LIBRARY)" > clean/Makefile.Microsoft_nmake

echo "\
# This Makefile can be used with GNU Make or BSD Make

LIB=lib${PARAM}_avx2.a
HEADERS=$(basename -a avx2/*.h | tr '\n' ' ')
OBJECTS=$(basename -a avx2/*.c | sed 's/\.c/.o/' | tr '\n' ' ')

CFLAGS=-O3 -mavx2 -mbmi -mpclmul -Wall -Wextra -Wshadow -Wpedantic -Wvla -Werror -Wredundant-decls -Wmissing-prototypes -std=c99 -I../../../common \$(EXTRAFLAGS)

all: \$(LIB)

%.o: %.s \$(HEADERS)
	\$(AS) -o \$@ $<

%.o: %.c \$(HEADERS)
	\$(CC) \$(CFLAGS) -c -o \$@ $<

\$(LIB): \$(OBJECTS)
	\$(AR) -r \$@ \$(OBJECTS)

clean:
	\$(RM) \$(OBJECTS)
	\$(RM) \$(LIB)" > avx2/Makefile

  )
done
endtask

task 'Styling'
sed -i -s 's/ ;/;/g' ${BUILD_CRYPTO_KEM}/*/*/*.{c,h}
astyle \
  --style=google \
  --indent=spaces \
  --indent-preproc-define \
  --indent-preproc-cond \
  --pad-oper \
  --pad-comma \
  --pad-header \
  --align-pointer=name \
  --add-braces \
  --convert-tabs \
  --mode=c \
  --suffix=none \
  ${BUILD_CRYPTO_KEM}/*/*/*.{c,h} >/dev/null
endtask

# Package
task "Packaging pqclean-hqc-$(date +"%Y%m%d").tar.gz"
tar czf ${BASE}/pqclean-hqc-$(date +"%Y%m%d").tar.gz -C ${BUILD} crypto_kem test
endtask
