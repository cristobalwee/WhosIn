#!/bin/bash
gcc server.c -o server -lpthread
./server &
python inoutboard.py & 
