#!/bin/bash

rm -fr build
mkdir build
cmake -B build
cmake --build build
./build/Downloads-Sort