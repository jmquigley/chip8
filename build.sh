#!/bin/env bash

cppcheck -q -ibuild -iroms -i.git .
cmake -B build .
pushd build
make -j 10
popd
