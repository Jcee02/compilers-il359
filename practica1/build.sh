#!/bin/bash


set -xe


gcc -o lexer main.c util.c
./lexer example2.txt
