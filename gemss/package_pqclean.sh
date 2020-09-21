#!/bin/bash

BASE=`dirname $0`
BASE=`cd ${BASE} && pwd`
cd ${BASE}

VERSION=$(cat ${BASE}/VERSION)
ARCHIVE=${VERSION/.a/.zip}

BUILD=${BASE}/build
BUILD_UPSTREAM=${BUILD}/upstream
BUILD_CRYPTO_SIGN=${BUILD}/crypto_sign
BUILD_TEST=${BUILD}/test

SCRIPTS=${BASE}/scripts

#set -o errexit

function task {
  echo -e "[ ]" $1
}

function endtask {
  echo -e "\e[1A[x]"
}

function cleanup {
  rm -rf ${BUILD_UPSTREAM}
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
  wget -P ${BASE} http://www-polsys.lip6.fr/~ryckeghem/packages/${ARCHIVE}
fi

task "Unpacking ${ARCHIVE}"
unzip -qq -d ${BUILD} ${BASE}/${ARCHIVE}
mv ${BUILD}/${VERSION}* ${BUILD_UPSTREAM}
cd ${BUILD_UPSTREAM}
for X in {Ref*,Opt*}/sign/*/*/*
do
  IFS=/ read IMPL SIGN PARAM SUB FILE <<< ${X}
  if [ ${PARAM} == 'GeMSS128' ]; then continue; fi 
  if [ ${FILE} == 'choice_crypto.h' ]; then continue; fi 
  ln -sf ../../GeMSS128/${SUB}/${FILE} ${X}
done
endtask

task 'Applying patches to upstream source code'
cd ${BUILD_UPSTREAM}

for X in ${BASE}/patches/*
do
  patch -s -p1 < ${X}
done
endtask

task 'Copying files'
for COLOR in '' 'Blue' 'Red'
do
  for SECURITY in 128 192 256
  do
    INPARAM=${COLOR}GeMSS${SECURITY}
    OUTPARAM=gemss-$(echo $COLOR | tr [:upper:] [:lower:])-${SECURITY}
    OUTPARAM=${OUTPARAM/--/-}
    mkdir -p ${BUILD_CRYPTO_SIGN}/${OUTPARAM}/{clean,avx2}
    cp -Lp --no-preserve=mode ${BUILD_UPSTREAM}/Reference_Implementation/sign/${INPARAM}/*/*.{c,h} ${BUILD_CRYPTO_SIGN}/${OUTPARAM}/clean/
    cp -Lp --no-preserve=mode ${BUILD_UPSTREAM}/Optimized_Implementation/sign/${INPARAM}/*/*.{c,h} ${BUILD_CRYPTO_SIGN}/${OUTPARAM}/avx2/
    for F in PQCgenKAT_sign.c debug.h KAT_int.c hash.c KAT_int.h prefix_name.h\
             randombytes_FIPS.c randombytes_FIPS.h randombytes.h rng.c rng.h
    do
      rm -f ${BUILD_CRYPTO_SIGN}/${OUTPARAM}/*/$F
    done
    sed -i -s '/include "KAT_int.h"/d' ${BUILD_CRYPTO_SIGN}/*/*/*.h
  done
done
endtask

task 'Removing ifdefs'
# some useful sed arguments
GRAB=( -e '/\#define/!d' -e '/\#define _.*_H$/d' -e 's/\(define .*\)U$/\1/' )
STRAIGHTEN_IF=( -e :a -e '/#if.*\\$/N; s/\\\n//; ta' )
STRAIGHTEN_DEF=( -e :a -e '/#define.*\\$/N; s/\\\n//; ta' )

UNIFDEFOPTS="-B -k -m \
-D__x86_64__ -U__cplusplus \
-U__AVX2__ -U__AVX__ -U__PCLMUL__ -U__POPCNT__ -U__SSE2__ -U__SSE4_1__ -U__SSE__ -U__SSSE3__ \
-DENABLED_GF2X=0 \
-UKAT_INT -USUPERCOP -UTEST_LIBRARY \
-UBlueGeMSS -UDualModeMS -UFGeMSS -UGeMSS -UMQSOFT_REF -UQUARTZ -UQUARTZ_V1 -URedGeMSS \
-DENABLED_SEED_SK=1 -DGEN_MINUS_VINEGARS=1 -DITOH -DInnerMode -UUNIQUE_ROOT \
-DNB_BITS_UINT=64"

# All of the compilation decisions are set by choice_crypto.h
sed -s -i "${STRAIGHTEN_IF[@]}" ${BUILD_CRYPTO_SIGN}/*/*/choice_crypto.h
unifdef ${UNIFDEFOPTS} -DBlueGeMSS ${BUILD_CRYPTO_SIGN}/gemss-blue-{128,192,256}/*/choice_crypto.h
unifdef ${UNIFDEFOPTS} -DGeMSS ${BUILD_CRYPTO_SIGN}/gemss-{128,192,256}/*/choice_crypto.h
unifdef ${UNIFDEFOPTS} -DRedGeMSS ${BUILD_CRYPTO_SIGN}/gemss-red-{128,192,256}/*/choice_crypto.h

# We'll build without libgf2x
sed -i 's/ENABLED_GF2X 1/ENABLED_GF2X 0/' ${BUILD_CRYPTO_SIGN}/*/*/arch.h

for X in ${BUILD_CRYPTO_SIGN}/*/*/choice_crypto.h
do
  ( cd $(dirname ${X})
  DFILE=$(mktemp)
  PARAM=$(echo ${X} | awk -F/ '{print $(NF-2)}' )
  IMPL=$(echo ${X} | awk -F/ '{print $(NF-1)}' )

  if [ ${IMPL} == "avx2" ]
  then
    UNIFDEFOPTS="${UNIFDEFOPTS} -DENABLED_AVX2 -DENABLED_SSE -DENABLED_POPCNT -DENABLED_PCLMUL \
      -DENABLED_PCLMUL_AVX2 -DENABLED_PCLMUL_SSE2 -DENABLED_AVX -DENABLED_SSE2 \
      -DENABLED_SSE4_1 -DENABLED_SSSE3"
  else
    UNIFDEFOPTS="${UNIFDEFOPTS} -UENABLED_SSE -UENABLED_POPCNT -UENABLED_PCLMUL \
      -UENABLED_PCLMUL_AVX2 -UENABLED_PCLMUL_SSE2 -UENABLED_AVX -UENABLED_SSE2 \
      -UENABLED_SSE4_1 -UENABLED_SSSE3"
  fi

  # Remove line breaks in multi-line #if statements.
  sed -s -i "${STRAIGHTEN_IF[@]}" config_gf2n.h sign_keypairHFE.c rem_gf2n.c rem_gf2n.h

  cat choice_crypto.h | sed "${GRAB[@]}" >> ${DFILE}

  unifdef ${UNIFDEFOPTS} -f ${DFILE} parameters_HFE.h
  cat parameters_HFE.h | sed "${GRAB[@]}" >> ${DFILE}

  unifdef ${UNIFDEFOPTS} -f ${DFILE} arch.h
  cat arch.h | sed "${STRAIGHTEN_DEF[@]}" | sed "${GRAB[@]}" >> ${DFILE}

  unifdef ${UNIFDEFOPTS} -f ${DFILE} chooseRootHFE_gf2nx.h
  cat chooseRootHFE_gf2nx.h | sed "${GRAB[@]}" >> ${DFILE}

  FILE=config_gf2n.h
  unifdef ${UNIFDEFOPTS} -f ${DFILE} ${FILE}
  grep "#define K[123]" ${FILE} | sed "${GRAB[@]}" >> ${DFILE}
  unifdef ${UNIFDEFOPTS} -UK2 -UK3 -f ${DFILE} ${FILE}
  grep "#define __.*NOMIAL_GF2N__" ${FILE} | sed "${GRAB[@]}" >> ${DFILE}
  unifdef ${UNIFDEFOPTS} -U__TRINOMIAL_GF2N__ -U__PENTANOMIAL_GF2N__ -f ${DFILE} ${FILE}
  UNIFDEFOPTS="${UNIFDEFOPTS} -UK2 -UK3 -U__TRINOMIAL_GF2N__ -U__PENTANOMIAL_GF2N__"

  FILE=config_HFE.h
  unifdef ${UNIFDEFOPTS} -f ${DFILE} ${FILE}
  cat ${FILE} | sed "${GRAB[@]}" >> ${DFILE}

  FILE=frobeniusMap_gf2nx.h
  unifdef ${UNIFDEFOPTS} -f ${DFILE} ${FILE}
  grep "#define.*II" ${FILE} | sed "${GRAB[@]}" >> ${DFILE}

  K=$(grep 'define K [0-9]' ${DFILE} | awk '{print $(NF)}')
  N=$(grep 'define HFEn [0-9]' ${DFILE} | awk '{print $(NF)}')
  V=$(grep 'define HFEv [0-9]' ${DFILE} | awk '{print $(NF)}')
  DELTA=$(grep 'define HFEDELTA [0-9]' ${DFILE} | awk '{print $(NF)}')
  HFEDeg=$(grep 'define HFEDeg [0-9]' ${DFILE} | awk '{print $(NF)}')
  HFEDEGI=$(grep 'define HFEDegI [0-9]' ${DFILE} | awk '{print $(NF)}')
  HFEDEGJ=$(grep 'define HFEDegJ [0-9]' ${DFILE} | awk '{print $(NF)}')
  NB_ITE=$(grep 'define NB_ITE [0-9]' ${DFILE} | awk '{print $(NF)}')
  II=$(grep 'define II [0-9]' ${DFILE} | awk '{print $(NF)}')

  # remove unsigned (U) qualifiers
  K=${K}
  N=${N}
  V=${V}
  DELTA=${DELTA}
  HFEDeg=${HFEDeg}
  HFEDegI=${HFEDegI}
  HFEDegJ=${HFEDegJ}

  NR=$((${N}%64))
  NQ=$((${N}/64))
  NB_WORD_MUL=$(((2*(${N}-1))/64+1))
  NB_WORD_MMUL=$(((2*(${N}-1))/64+1))

  VR=$((${V}%64))
  VQ=$((${V}/64))

  M=$((${N}-${DELTA}))
  MR=$((${M}%64))
  MQ=$((${M}/64))
  MR8=$((${M}%8))
  MQ8=$((${M}/8))

  NV=$((${N}+${V}))
  NVR=$((${NV}%64))
  NVQ=$((${NV}/64))

  NB_MONOMIAL_PK=$(((${NV}*(${NV}+1))/2+1))

  HFENq=$((${NB_MONOMIAL_PK}/64))
  HFENq8=$((${NB_MONOMIAL_PK}/8))
  HFENr=$((${NB_MONOMIAL_PK}%64))
  HFENr8=$((${NB_MONOMIAL_PK}%8))
  HFENr8c=$(((8-(${NB_MONOMIAL_PK}%8))%8))

  LOST_BITS=$(((${MR8}-1)*${HFENr8c}))

  NB_WORD_GFqn=${NQ}
  [ ${NR} -ne 0 ] && ((NB_WORD_GFqn+=1))

  NB_WORD_GFqv=${VQ}
  [ ${VR} -ne 0 ] && ((NB_WORD_GFqv+=1))

  NB_WORD_GF2nv=${NVQ}
  [ ${NVR} -ne 0 ] && ((NB_WORD_GF2nv+=1))

  NB_BYTES_GFqm=${MQ8}
  [ ${MR8} -ne 0 ] && ((NB_BYTES_GFqm+=1))

  NB_WORD_GF2m=${MQ}
  [ ${MR} -ne 0 ] && ((NB_WORD_GF2m+=1))

  NB_WORD_GF2nvm=$((${NB_WORD_GF2nv}-${NB_WORD_GF2m}))
  [ ${MR} -ne 0 ] && ((NB_WORD_GF2nvm+=1))

  echo "#define HFENq $((${NB_MONOMIAL_PK}/64))" >> ${DFILE}
  echo "#define HFENq8 $((${NB_MONOMIAL_PK}/8))" >> ${DFILE}
  echo "#define HFENr $((${NB_MONOMIAL_PK}%64))" >> ${DFILE}
  echo "#define HFENr8 $((${NB_MONOMIAL_PK}%8))" >> ${DFILE}
  echo "#define HFENr8c $(((8-${NB_MONOMIAL_PK})%8))" >> ${DFILE}
  echo "#define HFEm ${M}" >> ${DFILE}
  echo "#define HFEmq ${MQ}" >> ${DFILE}
  echo "#define HFEmq8 ${MQ8}" >> ${DFILE}
  echo "#define HFEmr ${MR}" >> ${DFILE}
  echo "#define HFEmr8 ${MR8}" >> ${DFILE}
  echo "#define HFEn ${N}" >> ${DFILE}
  echo "#define HFEnr ${NR}" >> ${DFILE}
  echo "#define HFEnr8 $((${N}%8))" >> ${DFILE}
  echo "#define HFEnv ${NV}" >> ${DFILE}
  echo "#define HFEnvr ${NVR}" >> ${DFILE}
  echo "#define HFEnvr8 $((${NV}%8))" >> ${DFILE}
  echo "#define HFEnvrm1 $(((${NV}-1)%64))" >> ${DFILE}
  echo "#define HFEv ${V}" >> ${DFILE}
  echo "#define HFEvr ${VR}" >> ${DFILE}
  echo "#define HFEvr8 $((${VR}%8))" >> ${DFILE}
  echo "#define KI ${NR}" >> ${DFILE} 
  echo "#define LAST_ROW_Q $(((${NV}-${LOST_BITS})/64))" >> ${DFILE}
  echo "#define LAST_ROW_R $(((${NV}-${LOST_BITS})%64))" >> ${DFILE}
  echo "#define LOST_BITS ${LOST_BITS}" >> ${DFILE}
  echo "#define NB_WHOLE_BLOCKS $(((${NV}-(64-((${NB_MONOMIAL_PK}-${LOST_BITS}-${NVR})%64))%64)>>6))" >> ${DFILE}
  echo "#define NB_WORD_GF2m ${NB_WORD_GF2m}" >> ${DFILE}
  echo "#define NB_WORD_GF2m_TMP ${NB_WORD_GF2m}" >> ${DFILE}
  echo "#define NB_WORD_GF2nv ${NB_WORD_GF2nv}" >> ${DFILE}
  echo "#define NB_WORD_GF2nv_TMP ${NB_WORD_GF2nv}" >> ${DFILE}
  echo "#define NB_WORD_GF2nvm ${NB_WORD_GF2nvm}" >> ${DFILE}
  echo "#define NB_WORD_GFqn ${NB_WORD_GFqn}" >> ${DFILE}
  echo "#define NB_WORD_GFqn_TMP ${NB_WORD_GFqn}" >> ${DFILE}
  echo "#define NB_WORD_GFqv ${NB_WORD_GFqv}" >> ${DFILE}
  echo "#define NB_WORD_GFqv_TMP ${NB_WORD_GFqv}" >> ${DFILE}
  echo "#define NB_WORD_MMUL ${NB_WORD_MMUL}" >> ${DFILE}
  echo "#define NB_WORD_MMUL_TMP ${NB_WORD_MMUL}" >> ${DFILE}
  echo "#define NB_WORD_MUL ${NB_WORD_MUL}" >> ${DFILE}
  echo "#define REM_MACRO 0" >> ${DFILE}
  echo "#define SIZE_ALIGNED_GFqm 0" >> ${DFILE}
  echo "#define SIZE_ALIGNED_GFqn 0" >> ${DFILE}

  FILE=gf2nx.h
  sed -i "s/(HFEDeg&1U\?)/($((${HFEDeg}%2)))/" ${FILE}
  unifdef ${UNIFDEFOPTS} -f ${DFILE} ${FILE}
  grep 'define ENABLED_REMOVE_ODD_DEGREE' ${FILE} >> ${DFILE}

  # Done extracting defines. Do a full pass to simplify later work.

  unifdef ${UNIFDEFOPTS} -f ${DFILE} *.{c,h}

  # Clean up some arithmetic that unifdef cannot handle.

  FILE=chooseRootHFE_gf2nx.h
  sed -i 's/FIRST_ROOT+DETERMINIST_ROOT+QUARTZ_ROOT/1/' ${FILE}

  FILE=bit.h
  sed -i 's/if (NB_BITS_UINT==64U)/if (1)/' ${FILE}

  FILE=convMQ_gf2.c
  VAL=$((((${NB_MONOMIAL_PK}-${LOST_BITS}+7)/8)%8))
  sed -i "s/((NB_MONOMIAL_PK-LOST_BITS+7)>>3)&7/${VAL}/" ${FILE}

  FILE=evalMQSv_gf2.c
  NB_WORD_EQ=${NQ}
  [ ${NR} -ne 0 ] && ((NB_WORD_EQ+=1))
  unifdef ${UNIFDEFOPTS} -DNB_VAR=${V} -DNB_VARq=${VQ} -DNB_VARr=${VR} -DNB_EQr=${NR}\
          -DNB_WORD_EQ_TMP=${NB_WORD_EQ} -DNB_WORD_EQ=${NB_WORD_EQ}\
          -DHYBRID_FUNCTIONS=0\
          -f ${DFILE} ${FILE}

  FILE=evalMQSnocst8_gf2.c
  NB_BYTES_EQ=${MQ8}
  [ ${MR} -ne 0 ] && ((NB_BYTES_EQ+=1))
  NB_WORD_EQ_NOCST8=$(((${NB_BYTES_EQ}+7)/8))
  LEN_UNROLLED_64=$(grep 'define LEN_UNROLLED_64' evalMQSnocst8_gf2.c | awk '{print $(NF)}')
  sed -i "s/NB_EQ&63/${MR}/" ${FILE}
  sed -i "s/LEN_UNROLLED_64<<1/$((${LEN_UNROLLED_64}*2))/" evalMQSnocst8_gf2.c
  unifdef ${UNIFDEFOPTS} -DNB_VAR=${NV} -DNB_VARq=${NVQ} -DNB_VARr=${NVR} -DNB_EQr=${MR}\
          -DNB_BYTES_EQ=${NB_BYTES_EQ} -DNB_WORD_EQ=$((NB_WORD_EQ_NOCST8))\
          -DLEN_UNROLLED_64=${LEN_UNROLLED_64}\
          -f ${DFILE} ${FILE}

  FILE=evalMQSnocst8_quo_gf2.c
  [ ${MQ8} == 0 ] && NB_EQ=${M} || NB_EQ=$((8*${MQ8}))
  NB_EQR=$((${NB_EQ}%8))
  NB_BYTES_EQ=$((${NB_EQ}/8))
  [ ${NB_EQR} -ne 0 ] && ((NB_BYTES_EQ+=1))
  NB_WORD_EQ=$(((${NB_BYTES_EQ}+7)/8))
  sed -i "s/NB_EQ&63/$((${NB_EQ}%64))/" ${FILE}
  LEN_UNROLLED_64=$(grep 'define LEN_UNROLLED_64' ${FILE} | awk '{print $(NF)}')
  sed -i "s/LEN_UNROLLED_64<<1/$((${LEN_UNROLLED_64}*2))/" ${FILE}
  unifdef ${UNIFDEFOPTS} -DNB_VAR=${NV} -DNB_VARq=${NVQ} -DNB_VARr=${NVR}\
          -DNB_EQq_orig=${MQ8} -DNB_EQr=$((${NB_EQ}%8)) \
          -DNB_BYTES_EQ=${NB_BYTES_EQ} -DNB_WORD_EQ=${NB_WORD_EQ} \
          -DLEN_UNROLLED_64=${LEN_UNROLLED_64} \
          -f ${DFILE} ${FILE}

  FILE=frobeniusMap_gf2nx.c
  [ ${IMPL} == "avx2" ] &&
    sed -i "s/(HFEn-HFEDegI)%II/$(((${N} - ${HFEDEGI})%${II}))/" ${FILE}

  FILE=inv_gf2n.c
  sed -i "s/HFEn&63/$((${N}%64))/" ${FILE}

  FILE=mixEquationsMQS_gf2.c
  sed -i "s/NB_BYTES_GFqm&7/$((${NB_BYTES_GFqm}%8))/" ${FILE}

  FILE=parameters_HFE.h
  sed -i "s/K<<1/$((2*${K}))/" ${FILE}
  sed -i "s/(1U<<HFEDegI)+(1U<<HFEDegJ)/$((2**${HFEDEGI} + 2**${HFEDEGJ}))/" ${FILE}
  sed -i "s/HFEn-1/$((${N}-1))/" ${FILE}

  FILE=rem_gf2n.c
  K3=$(grep 'define K3 [0-9]' ${DFILE} | awk '{print $(NF)}')
  sed -i "s/(HFEn-2+K3)&1/$(((${N}+${K3}-2)%2))/" ${FILE}
  sed -i "s/(NB_WORD_MMUL&1)/$((${NB_WORD_MMUL}%2))/" ${FILE}

  FILE=signHFE.c
  sed -i "s/HFEDELTA+HFEv/$((${DELTA}+${V}))/" ${FILE}
  sed -i "s/(HFEm&7)/(${MR8})/" ${FILE}
  sed -i "s/HFEn&7/$((${N}%8))/" ${FILE}
  sed -i "s/NB_WORD_GFqn+NB_WORD_GFqv/$((${NB_WORD_GFqn}+${NB_WORD_GFqv}))/" ${FILE}

  FILE=sign_openHFE.c
  sed -i "s/HFEDELTA+HFEv/$((${DELTA}+${V}))/" ${FILE}
  sed -i "s/HFEm&7/${MR8}/" ${FILE}

  FILE=sqr_gf2n.c
  sed -i "s/NB_WORD_MUL&1/$((${NB_WORD_MUL}%2))/" ${FILE}

  FILE=tools_gf2m.h
  sed -i "s/NB_WORD_GF2m&3/$((${NB_WORD_GF2m}%4))/" ${FILE}
  sed -i "s/NB_WORD_GF2m&1/$((${NB_WORD_GF2m}%2))/" ${FILE}

  FILE=tools_gf2n.h
  sed -i "s/NB_WORD_GFqn&3/$((${NB_WORD_GFqn}%4))/" ${FILE}
  sed -i "s/NB_WORD_GFqn&1/$((${NB_WORD_GFqn}%2))/" ${FILE}
  sed -i "s/HFEn%NB_BITS_UINT/$((${N}%64))/" ${FILE}

  # final pass
  unifdef ${UNIFDEFOPTS} -f ${DFILE} *.{c,h}

  rm ${DFILE}

  # Write api.h while we have all of the information we need
  SIZE_SK=$((${K}/8))
  SIZE_PK=$(((${NB_MONOMIAL_PK}*${M}+7)/8))
  SIZE_SIGN=$(((${NV}+(${NB_ITE}-1)*(${NV}-${M})+7)/8))
  echo "\
#ifndef API_H
#define API_H

#include <stddef.h>
#include <stdint.h>

#define CRYPTO_ALGNAME                      \"${PARAM}\"

#define CRYPTO_SECRETKEYBYTES               ${SIZE_SK}
#define CRYPTO_PUBLICKEYBYTES               ${SIZE_PK}
#define CRYPTO_BYTES                        ${SIZE_SIGN}

int crypto_sign_keypair(uint8_t *pk, uint8_t *sk);
int crypto_sign(uint8_t *sm, size_t *smlen, const uint8_t *msg, size_t len, const uint8_t *sk);
int crypto_sign_open(uint8_t *m, size_t *mlen, const uint8_t *sm, size_t smlen, const uint8_t *pk);
int crypto_sign_signature(uint8_t *sig, size_t *siglen, const uint8_t *m, size_t mlen, const uint8_t *sk);
int crypto_sign_verify(const uint8_t *sig, size_t siglen, const uint8_t *m, size_t mlen, const uint8_t *pk);

#endif
" > api.h
)
done
endtask

task 'Sorting #includes'
for PARAM in gemss-{,blue-,red-}{128,192,256}
do
  for IMPL in clean avx2
  do
    for F in ${BUILD_CRYPTO_SIGN}/${PARAM}/${IMPL}/*.h
    do
      START=$(grep -n -m 1 '^#include' ${F} | cut -d: -f1)
      if [ x${START} == x ]; then continue; fi
      GUARD=$(head -n $((${START}-1)) ${F})
      INCL1=$(grep '^#include \"' ${F} | sort -u)
      INCL2=$(grep '^#include <' ${F} | sort -u)
      REST=$(tail -n+$((${START}+1)) ${F} | sed '/^#include/d')
      echo "${GUARD}\n${INCL1}\n${INCL2}\n${REST}" | sed 's/\\n/\n/g' > ${F}
    done
    for F in ${BUILD_CRYPTO_SIGN}/${PARAM}/${IMPL}/*.c
    do
      INCL1=$(grep '^#include \"' ${F} | sort -u)
      INCL2=$(grep '^#include <' ${F} | sort -u)
      REST=$(sed '/^#include/d' ${F})
      echo "${INCL1}\n${INCL2}\n${REST}" | sed 's/\\n/\n/g' > ${F}
    done
  done
done
endtask

#MANIFEST=${BUILD_TEST}/duplicate_consistency
#mkdir -p ${MANIFEST}
#task "Preparing for duplicate consistency"
#( cd ${MANIFEST}
#for P1 in gemss-{,blue-,red-}{128,192,256}
#do
#  for OUT in clean avx2
#  do
#    sha1sum ${BUILD_CRYPTO_SIGN}/${P1}/${OUT}/*.{h,c} > ${P1}_${OUT}.xxx
#  done
#done
#)
#endtask
#
#( cd ${MANIFEST}
#for P1 in gemss-{,blue-,red-}{128,192,256}
#do
#  for OUT in clean avx2
#  do
#    task "${P1}/${OUT} duplicate consistency"
#    echo "\
#consistency_checks:" > ${P1}_${OUT}.yml
#    for P2 in gemss-{,blue-,red-}{128,192,256}
#    do
#      for IN in clean avx2
#      do
#        if ([ "${P1}" == "${P2}" ] && [ "${IN}" == "${OUT}" ]) || [ "${P1}" \> "${P2}" ]; then continue; fi
#        echo "\
#- source:
#    scheme: ${P2}
#    implementation: ${IN}
#  files:" >> ${P1}_${OUT}.yml
#        for HASH in $(cat ${P2}_${IN}.xxx | cut -d ' ' -f 1)
#        do
#          X=$(grep $HASH ${P1}_${OUT}.xxx | cut -d ' ' -f 3)
#          if [ x${X} != 'x' ]
#          then
#            [ -e ${BUILD_CRYPTO_SIGN}/${P2}/${OUT}/$(basename $X) ] && \
#            echo "\
#      - $(basename $X)" >> ${P1}_${OUT}.yml
#          fi
#        done
#      done
#    done
#    endtask
#  done
#done
#)
#rm -rf ${MANIFEST}/*.xxx


task 'Namespacing' 
# XXX: figure out how to preserve define formatting.
sed -s -i "${STRAIGHTEN_DEF[@]}" ${BUILD_CRYPTO_SIGN}/*/*/*.h

# Fixup a few definitions
#sed -i -s 's/#define.*void\(.*\)/void \1;/' ${BUILD_CRYPTO_SIGN}/*/*/{sqr_gf2n.h,mul_gf2n.h}
#sed -i '/MUL_THEN_REM_GF2N;/d' ${BUILD_CRYPTO_SIGN}/*/*/mul_gf2n.h
#sed -i '/SQR_THEN_REM_GF2N;/d' ${BUILD_CRYPTO_SIGN}/*/*/sqr_gf2n.h
#sed -i '/SQR_NOCST_THEN_REM_GF2N;/d' ${BUILD_CRYPTO_SIGN}/*/*/sqr_gf2n.h

# GeMSS has its own namespacing macro. We'll delete it and do it our way.
sed -i -s '/include "prefix_name.h"/d' ${BUILD_CRYPTO_SIGN}/*/*/*.h
sed -i -s 's/^\s*\(int\|void\|gf2\|UINT\|uint64_t\|unsigned int\)\s\+PREFIX_NAME(\([^)]*\))/\1 \2/' ${BUILD_CRYPTO_SIGN}/*/*/*.{h,c}

# Insert hooks for namespacing. These will be removed later.
sed -i -s 's/^\s*\(int\|void\|gf2\|UINT\|uint64_t\|unsigned int\)\s\+\([^(]*\)(/#define \2 CRYPTO_NAMESPACE(\2)\n&/' ${BUILD_CRYPTO_SIGN}/*/*/*.h
sed -i -s '/#define.*PREFIX_NAME/d' ${BUILD_CRYPTO_SIGN}/*/*/*.h

for PARAM in gemss-{,blue-,red-}{128,192,256}
do
  for IMPL in clean avx2
  do
    ( cd ${BUILD_CRYPTO_SIGN}/${PARAM}/${IMPL}
    NAMESPACE=$(echo PQCLEAN_${PARAM//-/}_${IMPL} | tr [:lower:] [:upper:])
    for X in $(grep CRYPTO_NAMESPACE *.{c,h} | cut -f2 -d' ' | sort -u); do
      sed -i -s "s/\([^a-zA-Z_]\)${X}\([^a-zA-Z\._]\|$\)/\1${NAMESPACE}_${X}\2/g" *.c *.h
    done
    sed -i -s '/CRYPTO_NAMESPACE/d' *.{c,h}
    sed -i -s "s/CRYPTO_/${NAMESPACE}_CRYPTO_/" *.{c,h}
    sed -i "s/API_H/${NAMESPACE}_API_H/" api.h

    sed -i -s "s/f_/${NAMESPACE}_/" tools_gf2n.h
    )
  done
done
endtask

task 'Copying metadata'
# Makefiles and other metadata
for PARAM in gemss-{,blue-,red-}{128,192,256}
do
  ( cd ${BUILD_CRYPTO_SIGN}/${PARAM}/

  echo "Public Domain" > clean/LICENSE
  cp -Lp clean/LICENSE avx2/LICENSE
  cp -Lp ${BASE}/meta/crypto_sign_${PARAM}_META.yml META.yml
  echo "\
principal-submitters:
  - people
implementations:
    - name: clean
      version: ${VERSION}
    - name: avx2
      version: ${VERSION}
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

CFLAGS=-O3 -mavx2 -mbmi -mpclmul -Wall -Wextra -Wpedantic -Wvla -Werror -Wredundant-decls -Wmissing-prototypes -std=c99 -I../../../common \$(EXTRAFLAGS)

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
  ${BUILD_CRYPTO_SIGN}/*/*/*.{c,h} >/dev/null
endtask

# Package
task "Packaging pqclean-gemss-$(date +"%Y%m%d").tar.gz"
tar czf ${BASE}/pqclean-gemss-$(date +"%Y%m%d").tar.gz -C ${BUILD} crypto_sign test
endtask

