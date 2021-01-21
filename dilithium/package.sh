#!/bin/bash

VERSION=$(cat VERSION)
PACKAGER=$(git rev-parse HEAD)

BASE=`dirname $0`
BASE=`cd $BASE && pwd`
echo ${BASE}

ARCHIVE=${VERSION}.zip
BUILD=${BASE}/build
BUILD_CRYPTO_SIGN=${BUILD}/crypto_sign
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

if [ -e "${BUILD_CRYPTO_SIGN}" ]
then
  read -p "${BUILD_CRYPTO_SIGN} directory already exists. Delete it? " yn
  if [ "${yn:-n}" != "y" ]
  then
    exit -1
  fi
  rm -rf ${BUILD_CRYPTO_SIGN} ${BUILD_TEST}
fi
mkdir -p ${BUILD_CRYPTO_SIGN} ${BUILD_TEST}

if [ ! -f ${BASE}/${ARCHIVE} ]
then
  wget -P ${BASE} https://github.com/pq-crystals/dilithium/archive/${VERSION}.zip
fi

task "Unpacking ${ARCHIVE}"
unzip -qq -d ${BUILD} ${BASE}/${ARCHIVE}
mv ${BUILD}/dilithium-${VERSION} ${BUILD_UPSTREAM}
endtask

