#!/bin/bash

mkdir build
cd build/
cmake ..
make -j
chmod 777 http_server_cpp
cp http_server_cpp ../