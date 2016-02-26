# binson-c-light

A light-weight C implementation of the Binson serialization format for Linux and Atmega AVR8 MCUs

> Binson is like JSON, but faster, binary and even simpler. See [binson.org](http://binson.org/)

Status
---------

Writer part done and tested at x86_64 GCC Linux and Arduino Atmega168

Parser part in dev state....

Features
---------

* Written in ANSI C (C99 standard)
* Configurable features (via #defines)
* Multiplatform. Tested at:
  * x86_64 Linux (GCC)
  * avr8 (Atmega168)
* Compatible with: 
  * [binson-java](https://github.com/franslundberg/binson-java) (avr8 build lacks DOUBLE object type)
  * [binson-java-light](https://github.com/franslundberg/binson-java-light) (avr8 build lacks DOUBLE object type)
* Has no 3rd party dependencies. (libc.so/avr-libc only)
* No Arduino IDE/libs required.
* Optional user notifications (via callback function):
  * Destination buffer overflow (writer)
  * Destination buffer guard limit exceeded (writer)
  * Object keys are out of order (writer)
* Partial destination buffer allow to stream objects even larger than RAM available
* Has API to access string constants located in program space (functions with _p suffix)

Usage
---------

See ./binson_light_examples.c for usage example.


Build
---------

Install gcc and libs (Ubuntu)

`
$ sudo apt-get install build-essential
`

Install avr-gcc toolchain

`
$ sudo apt-get install gcc-avr binutils-avr gdb-avr avr-libc avrdude
`

To build both for both Linux and AVR8 run from project dir:

`
$ ./build.sh
`

Resulting binary files will be placed under ./build

To upload .hex file to chip's flash memory use one of ./burn_* scripts.

By default scripts will assume Atmega168 with Arduino bootloader is connected to serial port /dev/ttyUSB0

To see debug output use:

`
$ minicom --device /dev/ttyUSB0 -b 19200
`


