#!/bin/bash

VERSION=$(cat VERSION)

BASE=`dirname $0`
BASE=`cd $BASE && pwd`
echo $BASE

ARCHIVE=${BASE}/${VERSION}.zip
BUILD=${BASE}/crypto_kem
UPSTREAM=${BASE}/upstream

function task {
  echo -e "[ ]" $1
}

function endtask {
  echo -e "\e[1A[x]"
}

function cleanup {
  rm -rf ${BUILD}
  rm -rf ${UPSTREAM}
}
trap cleanup EXIT

if [ -e "$BUILD" ]; then
  echo "Error; directory already exists; delete first."
  exit -1
fi

if [ ! -f ${ARCHIVE} ]
then
  wget -P ${BASE} https://github.com/jschanck/ntru/archive/${VERSION}.zip
fi

rm -rf ${UPSTREAM}
task "Unpacking ${ARCHIVE}"
unzip -qq ${ARCHIVE}
mv ntru-${VERSION} ${UPSTREAM}
endtask

for PARAM in hrss701 hps2048509 hps2048677 hps4096821; do
  mkdir -p ${BUILD}/ntru${PARAM}/avx2
  mkdir -p ${BUILD}/ntru${PARAM}/clean

  export NTRU_NAMESPACE=$(echo PQCLEAN_NTRU${PARAM}_AVX2_ | tr [:lower:] [:upper:])
  task "Building .S files for avx2-${PARAM}"
  ( cd ${UPSTREAM}/avx2-${PARAM} && make -B asm >/dev/null)
  endtask

  task "Copying ref-${PARAM} to ntru${PARAM}/clean/"
  ( cd ${UPSTREAM}/ref-${PARAM}/
    cp -Lp api.h cmov.h owcpa.h params.h poly.h sample.h ${BUILD}/ntru${PARAM}/clean/
    cp -Lp cmov.c kem.c owcpa.c pack3.c packq.c poly.c poly_lift.c poly_mod.c poly_r2_inv.c poly_rq_mul.c poly_s3_inv.c sample.c sample_iid.c ${BUILD}/ntru${PARAM}/clean/ )
  endtask

  task "Copying avx2-${PARAM} to ntru${PARAM}/clean/"
  ( cd ${UPSTREAM}/avx2-${PARAM}/
    cp -Lp api.h cmov.h owcpa.h params.h poly.h poly_r2_inv.h sample.h ${BUILD}/ntru${PARAM}/avx2/
    cp -Lp cmov.c kem.c owcpa.c pack3.c packq.c poly.c poly_r2_inv.c poly_s3_inv.c sample.c sample_iid.c ${BUILD}/ntru${PARAM}/avx2/
    cp -Lp *.s ${BUILD}/ntru${PARAM}/avx2/ )
  endtask

  if [ "${PARAM}" != "hrss701" ]; then
    ( cd ${UPSTREAM}/ref-${PARAM}/
      cp -Lp crypto_sort_int32.h ${BUILD}/ntru${PARAM}/clean/
      cp -Lp crypto_sort_int32.c ${BUILD}/ntru${PARAM}/clean/ )

    ( cd ${UPSTREAM}/avx2-${PARAM}/
      cp -Lp crypto_sort_int32.h ${BUILD}/ntru${PARAM}/avx2/
      cp -Lp crypto_sort_int32.c poly_lift.c ${BUILD}/ntru${PARAM}/avx2/ )
  fi

