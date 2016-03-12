#!/bin/bash
gcc -c -Wall -g -c nstdlib.c -o nstdlib.o
ar -rcs libnaught.a nstdlib.o