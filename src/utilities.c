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

void testTIPP()
{
    int n = 0;

    for (int i = 0; i < 80; i++)
    {
        n = generateNextTestNumberOfPoints(n);
        TIPP(n, n);
    }
}

void testRedBlackTreeUtilities()
{
    srand(0);

    int n = 0;

    for (int i = 0; i < 20; i++)
    {
        redBlackTreeInsertTime = 0;
        redBlackTreeRemoveTime = 0;
        redBlackTree *tree = (redBlackTree *)malloc(sizeof(redBlackTree));
        tree->first = NULL;
        tree->compare = comparePositionOfTwoPoints;

        n = generateNextTestNumberOfPoints(n);

        PointId **array = (PointId **)calloc(n, sizeof(PointId **));


        for (int i = 0; i < n; i++)
        {
            PointId *point = (PointId *)malloc(sizeof(PointId));

            // double x = (double)rand() / (double)(RAND_MAX)*100.0;
            // double y = (double)rand() / (double)(RAND_MAX)*100.0;
            int x, y;

            do
            {
                x = rand() % n;
                y = rand() % n;
            } while (array[x] != NULL);

            point->point.x = x;
            point->point.y = y;

            array[x] = point;

            insertIntoRedBlackTree(tree, point);
        }
        printf("InsertTime: %d, %lld\n", n, redBlackTreeInsertTime);

        //removeRedBlackTree(tree, true);
        for (int i = 0; i < n; i++)
        {
            // double x = (double)rand() / (double)(RAND_MAX)*100.0;
            // double y = (double)rand() / (double)(RAND_MAX)*100.0;
            int x;

            do
            {
                x = rand() % n;
            } while (array[x] == NULL);

            redBlackTreeNode *node = getFromRedBlackTree(tree, array[x]);
            removeFromRedBlackTree(tree, node);
            array[x] = NULL;

            // insertIntoRedBlackTree(tree, point);
        }

        printf("RemoveTime: %d, %lld\n", n, redBlackTreeRemoveTime);

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

void printInformationsAboutSizeOfStructures()
{
    printf("Size of structures: \n\n");

    printf("redBlackTree:          %4ld \n", sizeof(redBlackTree));
    printf("redBlackTreeNode:      %4ld \n", sizeof(redBlackTreeNode));
    printf("LinkedList:            %4ld \n", sizeof(LinkedList));
    printf("LinkedListNode:        %4ld \n", sizeof(LinkedListNode));
    printf("PolygonList:           %4ld \n", sizeof(PolygonList));
    printf("PolygonLinkedListNode: %4ld \n\n", sizeof(PolygonLinkedListNode));

    printf("Edge:                  %4ld \n", sizeof(Edge));
    printf("EdgeOfEdge:            %4ld \n", sizeof(EdgeOfEdge));
    printf("Simplex:               %4ld \n", sizeof(Simplex));

    printf("\n");
}
