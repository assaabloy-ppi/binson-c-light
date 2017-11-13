#!/bin/bash
mkdir -p ./build

#CFLAGS="-g -O0 -std=c99 -Wall"
CFLAGS="-std=c99 -Wall"

# use next for release builds
#CFLAGS="-Os -std=c99 -flto -fpack-struct -ffreestanding -ffunction-sections -fdata-sections -funsigned-char -funsigned-bitfields -Wl,--gc-sections  -Wall -W -Wextra -pedantic"  

gcc -I. $CFLAGS -DWITH_TO_STRING  binson_light.c binson_light_test.c  -o build/binson_light_test
gcc -I. $CFLAGS -DTEST_STREAM_MAIN -DABORT_ON_DIFF binson_light.c binson_light_test_stream.c  -o build/binson_light_test_stream

#gcc -I. $CFLAGS  binson_light.c binson_light_examples.c  -o build/binson_light_examples
#gcc -I. $CFLAGS  binson_light.c binson_light_to_string.c binson_light_to_string_examples.c -o build/binson_light_to_string_examples
#gcc -I. $CFLAGS -DWITH_TO_STRING binson_light.c  binson_light_to_string_examples.c -o build/binson_light_to_string_examples

gcc -I. $CFLAGS  binson_light.c bug_6.c  -o build/bug_6
gcc -I. $CFLAGS  binson_light.c bug_14.c  -o build/bug_14
gcc -I. $CFLAGS  binson_light.c bug_14_2.c  -o build/bug_14_2
gcc -I. $CFLAGS  binson_light.c bug_15.c  -o build/bug_15

ARM_CFLAGS="-std=c99 -Wall -fpack-struct -ffreestanding -funsigned-char"
ARM_CMDARGS="-c -I. -I/usr/include/newlib \
             -target arm-none-eabi  -mfloat-abi=hard -mcpu=cortex-m4 -mthumb $ARM_CFLAGS  \
             binson_light.c"

mkdir -p build/clang/arm
clang -Os $ARM_CMDARGS -o ./build/clang/arm/binson_light-`date '+%Y-%m-%d-%H:%M:%S'`_Os.o
clang -O2 $ARM_CMDARGS -o ./build/clang/arm/binson_light-`date '+%Y-%m-%d-%H:%M:%S'`_O2.o

