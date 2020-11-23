#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utilities.h"
#include "DataStructures/dataStructure.h"
#include "DataStructures/redBlackTree.h"
#include "serialDT.h"

#if defined(WIND32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <time.h>
#include <Windows.h>
#else
#include <sys/time.h>
#include <unistd.h>
#endif

int generateNextTestNumberOfPoints(int n)
{
    if (n == 0)
        return 2;
    if (n == 2)
        return 4;
    if (n == 4)
        return 6;
    if (n == 6)
        return 8;
    return n + pow(2, (int)floor(log2((double)n)) - 2);
}

void testRedBlackTree()
{
    srand(0);

    int n = 0;
    for (int i = 0; i < 60; i++)
    {
        redBlackTreeInsertTime = 0;
        redBlackTree *tree = (redBlackTree *)malloc(sizeof(redBlackTree));
        tree->first = NULL;
        tree->compare = comparePositionOfTwoPoints;

        n = generateNextTestNumberOfPoints(n);

        for (int i = 0; i < n; i++)
        {
            PointId *point = (PointId *)malloc(sizeof(PointId));

            double x = (double)rand() / (double)(RAND_MAX)*100;
            double y = (double)rand() / (double)(RAND_MAX)*100;

            point->point.x = x;
            point->point.y = y;
            insertIntoRedBlackTree(tree, point);
        }
        printf("%d, %lld\n", n, redBlackTreeInsertTime);
        
        removeRedBlackTree(tree, true);

        // if(i > 60)
        //     sleep(2);
    }
}

void testDoubleLinkedList()
{
    srand(0);

    int n = 0;
    for (int i = 0; i < 55; i++)
    {
        doubleLinkedListInsertTime = 0;
        DoubleLinkedList *list = (DoubleLinkedList *)malloc(sizeof(DoubleLinkedList));
        DoubleLinkedListNode *first = (DoubleLinkedListNode *)malloc(sizeof(DoubleLinkedListNode));

        PointId *pointFirst = (PointId *)malloc(sizeof(PointId));
        double x = (double)rand() / (double)(RAND_MAX)*100;
        double y = (double)rand() / (double)(RAND_MAX)*100;
        pointFirst->point.x = x;
        pointFirst->point.y = y;
        list->first = first;
        first->data = pointFirst;

        n = generateNextTestNumberOfPoints(n);

        for (int i = 0; i < n; i++)
        {
            PointId *point = (PointId *)malloc(sizeof(PointId));

            double x = (double)rand() / (double)(RAND_MAX)*100;
            double y = (double)rand() / (double)(RAND_MAX)*100;

            point->point.x = x;
            point->point.y = y;
            insertIntoDoubleLinkedList(list, first, point, comparePositionOfTwoPoints);
        }
        printf("%d, %lld\n", n, doubleLinkedListInsertTime);
    }
}

