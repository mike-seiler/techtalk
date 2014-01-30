#!/bin/sh
set -eu
scripts=$(dirname $0)

g++ -std=c++11 $scripts/pycounter.C -O3 -I/usr/include/python2.7 -I/usr/local/include/boost/python -lboost_python -o $scripts/counter.so -shared -fPIC -march=native 
