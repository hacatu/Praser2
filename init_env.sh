#!/bin/sh
export BUILD_ROOT=`pwd`
export GCOV_PREFIX=$BUILD_ROOT/notes
export GCOV_PREFIX_STRIP=$((`echo $GCOV_PREFIX|tr -cd '/' | wc -c`*2+6))
echo CONFIG_BUILD_ROOT=$BUILD_ROOT > tup.config

