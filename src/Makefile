CC = gcc
CFLAGS = -O3
LIBS = -lm

FILES = \
	DataStructures/dataStructure.h\
	DataStructures/dataStructure.c\
	DataStructures/redBlackTree.h\
	DataStructures/redBlackTree.c\
	DataStructures/doubleLinkedList.h\
	DataStructures/doubleLinkedList.c\
	DataStructures/linkedList.h\
	DataStructures/linkedList.c\
	myMath.h\
	myMath.c\
	polygon.h\
	polygon.c\
	simplex.h\
	simplex.c\
	serialDT.c\
	serialDT.h\
	utilities.h\
	utilities.c


OUT = out/DT

all: main

main : 
	$(CC) $(FILES) $(CFLAGS) $(LIBS) -o $(OUT)

clean: 
	rm -f out/DT
	rm -f out/*.o
