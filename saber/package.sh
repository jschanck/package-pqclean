#!/bin/bash

VERSION=$(cat VERSION)
PACKAGER=$(git rev-parse HEAD)

BASE=`dirname $0`
BASE=`cd $BASE && pwd`
echo ${BASE}

ARCHIVE=${VERSION}.zip
BUILD=${BASE}/build
BUILD_CRYPTO_KEM=${BUILD}/crypto_kem
BUILD_UPSTREAM=${BUILD}/upstream
BUILD_TEST=${BUILD}/test

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
  wget -P ${BASE} https://github.com/KULeuven-COSIC/SABER/archive/${VERSION}.zip
fi

task "Unpacking ${ARCHIVE}"
unzip -qq -d ${BUILD} ${BASE}/${ARCHIVE}
mv ${BUILD}/SABER-${VERSION} ${BUILD_UPSTREAM}
endtask

task 'Applying patches to upstream source code'
( cd ${BUILD_UPSTREAM}

for X in ${BASE}/patches/*
do
  patch -s -p1 < ${X}
done
)
endtask

for PARAM in lightsaber saber firesaber; do
  mkdir -p ${BUILD_CRYPTO_KEM}/${PARAM}/avx2
  mkdir -p ${BUILD_CRYPTO_KEM}/${PARAM}/clean

  task "Copying Reference_Implementation_KEM"
  ( cd ${BUILD_UPSTREAM}/Reference_Implementation_KEM/
    cp -Lp api.h cbd.h pack_unpack.h poly.h poly_mul.h SABER_indcpa.h SABER_params.h verify.h ${BUILD_CRYPTO_KEM}/${PARAM}/clean/
    cp -Lp cbd.c kem.c pack_unpack.c poly.c poly_mul.c SABER_indcpa.c verify.c ${BUILD_CRYPTO_KEM}/${PARAM}/clean/ )
  endtask

  task "Copying AVX_Implementation_KEM"
  ( cd ${BUILD_UPSTREAM}/AVX_Implementation_KEM/
    cp -Lp api.h cbd.h kem.h pack_unpack.h poly.h SABER_indcpa.h SABER_params.h verify.h ${BUILD_CRYPTO_KEM}/${PARAM}/avx2/
    cp -Lp cbd.c kem.c pack_unpack.c poly.c poly_mul.c SABER_indcpa.c verify.c ${BUILD_CRYPTO_KEM}/${PARAM}/avx2/ )
  endtask

# Makefiles and other metadata
( cd ${BUILD_CRYPTO_KEM}/${PARAM}/
echo "Public Domain" > clean/LICENSE
cp clean/LICENSE avx2/LICENSE

echo "\
# This Makefile can be used with GNU Make or BSD Make

LIB=lib${PARAM}_clean.a
HEADERS=$(basename -a clean/*.h | tr '\n' ' ')
OBJECTS=$(basename -a clean/*.c | sed 's/\.c/.o/' | tr '\n' ' ')

CFLAGS=-O3 -Wall -Wextra -Wpedantic -Wvla -Werror -Wredundant-decls -Wmissing-prototypes -std=c99 -I../../../common \$(EXTRAFLAGS)

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

CFLAGS=-O3 -mavx2 -Wall -Wextra -Wpedantic -Wvla -Werror -Wredundant-decls -Wmissing-prototypes -std=c99 -I../../../common \$(EXTRAFLAGS)

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

echo "\
name: LightSaber
type: kem
claimed-nist-level: 1
claimed-security: IND-CCA2
length-public-key: 672
length-ciphertext: 736
length-secret-key: 1568
length-shared-secret: 32
nistkat-sha256: dc2233ae221cfabbb1db5ab1a76c93967d37de9f87a8092561f95ab28eff6061" \
> ${BUILD_CRYPTO_KEM}/lightsaber/META.yml

echo "\
name: Saber
type: kem
claimed-nist-level: 3
claimed-security: IND-CCA2
length-public-key: 992
length-ciphertext: 1088
length-secret-key: 2304
length-shared-secret: 32
nistkat-sha256: c9e2c16f41f162c607a1d5704107159e5e12713b9bb8c356b1d68b216e79096e" \
> ${BUILD_CRYPTO_KEM}/saber/META.yml

echo "\
name: FireSaber
type: kem
claimed-nist-level: 5
claimed-security: IND-CCA2
length-public-key: 1312
length-ciphertext: 1472
length-secret-key: 3040
length-shared-secret: 32
nistkat-sha256: 937d9b2e139112e13d4093a6afe715deff476e4d578208b9e8e1809de43835cd" \
> ${BUILD_CRYPTO_KEM}/firesaber/META.yml

echo "\
principal-submitters:
  - Jan-Pieter D'Anvers
  - Angshuman Karmakar
  - Sujoy Sinha Roy
  - Frederik Vercauteren
implementations:
    - name: clean
      version: https://github.com/KULeuven-COSIC/SABER/tree/${VERSION} via https://github.com/jschanck/package-pqclean/tree/${PACKAGER:0:8}/saber
    - name: avx2
      version: https://github.com/KULeuven-COSIC/SABER/tree/${VERSION} via https://github.com/jschanck/package-pqclean/tree/${PACKAGER:0:8}/saber
      supported_platforms:
          - architecture: x86_64
            operating_systems:
                - Linux
                - Darwin
            required_flags:
                - avx2" \
  | tee -a ${BUILD_CRYPTO_KEM}/*/META.yml >/dev/null

task 'Renaming rng include'
for PARAM in lightsaber saber firesaber
do
  sed -s -i 's/#include "rng\.h"/#include "randombytes\.h"/' ${BUILD_CRYPTO_KEM}/${PARAM}/{clean,avx2}/*.{c,h}
done
endtask

task 'Simplifying ifdefs'
sed -i -s 's/^#include"/#include "/' ${BUILD_CRYPTO_KEM}/*/*/*.{c,h}
sed -i -s 's/if SABER_TYPE == /if /' ${BUILD_CRYPTO_KEM}/*/avx2/api.h

unifdef -k -m -DSABER_L=2 -DSABER_MU=10 -DSABER_ET=3 -DLightSaber -USaber -UFireSaber -DSaber_type=1 ${BUILD_CRYPTO_KEM}/lightsaber/*/*.{c,h}
unifdef -k -m -DSABER_L=3 -DSABER_MU=8  -DSABER_ET=4 -ULightSaber -DSaber -UFireSaber -DSaber_type=2 ${BUILD_CRYPTO_KEM}/saber/*/*.{c,h}
unifdef -k -m -DSABER_L=4 -DSABER_MU=6  -DSABER_ET=6 -ULightSaber -USaber -DFireSaber -DSaber_type=3 ${BUILD_CRYPTO_KEM}/firesaber/*/*.{c,h}
endtask


MANIFEST=${BUILD_TEST}/duplicate_consistency
mkdir -p ${MANIFEST}
task "Preparing for duplicate consistency"
( cd ${MANIFEST}
for P1 in lightsaber saber firesaber
do
  for OUT in clean avx2
  do
    sha1sum ${BUILD_CRYPTO_KEM}/${P1}/${OUT}/*.{h,c} > ${P1}_${OUT}.xxx
  done
done
)
endtask

( cd ${MANIFEST}
for P1 in lightsaber saber firesaber
do
  for OUT in clean avx2
  do
    task "${P1}/${OUT} duplicate consistency"
    echo "\
consistency_checks:" > ${P1}_${OUT}.yml
    for P2 in lightsaber saber firesaber
    do
      for IN in clean avx2
      do
        if ([ "${P1}" == "${P2}" ] && [ "${IN}" == "${OUT}" ]) || \
           ([ "${P1}" == "firesaber" ] && [ "${P2}" == "lightsaber" ]) || \
           ([ "${P1}" == "firesaber" ] && [ "${P2}" == "saber" ]) || \
           ([ "${P1}" == "saber" ] && [ "${P2}" == "lightsaber" ]); then
          continue
        fi
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
sed -i -s 's/^\(int\|void\|uint8_t\) \([^(]*\)(.*);/#define \2 CRYPTO_NAMESPACE(\2)\n&\n/' ${BUILD_CRYPTO_KEM}/*/*/*.h

for PARAM in lightsaber saber firesaber
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

task 'Checking include guards'
for PARAM in lightsaber saber firesaber
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
for PARAM in lightsaber saber firesaber
do
  for IMPL in clean avx2
  do
    for F in ${BUILD_CRYPTO_KEM}/${PARAM}/${IMPL}/*.h
    do
      START=$(grep -n -m 1 '^#include' ${F} | cut -d: -f1)
      if [ x${START} == x ]; then continue; fi
      GUARD=$(head -n $((${START}-1)) ${F})
      INCL1=$(grep '^#include \"' ${F} | LC_ALL=C sort -u)
      INCL2=$(grep '^#include <' ${F} | LC_ALL=C sort -u)
      REST=$(tail -n+$((${START}+1)) ${F} | sed '/^#include/d')
      echo "${GUARD}\n${INCL1}\n${INCL2}\n${REST}" | sed 's/\\n/\n/g' > ${F}
    done
    for F in ${BUILD_CRYPTO_KEM}/${PARAM}/${IMPL}/*.c
    do
      INCL1=$(grep '^#include \"' ${F} | LC_ALL=C sort -u)
      INCL2=$(grep '^#include <' ${F} | LC_ALL=C sort -u)
      REST=$(sed '/^#include/d' ${F})
      echo "${INCL1}\n${INCL2}\n${REST}" | sed 's/\\n/\n/g' > ${F}
    done
  done
done
endtask

task "Styling"
# Apply PQClean formatting 
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
task "Packaging"
( cd ${BUILD}; tar czf ${BASE}/pqclean-saber-$(date +"%Y%m%d").tar.gz crypto_kem test )
endtask
