#!/bin/bash

mkdir -p DebugSan
cd DebugSan
cmake -DCMAKE_BUILD_TYPE=Debug -DSANITIZE_ADDRESS=On -DSANITIZE_UNDEFINED=On ..
make -j8
ctest -j8

for executable in fuzz_parser_verify fuzz_defined fuzz_goinoutobj fuzz_goinoutarr;
do
    echo "Dry running $executable with output from fuzz-tests"
    for file in $(find utest/test_data -type f);
    do
        ./DebugSan/r_$executable < $file > /dev/null
    done

done

mkdir -p coverage
lcov --base-directory . \
    --directory . \
    --capture --output-file coverage/coverage.info
genhtml -o coverage coverage/coverage.info
printf "Coverage report in $(pwd)/coverage/index.html\n"
