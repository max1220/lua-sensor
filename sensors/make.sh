#!/bin/bash
gcc -Wall -Wextra -Wpedantic -fPIC -shared -I/usr/include/sensors/ -I/usr/include/lua5.1 -o sensors.so sensors.c -llua5.1 -lsensors
strip sensors.so
