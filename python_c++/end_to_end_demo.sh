#!/bin/sh

set -eu

scripts=$(cd `dirname $0`; pwd)
cd $scripts


sh compile.sh

clear
echo ''
echo "Using C++ search_helper.C extension"
python searcher.py

rm -rf search_helper.so

echo ''
echo "Using Python search_helper.py extension, without C++"
python searcher.py
