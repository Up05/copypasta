#!/bin/sh
clear
# gcc *.c -lncursesw -g -O0 -mshstk -o copypasta 
gcc *.c -lncursesw -O2 -mshstk -o copypasta 
# && ./copypasta
