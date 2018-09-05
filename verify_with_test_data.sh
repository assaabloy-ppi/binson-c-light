#!/bin/sh

for file in $(find utest/test_data/valid_objects -type f);
do
    if ! ./fuzz-test/fuzz_parser_verify < $file > /dev/null; then
        echo "Valid object file $file failed."
        exit 1
    fi
done

for file in $(find utest/test_data/bad_objects -type f);
do
    if ./fuzz-test/fuzz_parser_verify < $file > /dev/null; then
        echo "Invalid objectfile $file failed."
        exit 1
    fi
done

exit 0
