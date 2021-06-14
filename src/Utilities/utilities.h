#ifndef UTILITIES_H
#define UTILITIES_H

#include "../constants.h"
#include "../IO/userOptions.h"

int findInPolygonListCount;

long long extern redBlackTreeInsertCount;
long long extern redBlackTreeGetCount;
long long extern redBlackTreeRemoveCount;
long long extern redBlackTreeNextNodeCount;
long long extern redBlackTreePrevNodeCount;

long long extern redBlackTreeInsertDLLCount;
long long extern redBlackTreeGetDLLCount;
long long extern redBlackTreeRemoveDLLCount;
long long extern redBlackTreeNextNodeDLLCount;
long long extern redBlackTreePrevNodeDLLCount;

long long extern LUTRBTDLLInsertCount;
long long extern LUTRBTDLLGetCount;
long long extern LUTRBTDLLPrevNodeCount;
long long extern LUTRBTDLLNextNodeCount;
long long extern LUTRBTDLLRemoveCount;

long long extern doubleLinkedListInsertTime;
long long extern doubleLinkedListInsertTime2;
long long extern doubleLinkedListRemoveTime;
long long extern redBlackTreeInsertTime;
long long extern redBlackTreeGetTime;
long long extern redBlackTreeRemoveTime;
long long extern redBlackTreeNextNodeTime;
long long extern redBlackTreePrevNodeTime;
long long extern redBlackTreeInsertDLLTime;
long long extern redBlackTreeGetDLLTime;
long long extern redBlackTreeRemoveDLLTime;
long long extern redBlackTreeNextNodeDLLTime;
long long extern redBlackTreePrevNodeDLLTime;

long long extern findFirstSimplexTime;
long long extern trianglesToModifyTime;
long long extern findPolygonTime;
long long extern createTreeOfEdgeOfEdgesTime;
long long extern uploadInformationsAboutNeighborsInEdgesTime;
long long extern updateAndAddSimplexesTime;
long long extern NextNodeAfterAddingTime;

int generateNextTestNumberOfPoints(int n);
void testTIPP(UserOptions *options);
void testRedBlackTreeUtilities();
void testDoubleLinkedList();
void printInformationsAboutSizeOfStructures();
void printHilbertCurve(int n, char *filename);


#endif