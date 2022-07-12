#!/bin/bash

# clean build dir
if [ -d 'build' ]
then
	rm -r build
fi

mkdir build

# compile
gcc -o build/main.o main.c

# make built file executable
chmod +x build/main.o

# run executable
./build/main.o

