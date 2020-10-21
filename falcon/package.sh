VERSION=$(cat VERSION)
PACKAGER=$(git rev-parse HEAD)

PYTHON=/usr/bin/python3

BASE=`dirname $0`
BASE=`cd ${BASE} && pwd`
cd ${BASE}

ARCHIVE=${VERSION}.tar.xz
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
fi
mkdir -p ${BUILD_CRYPTO_SIGN} ${BUILD_TEST}

if [ ! -f ${BASE}/${ARCHIVE} ]
then
  wget -P ${BASE} https://bench.cr.yp.to/supercop/${ARCHIVE}
fi
task "Unpacking ${ARCHIVE}"
( cd ${BUILD}
unxz < ${BASE}/${ARCHIVE} | tar -xf - ${VERSION}/crypto_sign/falcon{512,1024}dyn
mv ${VERSION} ${BUILD_UPSTREAM}
)
endtask

task 'Applying patches'
( cd ${BUILD_UPSTREAM}

for X in ${BASE}/patches/*
do
  patch -s -p1 < ${X}
done
)
endtask

for PARAM in 512 1024
do
  mkdir -p ${BUILD_CRYPTO_SIGN}/falcon-${PARAM}/avx2
  mkdir -p ${BUILD_CRYPTO_SIGN}/falcon-${PARAM}/clean

  task "Copying reference implementation"
  ( cd ${BUILD_UPSTREAM}/crypto_sign/falcon${PARAM}dyn/ref
  OUT=${BUILD_CRYPTO_SIGN}/falcon-${PARAM}/clean/
  cp -Lp api.h fpr.h inner.h ${OUT}
  cp -Lp api.c ${OUT}/pqclean.c
  cp -Lp codec.c common.c fft.c fpr.c keygen.c rng.c sign.c vrfy.c ${OUT} )
  endtask

  task "Copying avx2 implementation"
  ( cd ${BUILD_UPSTREAM}/crypto_sign/falcon${PARAM}dyn/avx2
  OUT=${BUILD_CRYPTO_SIGN}/falcon-${PARAM}/avx2/
  cp -Lp api.h fpr.h inner.h ${OUT}
  cp -Lp api.c ${OUT}/pqclean.c
  cp -Lp codec.c common.c fft.c fpr.c keygen.c rng.c sign.c vrfy.c ${OUT} )
  endtask
done

task 'Copying metadata'
( # Makefiles and other metadata
for PARAM in falcon-{512,1024}
do
  ( cd ${BUILD_CRYPTO_SIGN}/${PARAM}/
echo '\
MIT License

Copyright (c) 2017-2019  Falcon Project

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
' | tee clean/LICENSE avx2/LICENSE >/dev/null

  cp -Lp ${BASE}/meta/crypto_sign_${PARAM}_META.yml META.yml
  echo "\
implementations:
    - name: clean
      version: ${VERSION} via https://github.com/jschanck/package-pqclean/tree/${PACKAGER:0:8}/falcon
    - name: avx2
      version: ${VERSION} via https://github.com/jschanck/package-pqclean/tree/${PACKAGER:0:8}/falcon
      supported_platforms:
          - architecture: x86_64
            operating_systems:
                - Linux
                - Darwin
            required_flags:
                - avx2" >> META.yml

  echo "\
# This Makefile can be used with GNU Make or BSD Make

LIB=lib${PARAM/-/}_clean.a

SOURCES = $(basename -a clean/*.c | tr '\n' ' ')
OBJECTS = $(basename -a clean/*.c | sed 's/\.c/.o/' | tr '\n' ' ')
HEADERS = $(basename -a clean/*.h | tr '\n' ' ')

CFLAGS=-O3 -Wall -Wconversion -Wextra -Wpedantic -Wvla -Werror -Wmissing-prototypes -Wredundant-decls -std=c99 -I../../../common \$(EXTRAFLAGS)

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

LIBRARY=lib${PARAM/-/}_clean.lib
OBJECTS=$(basename -a clean/*.c | sed 's/\.c/.obj/' | tr '\n' ' ')

# Warning C4146 is raised when a unary minus operator is applied to an
# unsigned type; this has nonetheless been standard and portable for as
# long as there has been a C standard, and we do that a lot, especially
# for constant-time computations. Thus, we disable that spurious warning.
CFLAGS=/nologo /O2 /I ..\..\..\common /W4 /wd4146 /WX

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

LIB=lib${PARAM/-/}_avx2.a

SOURCES = $(basename -a avx2/*.c | tr '\n' ' ')
OBJECTS = $(basename -a avx2/*.c | sed 's/\.c/.o/' | tr '\n' ' ')
HEADERS = $(basename -a avx2/*.h | tr '\n' ' ')

CFLAGS=-O3 -Wconversion -mavx2 -Wall -Wextra -Wpedantic -Wvla -Werror -Wmissing-prototypes -Wredundant-decls -std=c99 -I../../../common \$(EXTRAFLAGS)

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
done )
endtask

task 'Removing restrict keyword'
sed -i -s 's/\(fpr\|int8_t\|int32_t\|uint32_t\) \*restrict/\1 */g' ${BUILD_CRYPTO_SIGN}/falcon*/*/*.{c,h}
endtask

task 'Removing TARGET_AVX2 hints'
sed -i -s '/^TARGET_AVX2$/d' ${BUILD_CRYPTO_SIGN}/falcon*/avx2/*.{c,h}
endtask

task 'Simplifying ifdefs'
STRAIGHTEN_IF=( -e :a -e '/#\(if\|elif\).*\\$/N; s/\\\n//; ta' )
sed -i "${STRAIGHTEN_IF[@]}" ${BUILD_CRYPTO_SIGN}/*/*/inner.h

unifdef -k -m \
  -DFALCON_ASM_CORTEXM4=0 \
  -DFALCON_AVX2=0 \
  -DFALCON_FMA=0 \
  -DFALCON_FPEMU=1 \
  -DFALCON_FPNATIVE=0 \
  -DFALCON_KG_CHACHA20=0 \
  -DFALCON_LE=0 \
  -DFALCON_UNALIGNED=0 \
  -DFALCON_RAND_GETENTROPY=0 \
  -DFALCON_RAND_URANDOM=0 \
  -DFALCON_RAND_WIN32=0 \
  -UTARGET_AVX2 \
  -Drestrict \
  ${BUILD_CRYPTO_SIGN}/falcon*/clean/*.{c,h}

unifdef -k -m \
  -DFALCON_ASM_CORTEXM4=0 \
  -DFALCON_AVX2=1 \
  -DFALCON_FMA=0 \
  -DFALCON_FPEMU=0 \
  -DFALCON_FPNATIVE=1 \
  -DFALCON_KG_CHACHA20=0 \
  -DFALCON_LE=1 \
  -DFALCON_UNALIGNED=1 \
  -DFALCON_RAND_GETENTROPY=0 \
  -DFALCON_RAND_URANDOM=0 \
  -DFALCON_RAND_WIN32=0 \
  -UTARGET_AVX2 \
  -D__x86_64__ \
  -Drestrict \
  ${BUILD_CRYPTO_SIGN}/falcon*/avx2/*.{c,h}
endtask

MANIFEST=${BUILD_TEST}/duplicate_consistency
mkdir -p ${MANIFEST}
task "Preparing for duplicate consistency"
( cd ${MANIFEST}
for P1 in falcon-{512,1024}
do
  for OUT in clean avx2
  do
    for F in ${BUILD_CRYPTO_SIGN}/${P1}/${OUT}/*.{h,c}
    do
      sed 's/falcon\(512\|1024\)dyn_\(ref\|avx2\)_//g' ${F} | sha1sum - | sed "s/-/$(basename ${F})/" >> ${P1}_${OUT}.xxx
    done
  done
done
)
endtask

( cd ${MANIFEST}
for P1 in falcon-{512,1024}
do
  for OUT in clean avx2
  do
    task "${P1}/${OUT} duplicate consistency"
    echo "\
consistency_checks:" > ${P1}_${OUT}.yml
    for P2 in falcon-{512,1024}
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
# Insert hooks for namespacing. These will be removed later.
for PARAM in 512 1024
do
  for IMPL in clean avx2
  do
    ( cd ${BUILD_CRYPTO_SIGN}/falcon-${PARAM}/${IMPL}
    NAMESPACE=$(echo PQCLEAN_FALCON${PARAM}_${IMPL} | tr [:lower:] [:upper:])
    sed -i -s "s/falcon${PARAM}dyn_\(ref\|avx2\)_/${NAMESPACE}_/g" *.{c,h}
    sed -i -s "s/CRYPTO_/${NAMESPACE}_CRYPTO_/g" *.{c,h}
    sed -i "s/API_H/${NAMESPACE}_API_H/" api.h
    sed -i -s "s/crypto_sign/${NAMESPACE}_crypto_sign/" api.h pqclean.c
    )
  done
done
endtask

task 'Checking include guards'
for PARAM in falcon-{512,1024}
do
  for IMPL in clean avx2
  do
    for F in ${BUILD_CRYPTO_SIGN}/${PARAM}/${IMPL}/*.h
    do
      NAMESPACE=$(echo PQCLEAN_${PARAM/-/}_${IMPL} | tr [:lower:] [:upper:])
      DEF=$(basename ${F} | tr [:lower:] [:upper:] | tr '.' '_')
      GUARD="#ifndef ${NAMESPACE}_${DEF}\n#define ${NAMESPACE}_${DEF}"
      START=$(grep -n -m 1 '^#ifndef' ${F} | cut -d: -f1)
      if [ x${START} == x ]
      then
        echo -e "${GUARD}\n\n$(cat ${F})\n#endif" > ${F}
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
for PARAM in falcon-{512,1024}
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
( cd ${BUILD}; tar czf ${BASE}/pqclean-falcon-$(date +"%Y%m%d").tar.gz crypto_sign test )
endtask
