#!/bin/sh

for executable in fuzz_parser_verify fuzz_defined fuzz_goinoutobj fuzz_goinoutarr;
do
    echo "Dry running $executable with output from fuzz-tests"
    for file in $(find utest/test_data -type f);
    do
        ./r_$executable < $file > /dev/null
    done

done
