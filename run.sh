#!/bin/bash

set -e 

clear 
g++ main.cpp -o build/tracer  --std=c++23
./build/tracer 
feh build/image.ppm
