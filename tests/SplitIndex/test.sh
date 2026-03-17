#!/bin/bash

# change to the directory of the script
cd $( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
# change to project directory
cd ../..

./build/fqtools split-index -R1 tests/SplitIndex/R1.fq -R2 tests/SplitIndex/R2.fq -delimiter " "
