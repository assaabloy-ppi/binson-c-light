#!/bin/sh

#    find $output_dir -type f -exec sh -c "cat {} | ./$debug_build_dir/$target > /dev/null && echo \"Return with 0: {}\"" \;

mkdir -p generated_test_cases
mkdir -p generated_test_cases/writer
mkdir -p generated_test_cases/parser

if ./$1 < $2; then
    echo "Returned 0 with file $2"
    if java -cp binson-3.2.jar org.binson.PrintBinsonFile $2; then
        echo "Java returned 0 with file $2"
        echo $2 >> passed.txt
        filename=$(md5sum -b $2 | awk '{print $1}')".c"
        java -cp binson-3.2.jar org.binson.JavaToCWriter $2 > generated_test_cases/writer/w_$filename
        java -cp binson-3.2.jar org.binson.JavaToCParser $2 > generated_test_cases/parser/p_$filename
        exit 0
    else
        echo "Java dit not return 0 with file $2"
        exit 1
    fi
else
    echo "Returned non 0 with file $2"
fi

exit 0
