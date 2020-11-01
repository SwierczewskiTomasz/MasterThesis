#!/bin/bash
make all
out/DT.exe > out/output.txt
gnuplot "generateImages.plt"