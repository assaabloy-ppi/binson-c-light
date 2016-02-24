#!/bin/bash

PORT="/dev/ttyUSB0"
BAUD=19200

minicom --device $PORT -b $BAUD