CC = gcc
CFLAGS = -O3
LIBS = -lm

FILES = \
	myMath.h\
	myMath.c\
	polygon.h\
	polygon.c\
	dataStructure.h\
	dataStructure.c\
	serialDT.c\
	serialDT.h

OUT = out/DT.exe

all: main

main : 
	$(CC) $(FILES) $(CFLAGS) $(LIBS) -o $(OUT)


clean: 
	rm -f out/DT.exe
	rm -f out/*.o
