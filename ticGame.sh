#!/bin/bash

clear

if ! [ -x "$(command -v g++)" ]; then
  echo 'Error: g++ is not installed. Please install for cpp file compilation.' >&2
  exit 1
fi

g++ -o tic tic.cpp
./tic
