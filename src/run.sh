#!/bin/bash
make all
out/DT #> out/output.txt
# valgrind --leak-check=yes out/DT
gnuplot "generateImages.plt"