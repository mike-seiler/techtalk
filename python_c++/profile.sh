#!/bin/sh

python searcher.py profile

python ../gprof2dot.py -fpstats profile.out | dot -Tpng -o searcher.profile.png
python ../gprof2dot.py -e .05 -n .01 -fpstats profile.out | dot -Tpng -o searcher.profile.detailed.png




