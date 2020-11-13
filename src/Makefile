CC = gcc
CFLAGS = -O3
LIBS = -lm

FILES = \
	dataStructure.h\
	dataStructure.c\
	myMath.h\
	myMath.c\
	polygon.h\
	polygon.c\
	serialDT.c\
	serialDT.h\
	redBlackTree.c\
	redBlackTree.h\
	utilities.h\
	utilities.c

OUT = out/DT.exe

all: main

main : 
	$(CC) $(FILES) $(CFLAGS) $(LIBS) -o $(OUT)



clean: 
	rm -f out/DT.exe
	rm -f out/*.o
