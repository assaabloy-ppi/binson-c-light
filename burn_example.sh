#!/bin/bash

PORT="/dev/ttyUSB0"
CHIP="atmega168"

avr-size -C --mcu=$CHIP build/arduino/binson_light_examples
avrdude -v -p$CHIP -carduino -P$PORT -b19200 -D -Uflash:w:build/arduino/binson_light_examples.hex:i 