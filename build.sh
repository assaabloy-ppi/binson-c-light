#!/bin/bash

mkdir -p DebugSan
cd DebugSan
cmake -DCMAKE_BUILD_TYPE=Debug -DSANITIZE_ADDRESS=On -DSANITIZE_UNDEFINED=On ..
make -j8
ctest -j8

cd ..

for executable in fuzz_parser_verify fuzz_defined fuzz_goinoutobj fuzz_goinoutarr;
do
    echo "Dry running $executable with output from fuzz-tests"
    for file in $(find utest/test_data -type f);
    do
        ./DebugSan/fuzz-test/$executable < $file > /dev/null
    done

done

for file in $(find utest/test_data/valid_objects -type f);
do
    if ! ./DebugSan/fuzz-test/fuzz_parser_verify < $file > /dev/null; then
        echo "Valid object file $file failed."
        exit 1
    fi
done

for file in $(find utest/test_data/bad_objects -type f);
do
    if ./DebugSan/fuzz-test/fuzz_parser_verify < $file > /dev/null; then
        echo "Invalid objectfile $file failed."
        exit 1
    fi
done

mkdir -p coverage
lcov -b . \
    -d DebugSan/CMakeFiles/binson_parser.dir \
    -d DebugSan/CMakeFiles/binson_writer.dir \
    -d DebugSan/CMakeFiles/binson_class.dir \
    --no-recursion \
    --no-external \
    --capture --output-file coverage/coverage.info
genhtml -o coverage coverage/coverage.info

printf "Coverage report in $(pwd)/coverage/index.html\n"

exit 0