# Makefiles and other metadata
( cd ${BUILD}/ntru${PARAM}/
echo "Public Domain" > clean/LICENSE
cp clean/LICENSE avx2/LICENSE

echo "\
# This Makefile can be used with GNU Make or BSD Make

LIB=libntru${PARAM}_clean.a
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

LIBRARY=libntru${PARAM}_clean.lib
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

LIB=libntru${PARAM}_avx2.a
HEADERS=$(basename -a avx2/*.h | tr '\n' ' ')
OBJECTS=$(basename -a avx2/*.c | sed 's/\.c/.o/' | tr '\n' ' ') \\
        $(basename -a avx2/square_* | sort -V | sed 's/\.s/.o/' | tr '\n' ' ') \\
        $(basename -a avx2/poly_*.s | sed 's/\.s/.o/' | tr '\n' ' ') vec32_sample_iid.o

CFLAGS=-O3 -mavx2 -mbmi2 -Wall -Wextra -Wpedantic -Wvla -Werror -Wredundant-decls -Wmissing-prototypes -std=c99 -I../../../common \$(EXTRAFLAGS)

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
name: ntruhps2048509
type: kem
claimed-nist-level: 1
claimed-security: IND-CCA2
length-public-key: 699
length-secret-key: 935
length-ciphertext: 699
length-shared-secret: 32
nistkat-sha256: fc314366fbe795e2db6d29abb9f5b2ff43f0f608d0bd66161f9450364f0d271b" \
> ${BUILD}/ntruhps2048509/META.yml

echo "\
name: ntruhps2048677
type: kem
claimed-nist-level: 3
claimed-security: IND-CCA2
length-public-key: 930
length-secret-key: 1234
length-ciphertext: 930
length-shared-secret: 32
nistkat-sha256: 33e2cad6c2a2f17991517050d7a1b745908c84b8283a4e0f07dbe6f62d166507" \
> ${BUILD}/ntruhps2048677/META.yml

echo "\
name: ntruhps4096821
type: kem
claimed-nist-level: 5
claimed-security: IND-CCA2
length-public-key: 1230
length-secret-key: 1590
length-ciphertext: 1230
length-shared-secret: 32
nistkat-sha256: 1a8382ae0c801a43cf461c98d22743f5b2d8a1ffed1b1df0dd767de2c2874597" \
> ${BUILD}/ntruhps4096821/META.yml

echo "\
name: ntruhrss701
type: kem
claimed-nist-level: 3
claimed-security: IND-CCA2
length-public-key: 1138
length-secret-key: 1450
length-ciphertext: 1138
length-shared-secret: 32
nistkat-sha256: 501e000c3eb374ffbfb81b0f16673a6282116465936608d7d164b05635e769e8" \
> ${BUILD}/ntruhrss701/META.yml

echo "\
principal-submitters:
  - John M. Schanck
auxiliary-submitters:
  - Cong Chen
  - Oussama Danba
  - Jeffrey Hoffstein
  - Andreas Hülsing
  - Joost Rijneveld
  - Tsunekazu Saito
  - Peter Schwabe
  - William Whyte
  - Keita Xagawa
  - Takashi Yamakawa
  - Zhenfei Zhang
implementations:
    - name: clean
      version: https://github.com/jschanck/ntru/tree/${VERSION:0:8} reference implementation
    - name: avx2
      version: https://github.com/jschanck/ntru/tree/${VERSION:0:8} avx2 implementation
      supported_platforms:
          - architecture: x86_64
            operating_systems:
                - Linux
                - Darwin
            required_flags:
                - avx2
                - bmi2" \
  | tee -a ${BUILD}/*/META.yml >/dev/null

# Simplify ifdefs
task 'Simplifying ifdefs'
sed -i -s "s/NTRU_PACK_DEG > (NTRU_PACK_DEG \/ 5) \* 5/0/" ${BUILD}/ntru{hrss701,hps4096821}/*/pack3.c
sed -i -s "s/NTRU_PACK_DEG > (NTRU_PACK_DEG \/ 5) \* 5/1/" ${BUILD}/ntru{hps2048509,hps2048677}/*/pack3.c
sed -i -s "s/(NTRU_N - 1) > ((NTRU_N - 1) \/ 4) \* 4/0/" ${BUILD}/ntru*/*/sample.c

unifdef -k -m -DCRYPTO_NAMESPACE ${BUILD}/ntru*/*/params.h
unifdef -k -m -UNTRU_HPS -DNTRU_HRSS -DNTRU_N=701 -DNTRU_Q=8192 ${BUILD}/ntruhrss701/*/*.{c,h}
unifdef -k -m -DNTRU_HPS -UNTRU_HRSS -DNTRU_N=509 -DNTRU_Q=2048 ${BUILD}/ntruhps2048509/*/*.{c,h}
unifdef -k -m -DNTRU_HPS -UNTRU_HRSS -DNTRU_N=677 -DNTRU_Q=2048 ${BUILD}/ntruhps2048677/*/*.{c,h}
unifdef -k -m -DNTRU_HPS -UNTRU_HRSS -DNTRU_N=821 -DNTRU_Q=4096 ${BUILD}/ntruhps4096821/*/*.{c,h}
endtask

task "Patching for PQClean"
# Remove __attribute__ from crypto_sort_int32.c
sed -i -s 's/__attribute__((noinline))//' ${BUILD}/*/avx2/crypto_sort_int32.c

# Replace unsigned char with uint8_t at top level
sed -i -s "s/unsigned char /uint8_t /g" ${BUILD}/*/*/api.h
sed -i -s "s/unsigned char /uint8_t /g" ${BUILD}/*/*/kem.c
sed -i -s "3a#include <stdint.h>\n" ${BUILD}/*/*/api.h

# Replace crypto_hash_sha3_256 with sha3_256
sed -i -s "s/crypto_hash_sha3256\.h/fips202.h/g" ${BUILD}/*/*/kem.c
sed -i -s "s/crypto_hash_sha3256/sha3_256/g" ${BUILD}/*/*/kem.c
endtask

task "Namespacing"
# Manual namespacing
for PARAM in hrss701 hps2048509 hps2048677 hps4096821; do
  for IMPL in clean avx2; do
    ( cd ${BUILD}/ntru${PARAM}/${IMPL}
    NTRU_NAMESPACE=$(echo PQCLEAN_NTRU${PARAM}_${IMPL}_ | tr [:lower:] [:upper:])
    for X in $(grep CRYPTO_NAMESPACE *.{c,h} | cut -f2 -d' ' | sort -u); do
      sed -i -s "s/ ${X}/ ${NTRU_NAMESPACE}${X}/g" *.c *.h
    done
    sed -i -s '/CRYPTO_NAMESPACE/d' *.{c,h}
    sed -i -s '/kem\.h/d' kem.c
    sed -i "s/API_H/${NTRU_NAMESPACE}API_H/" api.h
    sed -i "s/CRYPTO_/${NTRU_NAMESPACE}CRYPTO_/" api.h )
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
  ${BUILD}/*/*/*.{c,h} >/dev/null
endtask

# Package
task "Packaging"
tar czf pqclean-ntru-$(date +"%Y%m%d").tar.gz crypto_kem/
endtask

# Cleanup
rm -rf ${BUILD}
rm -rf ${UPSTREAM}
