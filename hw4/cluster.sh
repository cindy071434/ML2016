#!/bin/bash
g++ -o preprocess preprocess.cpp
./preprocess $1
python2 cluster.py $1 $2
