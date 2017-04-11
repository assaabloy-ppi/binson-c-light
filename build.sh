#!/bin/bash
mkdir ./build

CFLAGS="-g -Os -std=c99 -Wall"

# use next for release builds
#CFLAGS="-Os -std=c99 -flto -fpack-struct -ffreestanding -ffunction-sections -fdata-sections -funsigned-char -funsigned-bitfields -Wl,--gc-sections  -Wall -W -Wextra -pedantic"  

gcc -I. $CFLAGS  binson_light.c binson_light_test.c  -o build/binson_light_test
gcc -I. $CFLAGS  binson_light.c binson_light_examples.c  -o build/binson_light_examples
gcc -I. $CFLAGS  binson_light.c binson_light_to_string.c binson_light_to_string_examples.c -o build/binson_light_to_string_examples

#gcc -I. $CFLAGS  binson_light.c bug_3.c  -o build/bug_3

#gcc -I. $CFLAGS  binson_light.c bug_2.c  -o build/bug_2
#gcc -I. $CFLAGS  binson_light.c bug_2.c  -o build/bug_2
#gcc -I. $CFLAGS  binson_light.c bug_2.c  -o build/bug_2

