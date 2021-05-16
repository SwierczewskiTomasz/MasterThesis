CC = gcc
CFLAGS = -O3 -Wall -ggdb3
LIBS = -lm -lgsl -lgslcblas

FILES = \
	DataStructures/Lists/doubleLinkedList.h\
	DataStructures/Lists/doubleLinkedList.c\
	DataStructures/Lists/linkedList.h\
	DataStructures/Lists/linkedList.c\
	DataStructures/LookUpTables/blockSizeArray.h\
	DataStructures/LookUpTables/blockSizeArray.c\
	DataStructures/LookUpTables/LUTRBTDLL.h\
	DataStructures/LookUpTables/LUTRBTDLL_part_2.c\
	DataStructures/LookUpTables/LUTRBTDLL.c\
	DataStructures/LookUpTables/ZCurveLUT.h\
	DataStructures/LookUpTables/ZCurveLUT.c\
	DataStructures/Other/hashTable.h\
	DataStructures/Other/hashTable.c\
	DataStructures/Trees/redBlackTree.h\
	DataStructures/Trees/redBlackTreePriv.h\
	DataStructures/Trees/redBlackTree.c\
	DataStructures/Trees/redBlackTreeDLL.h\
	DataStructures/Trees/redBlackTreeDLLPriv.h\
	DataStructures/Trees/redBlackTreeDLL.c\
	DataStructures/edge.h\
	DataStructures/edge.c\
 	DataStructures/edgeOfEdge.h\
	DataStructures/edgeOfEdge.c\
	DataStructures/points.h\
	DataStructures/points.c\
	DataStructures/polygon.h\
	DataStructures/polygon.c\
	DataStructures/simplex.h\
	DataStructures/simplex.c\
	DT/DTUsingLUT/LUTDT.h\
	DT/DTUsingLUT/LUTDT.c\
	DT/standardDT/createSimplexList.c\
	DT/standardDT/createTreeOfEdgeOfEdges.c\
	DT/standardDT/findAllSimplexesToModify.c\
	DT/standardDT/findFirstSimplexToModify.c\
	DT/standardDT/findPolygon.c\
	DT/standardDT/serialDT.c\
	DT/standardDT/serialDT.h\
	DT/standardDT/updateAndAddSimplexes.c\
	DT/standardDT/uploadInformationsAboutNeighborsInEdges.c\
	DTFE/densityOfTriangles.c\
	DTFE/DTFE.c\
	DTFE/DTFE.h\
	DTFE/monteCarlo.c\
	DTFE/smallTest.c\
	HilbertCurve/hilbertCurve.h\
	HilbertCurve/hilbertCurve.c\
	IO/input.c\
	IO/io.h\
	IO/output.c\
	IO/userOptions.c\
	IO/userOptions.h\
	Logs/Log.h\
	Logs/Log.c\
	Utilities/compare.h\
	Utilities/compare.c\
	Utilities/myMath.h\
	Utilities/myMath.c\
	Utilities/supertriangles.h\
	Utilities/supertriangles.c\
	Utilities/utilities.h\
	Utilities/utilities.c\
	Utilities/validateResult.h\
	Utilities/validateResult.c\
	constants.h\
	oneHeaderToRuleThemAll.h\

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

debug:
	$(CC) $(FILES) $(MAIN_FILE) -Wall -ggdb3 $(LIBS) -o $(OUT)

test:
	$(CC) $(FILES) $(TESTS) $(CFLAGS) $(LIBS) -o $(OUT)

clean: 
	rm -f out/DT
	rm -f out/*.o
