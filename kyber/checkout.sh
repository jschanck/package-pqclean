PYTHON=/usr/bin/python3

BASE=`dirname $0`
BASE=`cd ${BASE} && pwd`

VERSION=$(cat ${BASE}/VERSION)
V1=upstream
V2=upstream-patched

ARCHIVE=${VERSION}.zip

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

if [ ! -f ${BASE}/${ARCHIVE} ]
then
  wget -P ${BASE} https://github.com/pq-crystals/kyber/archive/${VERSION}.zip
fi
unzip -qq -d ${BASE} ${BASE}/${ARCHIVE}
mv kyber-${VERSION} ${V1}
mkdir -p ${V2}

cp -rp ${V1}/* ${V2}

( cd ${V2}
for X in ${PATCHES}/*
do
  patch -p1 < ${X}
done
)
