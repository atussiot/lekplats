#!/bin/sh

set -e

START_TIME=$(date +%s)
BUILD_DIR="build"

if [[ -d $BUILD_DIR ]]; then
    echo "Clearing build directory..."
    rm -rf $BUILD_DIR
fi

echo " "
cppcheck -q --enable=all .
echo " "
cloc .
echo " "

mkdir build

pushd $BUILD_DIR >/dev/null

# Build all the things
cmake .. -G Ninja
ninja

# Test and run all the things
./tests_unit -c
./lekplats

popd $BUILD_DIR >/dev/null

END_TIME=$(date +%s)
echo "Executed all in $(($END_TIME - $START_TIME)) seconds"
echo "All good this time, bye bye"
