CC = gcc
CFLAGS = -O3 -Wall -ggdb3
LIBS = -lm -lgsl -lgslcblas

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
	DT/createSimplexList.c\
	DT/createTreeOfEdgeOfEdges.c\
	DT/findAllSimplexesToModify.c\
	DT/findFirstSimplexToModify.c\
	DT/findPolygon.c\
	DT/serialDT.c\
	DT/serialDT.h\
	DT/updateAndAddSimplexes.c\
	DT/uploadInformationsAboutNeighborsInEdges.c\
	DTFE/densityOfTriangles.c\
	DTFE/DTFE.c\
	DTFE/DTFE.h\
	DTFE/MonteCarlo.c\
	HilbertCurve/hilbertCurve.h\
	HilbertCurve/hilbertCurve.c\
	IO/input.c\
	IO/io.h\
	Logs/Log.h\
	Logs/Log.c\
	edgeOfEdge.h\
	edgeOfEdge.c\
	myMath.h\
	myMath.c\
	polygon.h\
	polygon.c\
	simplex.h\
	simplex.c\
	supertriangles.h\
	supertriangles.c\
	utilities.h\
	utilities.c\
	validateResult.h\
	validateResult.c

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
