#!/bin/bash
mkdir ./build
#mkdir ./build/arduino

#CHIP="atmega168"
#CFLAGS="-g -O1 -std=c99 -flto -fpack-struct -ffreestanding -ffunction-sections -fdata-sections -funsigned-char -funsigned-bitfields -Wl,--gc-sections  -Wall -W -Wextra -pedantic"
CFLAGS="-g -Og -std=c99   -Wall -W -Wextra -pedantic"

#CFLAGS_AVR="-Os  -std=c99 -flto -finline-functions -fpack-struct -ffreestanding -mrelax -ffunction-sections -fdata-sections -funsigned-char -funsigned-bitfields -Wl,--gc-sections  -Wall -W -Wextra -pedantic -DF_CPU=16000000UL -mmcu=$CHIP -DAVR8"
#CFLAGS_AVR="-O0 -std=c99   -Wall -W -Wextra -pedantic -DF_CPU=16000000UL -mmcu=$CHIP -DAVR8"
INC="-I."


echo "===================== GCC Linux native ==========================="
gcc $INC $CFLAGS  binson_light.c binson_light_test.c  -o build/binson_light_test
gcc $INC $CFLAGS  binson_light.c binson_light_examples.c  -o build/binson_light_examples

#echo "===================== gcc-avr ==========================="
#rm  build/arduino/*.*
#avr-gcc $INC $CFLAGS_AVR  binson_light.c binson_light_test.c  -o build/arduino/binson_light_test
#avr-gcc $INC $CFLAGS_AVR  binson_light.c binson_light_examples.c  -o build/arduino/binson_light_examples

#avr-objcopy -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0 build/arduino/binson_light_test build/arduino/binson_light_test.eep 
#avr-objcopy -O ihex -R .eeprom build/arduino/binson_light_test build/arduino/binson_light_test.hex

#avr-objcopy -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0 build/arduino/binson_light_examples build/arduino/binson_light_examples.eep 
#avr-objcopy -O ihex -R .eeprom build/arduino/binson_light_examples build/arduino/binson_light_examples.hex

#echo === binson_light_test ===
#avr-size -C --mcu=$CHIP build/arduino/binson_light_test

#echo === binson_light_examples ===
#avr-size -C --mcu=$CHIP build/arduino/binson_light_examples