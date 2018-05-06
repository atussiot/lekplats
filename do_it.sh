#!/bin/sh

set -e

BUILD_DIR="build"

if [[ -d $BUILD_DIR ]]; then
    echo "Clearing build directory..."
    rm -rf $BUILD_DIR
fi

echo " "
cppcheck -q --enable=all .
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

echo "All good this time, bye bye"
