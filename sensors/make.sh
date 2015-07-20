#!/bin/bash
gcc -shared -Wall -I/usr/include/lua5.1 -llua5.1 -lsensors -o sensors.so sensors.c -fpic
