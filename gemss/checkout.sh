PYTHON=/usr/bin/python3

BASE=`dirname $0`
BASE=`cd ${BASE} && pwd`

VERSION=$(cat ${BASE}/VERSION)
V1=upstream
V2=upstream-patched

ARCHIVE=${VERSION/.a/.zip}

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
  wget -P ${BASE} http://www-polsys.lip6.fr/~ryckeghem/packages/${ARCHIVE}
fi
unzip -qq -d ${BASE} ${BASE}/${ARCHIVE}

mv ${VERSION} ${V1}
mkdir -p ${V2}


# De-duplicate files with symlinks. All patches are applied to
# Reference_Implementation/GeMSS-128 and Optimized_Implementation/GeMSS-128

( cd ${V1}/Reference_Implementation/sign/
for X in */*/*
do
  IFS=/ read PARAM SUBDIR FILE <<< $X
  if [ ${PARAM} == 'GeMSS128' ]; then continue; fi 
  if [ ${FILE} == 'choice_crypto.h' ]; then continue; fi 
  ln -sf ../../GeMSS128/${SUBDIR}/${FILE} ${PARAM}/${SUBDIR}/${FILE}
done
)

cp -rp ${V1}/* ${V2}

( cd ${V2}
for X in ${PATCHES}/*
do
  patch -p1 < ${X}
done
)
