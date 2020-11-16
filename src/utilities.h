#ifndef UTILITIES_H
#define UTILITIES_H

#ifndef MEASURE_TIME
#define MEASURE_TIME 1
#endif

#ifndef DEBUG
#define DEBUG 1
#define DEBUG_REDBLACKTREE 1
#endif

long long extern doubleLinkedListInsertTime;
long long extern doubleLinkedListInsertTime2;
long long extern doubleLinkedListRemoveTime;
long long extern redBlackTreeInsertTime;
long long extern redBlackTreeGetTime;
long long extern redBlackTreeRemoveTime;
long long extern redBlackTreeNextNodeTime;

int generateNextTestNumberOfPoints(int n);
void testRedBlackTree();
void testDoubleLinkedList();
#endif