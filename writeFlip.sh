#! /bin/bash

stty -F /dev/ttyUSB0 9600
printf 'P,Y,0,2,M,Das ist ein Test' > /dev/ttyUSB0

