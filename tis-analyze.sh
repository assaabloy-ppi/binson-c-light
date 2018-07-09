#!/bin/sh

echo "Analysing own written unit test cases:"
for file in $(ls utest/*.c);
do
    /home/developer/tis-interpreter/tis-interpreter.sh binson_parser.c binson_writer.c $file --cc "-I."
done


for file in $(find utest/generated_test_cases -type f -name '*.c');
do
    echo "tis-interpreter analyzing file: $file"
    out=$(/home/developer/tis-interpreter/tis-interpreter.sh binson_parser.c binson_writer.c $file --cc "-I." | wc -l)
    if [ $out != "4" ]; then
        echo "File $file had some problems:"
        /home/developer/tis-interpreter/tis-interpreter.sh binson_parser.c binson_writer.c $file --cc "-I."
        exit 1
    fi
done

exit 0