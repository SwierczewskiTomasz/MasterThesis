#ifndef TESTREDBLACKTREE_H
#define TESTREDBLACKTREE_H

#include "mainTests.h"
#include "../DataStructures/redBlackTree.h"

typedef struct PointForRedBlackTreeTests{
    int x;
} PointForRedBlackTreeTests;

double compareTwoPointsForRedBlackTreeTests(void *p1, void *p2);
char* printPointForRedBlackTreeTests(void *point);

void testRedBlackTree(int *testCounter);
void testRedBlackTreeCreating(int *testCounter);
void testRedBlackTreeInserting(int *testCounter);
void testRedBlackTreeRemoving(int *testCounter);

void testRedBlackTreeRemovingCase1(int *testCounter);
void testRedBlackTreeRemovingCase2(int *testCounter);
void testRedBlackTreeRemovingCase3(int *testCounter);
void testRedBlackTreeRemovingCase4(int *testCounter);
void testRedBlackTreeRemovingCase5(int *testCounter);
void testRedBlackTreeRemovingCase6(int *testCounter);
void testRedBlackTreeRemovingCase7(int *testCounter);
void testRedBlackTreeRemovingCase8(int *testCounter);
void testRedBlackTreeRemovingCase9(int *testCounter);
void testRedBlackTreeRemovingCase10(int *testCounter);

#endif

