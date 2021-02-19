#! /bin/bash

rm -rf build

cmake . -B build -DCMAKE_BUILD_TYPE=debug

#make -C build -j8


