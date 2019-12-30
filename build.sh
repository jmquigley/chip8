#!/bin/env bash

cppcheck -q -ibuild -iroms -i.git .

if [ ! -z $DEBUG ]; then
    echo "Building DEBUG version"
    cmake -DCMAKE_BUILD_TYPE=Debug -B build .
else
    echo "Building RELEASE version"
    cmake -DCMAKE_BUILD_TYPE=Release -B build .
fi

pushd build
make -j 10
popd