task 'Applying patches to upstream source code'
( cd ${BUILD_UPSTREAM}

for X in ${BASE}/patches/*
do
  patch -s -p1 < ${X}
done
)
endtask

for PARAM in dilithium{2,3,5}{,aes}
do
  mkdir -p ${BUILD_CRYPTO_SIGN}/${PARAM}/avx2
  mkdir -p ${BUILD_CRYPTO_SIGN}/${PARAM}/clean

  task "Copying upstream/ref to ${PARAM}/clean"
  ( cd ${BUILD_UPSTREAM}/ref/
    OUT=${BUILD_CRYPTO_SIGN}/${PARAM}/clean/
    cp -Lp ntt.c packing.c poly.c polyvec.c reduce.c rounding.c sign.c ${OUT}
    cp -Lp api.h ntt.h packing.h params.h poly.h polyvec.h reduce.h rounding.h sign.h symmetric.h ${OUT}
    [[ ${PARAM} =~ "aes" ]] && 
      cp -Lp aes256ctr.{c,h} symmetric-aes.c ${OUT} ||
      cp -Lp symmetric-shake.c ${OUT} )
  endtask

  task "Copying upstream/avx2 to ${PARAM}/avx2"
  ( cd ${BUILD_UPSTREAM}/avx2/
    OUT=${BUILD_CRYPTO_SIGN}/${PARAM}/avx2/
    cp -Lp consts.c packing.c poly.c polyvec.c rejsample.c rounding.c sign.c ${OUT}
    cp -Lp align.h api.h cdecl.h consts.h ntt.h packing.h params.h poly.h polyvec.h rejsample.h rounding.h sign.h symmetric.h ${OUT}
    cp -Lp shuffle.inc ${OUT}
    cp -Lp invntt.S ntt.S pointwise.S shuffle.S ${OUT}
    [[ ${PARAM} =~ "aes" ]] &&
      cp -Lp aes256ctr.{c,h} ${OUT} ||
      cp -Lp fips202x4.{c,h} f1600x4.S symmetric-shake.c ${OUT} )
  endtask

# Makefiles and other metadata
( cd ${BUILD_CRYPTO_SIGN}/${PARAM}/

  echo "\
Public Domain (https://creativecommons.org/share-your-work/public-domain/cc0/)

For Keccak and AES we are using public-domain
code from sources and by authors listed in
comments on top of the respective files." > clean/LICENSE

  cp clean/LICENSE avx2/LICENSE
  cp -Lp ${BASE}/meta/crypto_sign_${PARAM}_META.yml META.yml
  echo "\
implementations:
    - name: clean
      version: https://github.com/pq-crystals/dilithium/commit/${VERSION} via https://github.com/jschanck/package-pqclean/tree/${PACKAGER:0:8}/dilithium
    - name: avx2
      version: https://github.com/pq-crystals/dilithium/commit/${VERSION} via https://github.com/jschanck/package-pqclean/tree/${PACKAGER:0:8}/dilithium
      supported_platforms:
        - architecture: x86_64
          operating_systems:
              - Linux
              - Darwin
          required_flags:
              - aes
              - avx2
              - bmi1
              - popcnt" >> META.yml

  echo "\
# This Makefile can be used with GNU Make or BSD Make

LIB=lib${PARAM}_clean.a
HEADERS=$(basename -a clean/*.h | tr '\n' ' ')
OBJECTS=$(basename -a clean/*.c | sed 's/\.c/.o/' | tr '\n' ' ')

CFLAGS=-O3 -Wall -Wextra -Wpedantic -Werror -Wmissing-prototypes -Wredundant-decls -std=c99 -I../../../common \$(EXTRAFLAGS)

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

# Warning C4146 is raised when a unary minus operator is applied to an
# unsigned type; this has nonetheless been standard and portable for as
# long as there has been a C standard, and we need it for constant-time
# computations. Thus, we disable that spurious warning.
CFLAGS=/nologo /O2 /I ..\..\..\common /W4 /WX /wd4146

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
HEADERS=$(basename -a avx2/*.h | tr '\n' ' ') \
$(basename -a avx2/*.inc | tr '\n' ' ')
OBJECTS=$(basename -a avx2/*.c | sed 's/\.c/.o/' | tr '\n' ' ') \
$(basename -a avx2/*.S | sed 's/\.S/.o/' | tr '\n' ' ')" > avx2/Makefile

  if [[ ${PARAM} =~ "aes" ]] 
  then
    echo "\
CFLAGS=-mavx2 -maes -mbmi2 -mpopcnt -O3 -Wall -Wextra -Wpedantic -Werror \\
          -Wmissing-prototypes -Wredundant-decls -std=c99 \\
          -I../../../common \$(EXTRAFLAGS)

all: \$(LIB)

%.o: %.c \$(HEADERS)
	\$(CC) \$(CFLAGS) -c -o \$@ $<

%.o: %.S \$(HEADERS)
	\$(CC) \$(CFLAGS) -c -o \$@ $<

\$(LIB): \$(OBJECTS)
	\$(AR) -r \$@ \$(OBJECTS)

clean:
	\$(RM) \$(OBJECTS)
	\$(RM) \$(LIB)" >> avx2/Makefile

  else

    echo "\
KECCAK4XDIR=../../../common/keccak4x
KECCAK4XOBJ=KeccakP-1600-times4-SIMD256.o
KECCAK4X=\$(KECCAK4XDIR)/\$(KECCAK4XOBJ)

CFLAGS=-mavx2 -mbmi2 -mpopcnt -O3 -Wall -Wextra -Wpedantic -Werror \\
          -Wmissing-prototypes -Wredundant-decls \\
          -Wpointer-arith -Wshadow \\
          -std=c99 -I../../../common \$(EXTRAFLAGS)

all: \$(LIB)

%.o: %.c \$(HEADERS)
	\$(CC) \$(CFLAGS) -c -o \$@ $<

%.o: %.S \$(HEADERS)
	\$(CC) \$(CFLAGS) -c -o \$@ $<

\$(LIB): \$(OBJECTS) \$(KECCAK4X)
	\$(AR) -r \$@ \$(OBJECTS) \$(KECCAK4X)

\$(KECCAK4X):
	\$(MAKE) -C \$(KECCAK4XDIR) \$(KECCAK4XOBJ)

clean:
	\$(RM) \$(OBJECTS)
	\$(RM) \$(LIB)" >> avx2/Makefile
  fi
 )
done

task 'Simplifying ifdefs'

# unifdef does not like the #if [...] #else #error #endif construction
sed -i -s '/#error/d' ${BUILD_CRYPTO_SIGN}/dilithium*/avx2/polyvec.c
sed -i -s '/#error/d' ${BUILD_CRYPTO_SIGN}/dilithium*/avx2/sign.c

sed -i -s 's/#\(.*\) GAMMA1 == (1 << 17)/#\1 1/' ${BUILD_CRYPTO_SIGN}/dilithium2*/*/{poly.c,rounding.c,params.h}
sed -i -s 's/#\(.*\) GAMMA1 == (1 << 19)/#\1 0/' ${BUILD_CRYPTO_SIGN}/dilithium2*/*/{poly.c,rounding.c,params.h}
sed -i -s 's/#\(.*\) GAMMA2 == (Q-1).88/#\1 1/' ${BUILD_CRYPTO_SIGN}/dilithium2*/*/{poly.c,rounding.c,params.h}
sed -i -s 's/#\(.*\) GAMMA2 == (Q-1).32/#\1 0/' ${BUILD_CRYPTO_SIGN}/dilithium2*/*/{poly.c,rounding.c,params.h}

sed -i -s 's/#\(.*\) GAMMA1 == (1 << 17)/#\1 0/' ${BUILD_CRYPTO_SIGN}/dilithium{3,5}*/*/{poly.c,rounding.c,params.h}
sed -i -s 's/#\(.*\) GAMMA1 == (1 << 19)/#\1 1/' ${BUILD_CRYPTO_SIGN}/dilithium{3,5}*/*/{poly.c,rounding.c,params.h}
sed -i -s 's/#\(.*\) GAMMA2 == (Q-1).88/#\1 0/' ${BUILD_CRYPTO_SIGN}/dilithium{3,5}*/*/{poly.c,rounding.c,params.h}
sed -i -s 's/#\(.*\) GAMMA2 == (Q-1).32/#\1 1/' ${BUILD_CRYPTO_SIGN}/dilithium{3,5}*/*/{poly.c,rounding.c,params.h}

unifdef -k -m -DDILITHIUM_MODE=2 -DD=13 -DK=4 -DL=4 -DETA=2 -UDILITHIUM_USE_AES -UDILITHIUM_RANDOMIZED_SIGNING -UDBENCH -U__ASSEMBLER__ ${BUILD_CRYPTO_SIGN}/dilithium2/*/*.{c,h,S}
unifdef -k -m -DDILITHIUM_MODE=3 -DD=13 -DK=6 -DL=5 -DETA=4 -UDILITHIUM_USE_AES -UDILITHIUM_RANDOMIZED_SIGNING -UDBENCH -U__ASSEMBLER__ ${BUILD_CRYPTO_SIGN}/dilithium3/*/*.{c,h,S}
unifdef -k -m -DDILITHIUM_MODE=5 -DD=13 -DK=8 -DL=7 -DETA=2 -UDILITHIUM_USE_AES -UDILITHIUM_RANDOMIZED_SIGNING -UDBENCH -U__ASSEMBLER__ ${BUILD_CRYPTO_SIGN}/dilithium5/*/*.{c,h,S}

unifdef -k -m -DDILITHIUM_MODE=2 -DD=13 -DK=4 -DL=4 -DETA=2 -DDILITHIUM_USE_AES -UDILITHIUM_RANDOMIZED_SIGNING -UDBENCH -U__ASSEMBLER__ ${BUILD_CRYPTO_SIGN}/dilithium2aes/*/*.{c,h,S}
unifdef -k -m -DDILITHIUM_MODE=3 -DD=13 -DK=6 -DL=5 -DETA=4 -DDILITHIUM_USE_AES -UDILITHIUM_RANDOMIZED_SIGNING -UDBENCH -U__ASSEMBLER__ ${BUILD_CRYPTO_SIGN}/dilithium3aes/*/*.{c,h,S}
unifdef -k -m -DDILITHIUM_MODE=5 -DD=13 -DK=8 -DL=7 -DETA=2 -DDILITHIUM_USE_AES -UDILITHIUM_RANDOMIZED_SIGNING -UDBENCH -U__ASSEMBLER__ ${BUILD_CRYPTO_SIGN}/dilithium5aes/*/*.{c,h,S}
endtask


MANIFEST=${BUILD_TEST}/duplicate_consistency
mkdir -p ${MANIFEST}
task "Preparing for duplicate consistency"
( cd ${MANIFEST}
for P1 in dilithium{2,3,5}{,aes}
do
  for OUT in clean avx2
  do
    sha1sum ${BUILD_CRYPTO_SIGN}/${P1}/${OUT}/*.{h,c} > ${P1}_${OUT}.xxx
  done
done
)
endtask

( cd ${MANIFEST}
for P1 in dilithium{2,3,5}{,aes}
do
  for OUT in clean avx2
  do
    task "${P1}/${OUT} duplicate consistency"
    echo "\
consistency_checks:" > ${P1}_${OUT}.yml
    for P2 in dilithium{2,3,5}{,aes}
    do
      for IN in clean avx2
      do
        if ([ "${P1}" == "${P2}" ] && [ "${IN}" == "${OUT}" ])
        then
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
            [ -e ${BUILD_CRYPTO_SIGN}/${P2}/${OUT}/$(basename $X) ] &&
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

for PARAM in dilithium{2,3,5}{,aes}
do
  for IMPL in clean avx2
  do
    ( cd ${BUILD_CRYPTO_SIGN}/${PARAM}/${IMPL}
    sed -i -s "s/AES256CTR_NAMESPACE/DILITHIUM_NAMESPACE/g" *.c *.h
    sed -i -s "s/FIPS202X4_NAMESPACE/DILITHIUM_NAMESPACE/g" *.c *.h

    NAMESPACE=$(echo PQCLEAN_${PARAM//-/}_${IMPL} | tr [:lower:] [:upper:])
    for X in $(grep DILITHIUM_NAMESPACE *.{c,h} | cut -f2 -d' ' | sort -u); do
      sed -i -s "/\\b${X}\\b\.[ch]"'/!s/'"\\b${X}\\b/${NAMESPACE}_${X}/g" *.c *.h
    done
    sed -i -s "s/, & PQCLEAN/, \&PQCLEAN/g" poly.c
    sed -i -s '/DILITHIUM_NAMESPACE/d' *.{c,h}
    sed -i -s "s/CRYPTO_/${NAMESPACE}_CRYPTO_/g" *.{c,h}
    sed -i "s/API_H/${NAMESPACE}_API_H/" api.h
    [ "${IMPL}" == "avx2" ] && sed -i -s "s/cdecl(\(.*\))/cdecl(${NAMESPACE}_\1)/" *.S
    )
  done
done
endtask

task 'Checking include guards'
for PARAM in dilithium{2,3,5}{,aes}
do
  for IMPL in clean avx2
  do
    NAMESPACE=$(echo PQCLEAN_${PARAM//-/}_${IMPL} | tr [:lower:] [:upper:])

    FILES=(${BUILD_CRYPTO_SIGN}/${PARAM}/${IMPL}/*.h)

    for F in ${FILES[@]}
    do
      DEF=${NAMESPACE}_$(basename ${F//-/_} | tr [:lower:] [:upper:] | tr '.' '_')
      GUARD="#ifndef ${DEF}\n#define ${DEF}\n"
      START=$(grep -n -m 1 '^#ifndef' ${F} | cut -d: -f1)
      if [ x${START} == x ]
      then
        REST=$(cat ${F})
        echo "${GUARD}\n${REST}\n#endif" | sed 's/\\n/\n/g' > ${F}
      else
        PRELUDE=$(head -n $((${START}-1)) ${F})
        REST=$(tail -n+$((${START}+2)) ${F})
        echo "${GUARD}\n${PRELUDE}\n${REST}" | sed 's/\\n/\n/g' > ${F}
      fi
    done
  done
done
endtask

task 'Sorting #includes'
for PARAM in dilithium{2,3,5}{,aes}
do
  for IMPL in clean avx2
  do
    for F in ${BUILD_CRYPTO_SIGN}/${PARAM}/${IMPL}/*.h
    do
      START=$(grep -n -m 1 '^#include' ${F} | cut -d: -f1)
      if [ x${START} == x ]; then continue; fi
      GUARD=$(head -n $((${START}-1)) ${F})
      INCL1=$(grep '^#include \"' ${F} | LC_ALL=C sort -u)
      INCL2=$(grep '^#include <' ${F} | LC_ALL=C sort -u)
      REST=$(tail -n+$((${START}+1)) ${F} | sed '/^#include/d')
      echo "${GUARD}\n${INCL1}\n${INCL2}\n${REST}" | sed 's/\\n/\n/g' > ${F}
    done
    for F in ${BUILD_CRYPTO_SIGN}/${PARAM}/${IMPL}/*.c
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
  ${BUILD_CRYPTO_SIGN}/*/*/*.{c,h} >/dev/null
endtask

# Package
task "Packaging"
( cd ${BUILD}; tar czf ${BASE}/pqclean-dilithium-$(date +"%Y%m%d").tar.gz crypto_sign test )
endtask
