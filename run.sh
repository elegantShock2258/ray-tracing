#!/bin/bash

set -e 

clear 
g++ main.cpp -o build/tracer 
./build/tracer 
feh build/image.ppm
