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
  wget -P ${BASE} https://github.com/pq-crystals/kyber/archive/${VERSION}.zip
fi

task "Unpacking ${ARCHIVE}"
unzip -qq -d ${BUILD} ${BASE}/${ARCHIVE}
mv ${BUILD}/kyber-${VERSION} ${BUILD_UPSTREAM}
endtask

task 'Applying patches to upstream source code'
( cd ${BUILD_UPSTREAM}

for X in ${BASE}/patches/*
do
  patch -s -p1 < ${X}
done
)
endtask

for PARAM in kyber{512,768,1024}{,-90s}
do
  mkdir -p ${BUILD_CRYPTO_KEM}/${PARAM}/avx2
  mkdir -p ${BUILD_CRYPTO_KEM}/${PARAM}/clean

  task "Copying upstream/ref to ${PARAM}/clean"
  ( cd ${BUILD_UPSTREAM}/ref/
    OUT=${BUILD_CRYPTO_KEM}/${PARAM}/clean/
    cp -Lp cbd.c indcpa.c kem.c ntt.c poly.c polyvec.c reduce.c verify.c ${OUT}
    cp -Lp api.h cbd.h indcpa.h kem.h ntt.h params.h poly.h polyvec.h reduce.h symmetric.h verify.h ${OUT}
    [[ ${PARAM} =~ "90s" ]] && 
      cp -Lp symmetric-aes.c aes256ctr.c aes256ctr.h ${OUT} ||
      cp -Lp symmetric-shake.c ${OUT} )
  endtask

  task "Copying upstream/avx2 to ${PARAM}/avx2"
  ( cd ${BUILD_UPSTREAM}/avx2/
    OUT=${BUILD_CRYPTO_KEM}/${PARAM}/avx2/
    cp -Lp cbd.c consts.c fq.inc indcpa.c kem.c poly.c polyvec.c rejsample.c shuffle.inc verify.c ${OUT}
    cp -Lp align.h api.h cbd.h cdecl.h consts.h indcpa.h kem.h ntt.h params.h poly.h polyvec.h reduce.h rejsample.h symmetric.h verify.h ${OUT}
    cp -Lp fq.inc shuffle.inc ${OUT}
    cp -Lp basemul.S fq.S invntt.S ntt.S shuffle.S ${OUT}
    [[ ${PARAM} =~ "90s" ]] &&
      cp -Lp aes256ctr.{c,h} ${OUT} ||
      cp -Lp fips202x4.{c,h} symmetric-shake.c ${OUT} )
  endtask

# Makefiles and other metadata
( cd ${BUILD_CRYPTO_KEM}/${PARAM}/

  echo "\
Public Domain (https://creativecommons.org/share-your-work/public-domain/cc0/)

For Keccak and AES we are using public-domain
code from sources and by authors listed in
comments on top of the respective files." > clean/LICENSE

  cp clean/LICENSE avx2/LICENSE
  cp -Lp ${BASE}/meta/crypto_kem_${PARAM}_META.yml META.yml
  echo "\
implementations:
    - name: clean
      version: https://github.com/pq-crystals/kyber/commit/${VERSION} via https://github.com/jschanck/package-pqclean/tree/${PACKAGER:0:8}/kyber
    - name: avx2
      version: https://github.com/pq-crystals/kyber/commit/${VERSION} via https://github.com/jschanck/package-pqclean/tree/${PACKAGER:0:8}/kyber
      supported_platforms:
        - architecture: x86_64
          operating_systems:
              - Linux
              - Darwin
          required_flags:
              - aes
              - avx2
              - bmi2
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

  if [[ ${PARAM} =~ "90s" ]] 
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

for PARAM in kyber{512,768}{,-90s}
do
  sed -i -s 's/KYBER_POLYVECCOMPRESSEDBYTES == (KYBER_K \* 352)/0/' ${BUILD_CRYPTO_KEM}/${PARAM}/{avx2,clean}/polyvec.c
  sed -i -s 's/KYBER_POLYVECCOMPRESSEDBYTES == (KYBER_K \* 320)/1/' ${BUILD_CRYPTO_KEM}/${PARAM}/{avx2,clean}/polyvec.c
done

for PARAM in kyber1024{,-90s}
do
  sed -i -s 's/KYBER_POLYVECCOMPRESSEDBYTES == (KYBER_K \* 352)/1/' ${BUILD_CRYPTO_KEM}/${PARAM}/{avx2,clean}/polyvec.c
  sed -i -s 's/KYBER_POLYVECCOMPRESSEDBYTES == (KYBER_K \* 320)/0/' ${BUILD_CRYPTO_KEM}/${PARAM}/{avx2,clean}/polyvec.c
done

unifdef -k -m -DKYBER_K=2 -DKYBER_ETA1=3 -DKYBER_ETA2=2 -DKYBER_POLYCOMPRESSEDBYTES=128 -DKYBER_SSBYTES=32 -DKYBER_INDCPA_MSGBYTES=32 -DKYBER_90S ${BUILD_CRYPTO_KEM}/kyber512-90s/*/*.{c,h,S}
unifdef -k -m -DKYBER_K=2 -DKYBER_ETA1=3 -DKYBER_ETA2=2 -DKYBER_POLYCOMPRESSEDBYTES=128 -DKYBER_SSBYTES=32 -DKYBER_INDCPA_MSGBYTES=32 -UKYBER_90S ${BUILD_CRYPTO_KEM}/kyber512/*/*.{c,h,S}

unifdef -k -m -DKYBER_K=3 -DKYBER_ETA1=2 -DKYBER_ETA2=2 -DKYBER_POLYCOMPRESSEDBYTES=128 -DKYBER_SSBYTES=32 -DKYBER_INDCPA_MSGBYTES=32 -DKYBER_90S ${BUILD_CRYPTO_KEM}/kyber768-90s/*/*.{c,h,S}
unifdef -k -m -DKYBER_K=3 -DKYBER_ETA1=2 -DKYBER_ETA2=2 -DKYBER_POLYCOMPRESSEDBYTES=128 -DKYBER_SSBYTES=32 -DKYBER_INDCPA_MSGBYTES=32 -UKYBER_90S ${BUILD_CRYPTO_KEM}/kyber768/*/*.{c,h,S}

unifdef -k -m -DKYBER_K=4 -DKYBER_ETA1=2 -DKYBER_ETA2=2 -DKYBER_POLYCOMPRESSEDBYTES=160 -DKYBER_SSBYTES=32 -DKYBER_INDCPA_MSGBYTES=32 -DKYBER_90S ${BUILD_CRYPTO_KEM}/kyber1024-90s/*/*.{c,h,S}
unifdef -k -m -DKYBER_K=4 -DKYBER_ETA1=2 -DKYBER_ETA2=2 -DKYBER_POLYCOMPRESSEDBYTES=160 -DKYBER_SSBYTES=32 -DKYBER_INDCPA_MSGBYTES=32 -UKYBER_90S ${BUILD_CRYPTO_KEM}/kyber1024/*/*.{c,h,S}

unifdef -k -m -DBMI ${BUILD_CRYPTO_KEM}/kyber*/avx2/*.{c,h,S}
endtask


MANIFEST=${BUILD_TEST}/duplicate_consistency
mkdir -p ${MANIFEST}
task "Preparing for duplicate consistency"
( cd ${MANIFEST}
for P1 in kyber{512,768,1024}{,-90s}
do
  for OUT in clean avx2
  do
    sha1sum ${BUILD_CRYPTO_KEM}/${P1}/${OUT}/*.{h,c} > ${P1}_${OUT}.xxx
  done
done
)
endtask

( cd ${MANIFEST}
for P1 in kyber{512,768,1024}{,-90s}
do
  for OUT in clean avx2
  do
    task "${P1}/${OUT} duplicate consistency"
    echo "\
consistency_checks:" > ${P1}_${OUT}.yml
    for P2 in kyber{512,768,1024}{,-90s}
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

for PARAM in kyber{512,768,1024}{,-90s}
do
  for IMPL in clean avx2
  do
    ( cd ${BUILD_CRYPTO_KEM}/${PARAM}/${IMPL}
    sed -i -s "s/AES256CTR_NAMESPACE/KYBER_NAMESPACE/g" *.c *.h
    sed -i -s "s/FIPS202X4_NAMESPACE/KYBER_NAMESPACE/g" *.c *.h

    NAMESPACE=$(echo PQCLEAN_${PARAM//-/}_${IMPL} | tr [:lower:] [:upper:])
    for X in $(grep KYBER_NAMESPACE *.{c,h} | cut -f2 -d' ' | sort -u); do
      sed -i -s "/\\b${X}\\b\.[ch]"'/!s/'"\\b${X}\\b/${NAMESPACE}_${X}/g" *.c *.h
    done
    sed -i -s "s/, & PQCLEAN/, \&PQCLEAN/g" poly.c
    sed -i -s '/KYBER_NAMESPACE/d' *.{c,h}
    sed -i -s "s/CRYPTO_/${NAMESPACE}_CRYPTO_/" *.h
    sed -i "s/API_H/${NAMESPACE}_API_H/" api.h
    [ "${IMPL}" == "avx2" ] && sed -i -s "s/cdecl(\(.*\))/cdecl(${NAMESPACE}_\1)/" *.S
    )
  done
done
endtask

task 'Checking include guards'
for PARAM in kyber{512,768,1024}{,-90s}
do
  for IMPL in clean avx2
  do
    NAMESPACE=$(echo PQCLEAN_${PARAM//-/}_${IMPL} | tr [:lower:] [:upper:])

    FILES=(${BUILD_CRYPTO_KEM}/${PARAM}/${IMPL}/*.h)

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
for PARAM in kyber{512,768,1024}{,-90s}
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
( cd ${BUILD}; tar czf ${BASE}/pqclean-kyber-$(date +"%Y%m%d").tar.gz crypto_kem test )
endtask
