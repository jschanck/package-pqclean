VERSION=$(cat VERSION)

PYTHON=/usr/bin/python3

WORKDIR=`dirname $0`
WORKDIR=`cd ${WORKDIR} && pwd`
PATCHES=${WORKDIR}/patches
SCRIPTS=${WORKDIR}/scripts

ARCHIVE=${VERSION}.tar.xz

cd ${WORKDIR}


if [ ! -e "${V1}" ]
then
  if [ ! -f ${ARCHIVE} ]
  then
    wget https://bench.cr.yp.to/supercop/${ARCHIVE}
  fi
  unxz < ${ARCHIVE} | tar --transform="s!${VERSION}!${V1}!" -xf -
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

cp -rp ${V1} ${V2}
( cd ${V2}
for X in ${PATCHES}/*
do
  patch -p1 < ${X}
done
)
