#!/bin/bash -e

PKG=$1

if [ ! -f "$1" ]; then
    echo -e "\e[1;31mError: build script '$1' not found!\e[0m"
    exit 1
fi

$1

exit $RET_CODE
