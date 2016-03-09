#!/bin/bash
mkdir ./build

CFLAGS="-g -Og -std=c99 -Wall -W -Wextra -pedantic"

# use next for release builds
#CFLAGS="-Os -std=c99 -flto -fpack-struct -ffreestanding -ffunction-sections -fdata-sections -funsigned-char -funsigned-bitfields -Wl,--gc-sections  -Wall -W -Wextra -pedantic"  

gcc -I. $CFLAGS  binson_light.c binson_light_test.c  -o build/binson_light_test
gcc -I. $CFLAGS  binson_light.c binson_light_examples.c  -o build/binson_light_examples
