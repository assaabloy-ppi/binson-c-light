#!/bin/bash
mkdir ./build

CFLAGS="-g -O0 -std=c99 -Wall"

# use next for release builds
#CFLAGS="-Os -std=c99 -flto -fpack-struct -ffreestanding -ffunction-sections -fdata-sections -funsigned-char -funsigned-bitfields -Wl,--gc-sections  -Wall -W -Wextra -pedantic"  

gcc -I. $CFLAGS -DWITH_TO_STRING  binson_light.c binson_light_test.c  -o build/binson_light_test
gcc -I. $CFLAGS  binson_light.c binson_light_examples.c  -o build/binson_light_examples
#gcc -I. $CFLAGS  binson_light.c binson_light_to_string.c binson_light_to_string_examples.c -o build/binson_light_to_string_examples
gcc -I. $CFLAGS -DWITH_TO_STRING binson_light.c  binson_light_to_string_examples.c -o build/binson_light_to_string_examples

gcc -I. $CFLAGS  binson_light.c bug_6.c  -o build/bug_6

#gcc -I. $CFLAGS  binson_light.c bug_2.c  -o build/bug_2
#gcc -I. $CFLAGS  binson_light.c bug_2.c  -o build/bug_2
#gcc -I. $CFLAGS  binson_light.c bug_2.c  -o build/bug_2

