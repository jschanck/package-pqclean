VERSION=$(cat VERSION)
PACKAGER=$(git rev-parse HEAD)

PYTHON=/usr/bin/python3

BASE=`dirname $0`
BASE=`cd ${BASE} && pwd`
cd ${BASE}

BUILD=${BASE}/build
BUILD_CRYPTO_KEM=${BUILD}/crypto_kem
BUILD_TEST=${BUILD}/test

SUPERCOP=${BUILD}/${VERSION}
SCRIPTS=${BASE}/scripts

ARCHIVE=${VERSION}.tar.xz

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
fi
mkdir -p ${BUILD_CRYPTO_KEM} ${BUILD_TEST}

if [ ! -e "${SUPERCOP}" ]
then
  if [ ! -f ${BASE}/${VERSION}.tar.xz ]
  then
    wget -P ${BASE} https://bench.cr.yp.to/supercop/${ARCHIVE}
  fi
  (cd ${BUILD}
  task "Unpacking ${VERSION}"
  unxz < ${BASE}/${VERSION}.tar.xz | tar -xf -
  endtask
  )
fi

task 'Applying patches'
( cd ${SUPERCOP}

for X in ${BASE}/patches/*
do
  patch -s -p1 < ${X}
done

for X in 653x4621 761x4591 857x5167
do
  IFS=x read p m <<< ${X}

  ${PYTHON} ${SCRIPTS}/gen_crypto_decode_avx.py $p $m > crypto_decode/${X}/avx/decode.c
  ${PYTHON} ${SCRIPTS}/gen_crypto_decode_portable.py $p $m > crypto_decode/${X}/portable/decode.c
  ${PYTHON} ${SCRIPTS}/gen_crypto_decode_int16.py $p $m > crypto_decode/${X}/int16/decode.c

  ${PYTHON} ${SCRIPTS}/gen_crypto_encode_avx.py $p $m > crypto_encode/${X}/avx/encode.c
  ${PYTHON} ${SCRIPTS}/gen_crypto_encode_portable.py $p $m > crypto_encode/${X}/portable/encode.c

  ${PYTHON} ${SCRIPTS}/gen_crypto_core_inv3_avx.py $p > crypto_core/inv3sntrup${p}/avx/r3_recip.c
done

for X in 653x1541x1541x2310xTrue 761x1531x1531x2295xTrue 857x1723x1723x2583xTrue
do
  IFS=x read p m0 m1 off div3 <<< ${X}

  ${PYTHON} ${SCRIPTS}/gen_crypto_decode_avx.py $p $m0 $m1 $off $div3 > crypto_decode/${p}x${m0}/avx/decode.c
  ${PYTHON} ${SCRIPTS}/gen_crypto_decode_int16.py $p $m0 $m1 $off $div3 > crypto_decode/${p}x${m0}/int16/decode.c
  ${PYTHON} ${SCRIPTS}/gen_crypto_decode_portable.py $p $m0 $m1 $off $div3 > crypto_decode/${p}x${m0}/portable/decode.c

  ${PYTHON} ${SCRIPTS}/gen_crypto_encode_avx.py $p $m0 $m1 $off $div3 > crypto_encode/${p}x${m0}/avx/encode.c
  ${PYTHON} ${SCRIPTS}/gen_crypto_encode_portable.py $p $m0 $m1 $off $div3 > crypto_encode/${p}x${m0}/portable/encode.c

  ${PYTHON} ${SCRIPTS}/gen_crypto_encode_avx.py $p $m0 $m1 $off $div3 True > crypto_encode/${p}x${m0}round/avx/encode.c
done
)
endtask


for PARAM in {sntrup,ntrulpr}{653,761,857}
do
  mkdir -p ${BUILD_CRYPTO_KEM}/${PARAM}/{clean,avx2}
  cp -Lp ${SUPERCOP}/crypto_kem/${PARAM}/factored/*.{c,h} ${BUILD_CRYPTO_KEM}/${PARAM}/clean/
  cp -Lp ${SUPERCOP}/crypto_kem/${PARAM}/factored/*.{c,h} ${BUILD_CRYPTO_KEM}/${PARAM}/avx2/
done

for PARAM in {sntrup,ntrulpr}{653,761,857}
do
  for OUT in clean avx2
  do
    # Add several #includes to params.h
    # Sort of a kludge, but its easier to grab the required dependencies
    # if we do all includes up front.
    sed -i 's/^\(.*\)round\.h"/\1round.h"\n\1.h"/' ${BUILD_CRYPTO_KEM}/${PARAM}/${OUT}/params.h
    # Similary, we need crypto_core_weight[...].h and crypto_encode_int16.h for some parameter sets
    sed -i "3a#include \"crypto_sort_int32.h\"" ${BUILD_CRYPTO_KEM}/${PARAM}/${OUT}/params.h
    sed -i "3a#include \"crypto_sort_uint32.h\"" ${BUILD_CRYPTO_KEM}/${PARAM}/${OUT}/params.h
    if [ -e "${SUPERCOP}/crypto_core/weight${PARAM}" ]
    then
      sed -i "3a#include \"crypto_core_weight${PARAM}.h\"" ${BUILD_CRYPTO_KEM}/${PARAM}/${OUT}/params.h
      sed -i "3a#include \"crypto_encode_int16.h\"" ${BUILD_CRYPTO_KEM}/${PARAM}/${OUT}/params.h
    fi

    DEPS=$(grep crypto_.*.h ${BUILD_CRYPTO_KEM}/${PARAM}/${OUT}/params.h \
                | cut -d' ' -f 2                               \
                | cut -d'.' -f 1                               \
                | tr -d '\"')
    for X in ${DEPS}
    do
      O=$(echo $X | sed 's/_/\//2' | cut -d'/' -f 1)
      P=$(echo $X | sed 's/_/\//2' | cut -d'/' -f 2)
      # For /clean, favor portable then ref
      for PREF in portable ref
      do
        [ -e "${SUPERCOP}/${O}/${P}/${PREF}/" ] && REF=${PREF} && break
      done

      # For /avx2, favor avx then portable then ref
      for PREF in avx portable ref
      do
        [ -e "${SUPERCOP}/${O}/${P}/${PREF}/" ] && AVX=${PREF} && break
      done
      # Special cases
      [ "${O}" == "crypto_sort" ] && [ "${P}" == "int32" ] && REF=x86 && AVX=avx2
      [ "${O}" == "crypto_sort" ] && [ "${P}" == "uint32" ] && REF=useint32 && AVX=useint32

      # Copy all .c files. Change filenames to avoid conflicts if necessary.
      [ "${OUT}" == "clean" ] && IN=${REF}
      [ "${OUT}" == "avx2" ] && IN=${AVX}

      task "Copying ${O}/${P}/${IN} to ${PARAM}/${OUT}"
      ( cd ${SUPERCOP}/${O}/${P}/${IN}/
      if [ "$(ls *.c | wc -l)" == "1" ]
      then
        cp -Lp *.c ${BUILD_CRYPTO_KEM}/${PARAM}/${OUT}/${X}.c
      else
        for F in *.c
        do
          cp -Lp ${F} ${BUILD_CRYPTO_KEM}/${PARAM}/${OUT}/${X}_${F}
        done
        # Move the main file to the right location
        mv $(grep "^\(void\|int\) ${O}(" ${BUILD_CRYPTO_KEM}/${PARAM}/${OUT}/${X}_*.c | cut -d: -f1) ${BUILD_CRYPTO_KEM}/${PARAM}/${OUT}/${X}.c
      fi
      sed -i -s "s/${O}\.h/${X}\.h/" ${BUILD_CRYPTO_KEM}/${PARAM}/${OUT}/*.c

      # Copy all .h files (except api.h). Change filenames and update #includes 
      for F in $(ls *.h | grep -v api.h | grep -v params.h)
      do
        cp -Lp ${F} ${BUILD_CRYPTO_KEM}/${PARAM}/${OUT}/${X}_${F}
        sed -i -s "s/\"${F}/\"${X}_${F}/" ${BUILD_CRYPTO_KEM}/${PARAM}/${OUT}/*
      done
      [ -e "params.h" ] && cp -Lp params.h ${BUILD_CRYPTO_KEM}/${PARAM}/${OUT}/DELETEME${X}_params.h
      )
      endtask

      if [ -e "${SUPERCOP}/${O}/${P}/${IN}/api.h" ]
      then
        API=$(sed "s/CRYPTO_/${X}_/" ${SUPERCOP}/${O}/${P}/${IN}/api.h)
      else
        API=""
      fi

      MAIN=${BUILD_CRYPTO_KEM}/${PARAM}/${OUT}/${X}
      PROTOTYPE=$(grep '^\(void\|int\) crypto_.*)' ${MAIN}.c | sed "s/${O}/${X}/")
      UPX=$(echo ${X} | tr [:lower:] [:upper:])
      echo "\
#ifndef ${UPX}_H
#define ${UPX}_H
#include <stdint.h>
${API}

#define ${X} CRYPTO_NAMESPACE(${X})
${PROTOTYPE};
#endif" > ${BUILD_CRYPTO_KEM}/${PARAM}/${OUT}/${X}.h
      for Y in $(sed "s/CRYPTO_//" ${SUPERCOP}/${O}/${P}/${IN}/api.h | cut -d' ' -f 2)
      do
        sed -i -s "s/${O}_${Y}/${X}_${Y}/" ${MAIN}.c
      done
      sed -i -s "s/${O}(/${X}(/" ${MAIN}.c
    done
  done

  # The "mod q" and "mod 3" ntt.{c,h} are identical
  (cd ${BUILD_CRYPTO_KEM}/${PARAM}/avx2/
  [ -e "crypto_core_mult3${PARAM}_ntt.c" ] && rm crypto_core_mult3${PARAM}_ntt.c
  [ -e "crypto_core_mult3${PARAM}_ntt.h" ] && rm crypto_core_mult3${PARAM}_ntt.h
  [ -e "crypto_core_mult3${PARAM}.c" ] \
    && sed -i "s/mult3${PARAM}_ntt.h/mult${PARAM}_ntt.h/" crypto_core_mult3${PARAM}.c
  )
done

for PARAM in sntrup{653,761,857}
do
  task "Copying crypto_decode/int16/ref to ${PARAM}/avx2"
  API=$(sed "s/CRYPTO_/${X}_/" ${SUPERCOP}/crypto_decode/int16/ref/api.h)
  cp -Lp ${SUPERCOP}/crypto_decode/int16/ref/*.c ${BUILD_CRYPTO_KEM}/${PARAM}/avx2/crypto_decode_int16.c
  echo "\
#ifndef CRYPTO_DECODE_INT16_H
#define CRYPTO_DECODE_INT16_H
#include <stdint.h>
${API}
#define crypto_decode_int16 CRYPTO_NAMESPACE(crypto_decode_int16)
void crypto_decode_int16(void *x,const unsigned char *s);
#endif" > ${BUILD_CRYPTO_KEM}/${PARAM}/avx2/crypto_decode_int16.h
  sed -i -s "s/crypto_decode\.h/crypto_decode_int16\.h/" ${BUILD_CRYPTO_KEM}/${PARAM}/avx2/crypto_decode_int16.c
  sed -i -s "s/crypto_decode(/crypto_decode_int16(/" ${BUILD_CRYPTO_KEM}/${PARAM}/avx2/crypto_decode_int16.c
  endtask
done

for PARAM in ntrulpr{653,761,857}
do
  task "Writing PQClean compatible crypto_stream_aes256ctr for ${PARAM}"

echo '#include "crypto_stream_aes256ctr.h"

int crypto_stream_aes256ctr(
    uint8_t *out,
    size_t outlen,
    const uint8_t nonce[AESCTR_NONCEBYTES],
    const uint8_t key[AES256_KEYBYTES]) {

    aes256ctx state;
    aes256_ctr_keyexp(&state, key);
    aes256_ctr(out, outlen, nonce, &state);
    aes256_ctx_release(&state);
    return 0;
}' | tee ${BUILD_CRYPTO_KEM}/${PARAM}/{clean,avx2}/crypto_stream_aes256ctr.c >/dev/null

echo '#ifndef CRYPTO_STREAM_AES256CTR_H
#define CRYPTO_STREAM_AES256CTR_H

#include <stddef.h>
#include <stdint.h>

#include "aes.h"

#define crypto_stream_aes256ctr CRYPTO_NAMESPACE(crypto_stream_aes256ctr)
int crypto_stream_aes256ctr(
    uint8_t *out,
    size_t outlen,
    const uint8_t nonce[AESCTR_NONCEBYTES],
    const uint8_t key[AES256_KEYBYTES]);

#endif' | tee ${BUILD_CRYPTO_KEM}/${PARAM}/{clean,avx2}/crypto_stream_aes256ctr.h >/dev/null
  endtask
done

for PARAM in {sntrup,ntrulpr}{653,761,857}
do
  task "Writing dummy crypto_declassify.h for ${PARAM}"

echo '#ifndef crypto_declassify_h
#define crypto_declassify_h

#define crypto_declassify(BUF,SIZE)

#endif' | tee ${BUILD_CRYPTO_KEM}/${PARAM}/{clean,avx2}/crypto_declassify.h >/dev/null
  endtask
done

task 'Adding #defines from dependencies'
for PARAM in {sntrup,ntrulpr}{653,761,857}
do
  for OUT in clean avx2
  do
    ( cd ${BUILD_CRYPTO_KEM}/${PARAM}/${OUT}/
    grep "define \(ppad\|qinv\|q14\|q18\|q27\|q31\|qinvvec\|crypto_core_weight\|endingmask\) " DELETEME*_params.h 2>/dev/null \
      | cut -d":" -f 2 \
      | sort -u \
      | while read Y
        do
          sed -i "6a${Y}" params.h
        done
    # cleanup qinv
    sed -i 's/qinv \(-[0-9]*\)/qinv (\1)/' params.h
    rm -f DELETEME*_params.h )
  done
done
endtask

task 'Renaming integer types' 
sed -i -s '/crypto_u\?int.*\.h/d' ${BUILD_CRYPTO_KEM}/*/*/*.c
sed -i -s 's/crypto_\(uint\|int\)\(8\|16\|32\|64\)/\1\2_t/' ${BUILD_CRYPTO_KEM}/*/*/*.c
endtask

task 'Substituting PQClean AES, SHA, and API' 
for PARAM in {sntrup,ntrulpr}{653,761,857}
do
  for IMPL in clean avx2
  do
    ( cd ${BUILD_CRYPTO_KEM}/${PARAM}/${IMPL}
    # Replace crypto_stream_aes256ctr.h with aes.h
    sed -i -s '/crypto_stream_aes256ctr_publicinputs\.h/d' kem.c
    sed -i -s 's/_publicinputs//g' kem.c
    # Replace crypto_hash_sha512.h with sha512.h
    sed -i -s 's/crypto_hash_sha512\.h/sha2.h/g' kem.c
    sed -i -s 's/crypto_hash_sha512/sha512/g' kem.c
    # Replace crypto_kem.h include with api.h
    sed -i -s '/crypto_kem\.h/d' kem.c
    echo -e "#include \"api.h\"\n$(cat kem.c)" > kem.c )
  done
done
endtask

task 'Correcting crypto_core_* declarations and definitions' 
# 2 parameters
for X in inv3 inv scale3 wforce
do
  sed -i -s "s/\(crypto_core_${X}(.*\), \?0, \?0/\1/" ${BUILD_CRYPTO_KEM}/sntru*/*/kem.c
  sed -i -s 's/, \?const unsigned char .kbytes, \?const unsigned char .cbytes//' ${BUILD_CRYPTO_KEM}/sntru*/*/crypto_core_${X}*
done
sed -i -s "s/\(crypto_core_weight(.*\), \?0, \?0/\1/" ${BUILD_CRYPTO_KEM}/sntru*/*/crypto_core_wforcesntru*
sed -i -s 's/, \?const unsigned char .kbytes, \?const unsigned char .cbytes//' ${BUILD_CRYPTO_KEM}/sntru*/*/crypto_core_weightsntru*
# 3 parameters
sed -i -s "s/\(crypto_core_mult3(.*\), \?0/\1/" ${BUILD_CRYPTO_KEM}/sntru*/*/kem.c
sed -i -s 's/, \?const unsigned char \*cbytes//' ${BUILD_CRYPTO_KEM}/sntru*/*/crypto_core_mult3*
sed -i -s "s/\(crypto_core_mult(.*\), \?0/\1/" ${BUILD_CRYPTO_KEM}/*/*/kem.c
sed -i -s 's/, \?const unsigned char \*cbytes//' ${BUILD_CRYPTO_KEM}/*/*/crypto_core_mult*
endtask

MANIFEST=${BUILD_TEST}/duplicate_consistency
mkdir -p ${MANIFEST}
task "Preparing for duplicate consistency"
( cd ${MANIFEST}
for P1 in sntrup653 sntrup761 sntrup857 ntrulpr653 ntrulpr761 ntrulpr857
do
  for OUT in clean avx2
  do
    sha1sum ${BUILD_CRYPTO_KEM}/${P1}/${OUT}/*.{h,c} > ${P1}_${OUT}.xxx
  done
done
)
endtask

( cd ${MANIFEST}
for P1 in {sntrup,ntrulpr}{653,761,857}
do
  for OUT in clean avx2
  do
    task "${P1}/${OUT} duplicate consistency"
    echo "\
consistency_checks:" > ${P1}_${OUT}.yml
    for P2 in {sntrup,ntrulpr}{653,761,857}
    do
      for IN in clean avx2
      do
        if ([ "${P1}" == "${P2}" ] && [ "${IN}" == "${OUT}" ]) || [ "${P1}" \> "${P2}" ]; then continue; fi
        echo "\
- source:
    scheme: ${P2}
    implementation: ${IN}
  files:" >> ${P1}_${OUT}.yml
        for HASH in $(cat ${P2}_${IN}.xxx | cut -d ' ' -f 1)
        do
          X=$(grep $HASH ${P1}_${OUT}.xxx | cut -d ' ' -f 3)
          if [ x${X} != 'x' ]
          then
            [ -e ${BUILD_CRYPTO_KEM}/${P2}/${OUT}/$(basename $X) ] && \
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
# Manual namespacing
for PARAM in {sntrup,ntrulpr}{653,761,857}
do
  for IMPL in clean avx2
  do
    ( cd ${BUILD_CRYPTO_KEM}/${PARAM}/${IMPL}
    NAMESPACE=$(echo PQCLEAN_${PARAM}_${IMPL} | tr [:lower:] [:upper:])
    for X in $(grep CRYPTO_NAMESPACE *.{c,h} | cut -f2 -d' ' | sort -u); do
      sed -i -s "s/ ${X}/ ${NAMESPACE}_${X}/g" *.c *.h
    done
    sed -i -s '/CRYPTO_NAMESPACE/d' *.{c,h}
    sed -i -s "s/CRYPTO_/${NAMESPACE}_CRYPTO_/" *.h
    sed -i -s "s/crypto_kem_/${NAMESPACE}_crypto_kem_/g" kem.c
    echo "\
#ifndef ${NAMESPACE}_API_H
#define ${NAMESPACE}_API_H

#define ${NAMESPACE}_CRYPTO_ALGNAME \"${PARAM}\"

$(cat api.h)

int ${NAMESPACE}_crypto_kem_keypair(unsigned char *pk, unsigned char *sk);
int ${NAMESPACE}_crypto_kem_enc(unsigned char *c, unsigned char *k, const unsigned char *pk);
int ${NAMESPACE}_crypto_kem_dec(unsigned char *k, const unsigned char *c, const unsigned char *sk); \

#endif
" > api.h
    )
  done
done
endtask

task 'Sorting #includes'
for PARAM in {sntrup,ntrulpr}{653,761,857}
do
  for IMPL in clean avx2
  do
    for F in ${BUILD_CRYPTO_KEM}/${PARAM}/${IMPL}/*.h
    do
      GUARD=$(head -n 2 ${F})
      INCL1=$(grep '^#include \"' ${F} | sort)
      INCL2=$(grep '^#include <' ${F} | sort)
      REST=$(tail -n+3 ${F} | sed '/^#include/d')
      echo -e "${GUARD}\n${INCL1}\n${INCL2}\n${REST}" > ${F}
    done
    for F in ${BUILD_CRYPTO_KEM}/${PARAM}/${IMPL}/*.c
    do
      INCL1=$(grep '^#include \"' ${F} | sort)
      INCL2=$(grep '^#include <' ${F} | sort)
      REST=$(sed '/^#include/d' ${F})
      echo -e "${INCL1}\n${INCL2}\n${REST}" > ${F}
    done
  done
done
endtask

task 'Copying metadata'
# Makefiles and other metadata
for PARAM in {sntrup,ntrulpr}{653,761,857}
do
  ( cd ${BUILD_CRYPTO_KEM}/${PARAM}/

  echo "Public Domain" > clean/LICENSE
  cp -Lp clean/LICENSE avx2/LICENSE
  cp -Lp ${BASE}/meta/crypto_kem_${PARAM}_META.yml META.yml
  echo "\
principal-submitters:
  - Daniel J. Bernstein
  - Chitchanok Chuengsatiansup
  - Tanja Lange
  - Christine van Vredendaal
implementations:
    - name: clean
      version: ${VERSION} via https://github.com/jschanck/package-pqclean/tree/${PACKAGER:0:8}/ntruprime
    - name: avx2
      version: ${VERSION} via https://github.com/jschanck/package-pqclean/tree/${PACKAGER:0:8}/ntruprime
      supported_platforms:
          - architecture: x86_64
            operating_systems:
                - Linux
                - Darwin
            required_flags:
                - avx2" >> META.yml

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
endtask

task 'Styling'
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
task "Packaging pqclean-ntruprime-$(date +"%Y%m%d").tar.gz"
tar czf ${BASE}/pqclean-ntruprime-$(date +"%Y%m%d").tar.gz -C ${BUILD} crypto_kem test
endtask
