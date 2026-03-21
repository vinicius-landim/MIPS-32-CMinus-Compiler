#!/bin/bash
flex scanner.l
bison -d parser.y
gcc -c *.c
gcc -g -o cmenos *.o -ll -lfl
./cmenos $1
g++ -c tradutor.cpp -o tradutor.out
g++ -c tradutorBinario.cpp -o tradutorBinario.out
g++ tradutor.out tradutorBinario.out
./a.out


