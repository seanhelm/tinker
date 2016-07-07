#!/bin/bash

FILE=morse

# Compile to hex
avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o $FILE.o $FILE.c
avr-gcc -mmcu=atmega328p $FILE.o -o $FILE
avr-objcopy -O ihex -R .eeprom $FILE $FILE.hex

# Flash to AVR
avrdude -F -V -c arduino -p ATMEGA328P -P /dev/cu.usbmodem1421 -b 115200 -U flash:w:$FILE.hex
