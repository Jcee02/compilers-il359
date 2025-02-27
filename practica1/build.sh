#!/bin/bash


set -xe


gcc -o main main.c util.c
./main example2.txt
