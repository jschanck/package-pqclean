PYTHON=/usr/bin/python3

BASE=`dirname $0`
BASE=`cd ${BASE} && pwd`

VERSION=$(cat ${BASE}/VERSION)
V1=upstream
V2=upstream-patched

ARCHIVE=hqc-submission_${VERSION}.zip

PATCHES=${BASE}/patches
SCRIPTS=${BASE}/scripts

cd ${BASE}

if [ -e "${V1}" ]
then
  read -p "${V1} directory already exists. Delete it? " yn
  if [ "${yn:-n}" != "y" ]
  then
    exit -1
  fi
  rm -rf ${V1}
fi

if [ -e "${V2}" ]
then
  read -p "${V2} directory already exists. Delete it? " yn
  if [ "${yn:-n}" != "y" ]
  then
    exit -1
  fi
  rm -rf ${V2}
fi

mkdir -p ${V1}
mkdir -p ${V2}


if [ ! -f ${BASE}/${ARCHIVE} ]
then
  wget -P ${BASE} https://pqc-hqc.org/doc/${ARCHIVE}
fi
unzip -qq -d ${BASE}/${V1}/ ${BASE}/${ARCHIVE}

for IMPL in Reference_Implementation Optimized_Implementation
do
  for K in 128 192 256
  do
    mv ${V1}/${IMPL}/hqc-${K} ${V1}/${IMPL}/hqc-rmrs-${K}
  done
done

cp -rp ${V1}/* ${V2}

( cd ${V2}
for X in ${PATCHES}/*
do
  patch -N -p1 < ${X}
done
)
