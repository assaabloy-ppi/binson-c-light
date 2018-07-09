#!/bin/sh

dirs="fuzz_parser_verify fuzz_defined fuzz_goinoutobj fuzz_goinoutarr"
for dir in $dirs;
do
    echo "Processing output from $dir"
    files=$(find output/$dir/queue_all -type f -name 'id:*')
    tot=$(ls output/$dir/queue_all | wc -l)
    i=0
    for file in $files;
    do
        filename=$(md5sum -b $file | awk '{print $1}')
        if build_debug/fuzz_parser_verify < $file > /dev/null ; then
            sh verify_with_binson_java.sh build_debug/fuzz_parser_verify $file > /dev/null
            cp $file ../utest/test_data/valid_objects/$filename
        else
            cp $file ../utest/test_data/bad_objects/$filename
        fi
        printf "\r$i/$tot  "
        i=$((i+1))
    done
    printf "\n"
done


