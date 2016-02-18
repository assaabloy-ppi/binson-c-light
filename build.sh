#!/bin/bash
mkdir ./build
mkdir ./build/arduino

CHIP="atmega328"
CFLAGS="-g -O2 -std=c99 -fno-builtin -Wall -W -Wextra -pedantic"
CFLAGS_AVR="-Os -std=c99 -flto -finline-functions -fpack-struct -ffreestanding -mrelax -ffunction-sections -fdata-sections -funsigned-char -funsigned-bitfields -Wl,--gc-sections  -Wall -W -Wextra -pedantic -DF_CPU=16000000UL -mmcu=$CHIP -DAVR8"
#CFLAGS_AVR="-O0 -std=c99   -Wall -W -Wextra -pedantic -DF_CPU=16000000UL -mmcu=$CHIP -DAVR8"
INC="-I."


echo "===================== GCC Linux native ==========================="
gcc $INC $CFLAGS  binson_light.c binson_light_test.c  -o build/binson_light_test

echo "===================== gcc-avr ==========================="
rm  build/arduino/binson_light_test build/arduino/binson_light_test.hex
avr-gcc $INC $CFLAGS_AVR  binson_light.c binson_light_test.c  -o build/arduino/binson_light_test
avr-objcopy -j .text -j .data -O ihex build/arduino/binson_light_test build/arduino/binson_light_test.hex
echo
avr-size -C --mcu=$CHIP build/arduino/binson_light_test