CC = gcc
CFLAGS = -O3 -Wall -ggdb3
LIBS = -lm

FILES = \
	constants.h\
	DataStructures/dataStructure.h\
	DataStructures/dataStructure.c\
	DataStructures/redBlackTree.h\
	DataStructures/redBlackTree.c\
	DataStructures/redBlackTreeDLL.h\
	DataStructures/redBlackTreeDLL.c\
	DataStructures/doubleLinkedList.h\
	DataStructures/doubleLinkedList.c\
	DataStructures/linkedList.h\
	DataStructures/linkedList.c\
	HilbertCurve/hilbertCurve.h\
	HilbertCurve/hilbertCurve.c\
	edgeOfEdge.h\
	edgeOfEdge.c\
	myMath.h\
	myMath.c\
	polygon.h\
	polygon.c\
	simplex.h\
	simplex.c\
	serialDT.c\
	serialDT.h\
	supertriangles.h\
	supertriangles.c\
	utilities.h\
	utilities.c

TESTS = \
	tests/mainTests.c\
	tests/mainTests.h\
	tests/testRedBlackTree.c\
	tests/testRedBlackTree.h\

MAIN_FILE = \
	main.c

OUT = out/DT

all: main

main: 
	$(CC) $(FILES) $(MAIN_FILE) $(CFLAGS) $(LIBS) -o $(OUT)

test:
	$(CC) $(FILES) $(TESTS) $(CFLAGS) $(LIBS) -o $(OUT)

clean: 
	rm -f out/DT
	rm -f out/*.o
