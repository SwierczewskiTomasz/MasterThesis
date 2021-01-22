#ifndef UTILITIES_H
#define UTILITIES_H

#include "constants.h"

long long extern doubleLinkedListInsertTime;
long long extern doubleLinkedListInsertTime2;
long long extern doubleLinkedListRemoveTime;
long long extern redBlackTreeInsertTime;
long long extern redBlackTreeGetTime;
long long extern redBlackTreeRemoveTime;
long long extern redBlackTreeNextNodeTime;
long long extern redBlackTreePrevNodeTime;

int generateNextTestNumberOfPoints(int n);
void testTIPP();
void testRedBlackTreeUtilities();
void testDoubleLinkedList();
void printInformationsAboutSizeOfStructures();
void printHilbertCurve(int n, char *filename);

#endif