#!/bin/bash
tests=0

while test $# -gt 0; do
  case $1 in
    -t|--tests)
      tests=1
      shift
      ;;
    *)
      break
      ;;
  esac
done

if [ $tests == 1 ];
then
    make test
    out/DT
else
    make main
    out/DT
    gnuplot "generateImages.plt"
fi

# make all
# make main
# make tests
# out/DT #&> out/output1.txt
# valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose out/DT &> out/output1.txt
# gnuplot "generateImages.plt"