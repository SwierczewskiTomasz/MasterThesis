#!/bin/bash
make all
out/DT #> out/output.txt
gnuplot "generateImages.plt"