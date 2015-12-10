#!/bin/bash
g++ -Wall -g -c nstdlib.cc -o nstdlib.o
ar -rcs libnaught.a nstdlib.o