#!/bin/sh
if [ "$#" -gt 0 ]; then
    TIS_INTERPRETER=$1
else
    TIS_INTERPRETER=$(find / -name 'tis-interpreter.sh' 2> /dev/null | sort | tail -1)
fi

if ! $TIS_INTERPRETER --version > /dev/null; then
    echo "Tis interpreter does not seems to work."
    exit 1
fi

echo "Using tis-interpreter $TIS_INTERPRETER"

echo "Analysing own written unit test cases:"
for file in $(ls utest/*.c);
do
    echo "tis-interpreter analyzing file: $file"
    if ! $TIS_INTERPRETER binson_parser.c binson_writer.c $file --cc "-I." > /dev/null; then
        echo "File $file had some problems:"
        $TIS_INTERPRETER binson_parser.c binson_writer.c $file --cc "-I."
        exit 1
    fi
done


for file in $(find utest/generated_test_cases -type f -name '*.c');
do
    echo "tis-interpreter analyzing file: $file"
    if ! $TIS_INTERPRETER binson_parser.c binson_writer.c $file --cc "-I." > /dev/null; then
        echo "File $file had some problems:"
        $TIS_INTERPRETER binson_parser.c binson_writer.c $file --cc "-I."
        exit 1
    fi
done

exit 0