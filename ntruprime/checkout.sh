#!/bin/sh

BASE=$(dirname "${0}")
BASE=$(cd "${BASE}" && pwd)

VERSION=$(cat "${BASE}"/VERSION)
V1=upstream
V2=upstream-patched

ARCHIVE="${VERSION}".tar.xz
PATCHES="${BASE}"/patches

cd "${BASE}" || exit

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
