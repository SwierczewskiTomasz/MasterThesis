#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "utilities.h"
#include "DataStructures/dataStructure.h"
#include "DataStructures/redBlackTree.h"
#include "HilbertCurve/hilbertCurve.h"
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
    // int n = 0;
    // int hilbertDimension = 16;

    // int dimensions[10];
    // dimensions[0] = 1;
    // dimensions[1] = 2;
    // dimensions[2] = 4;
    // dimensions[3] = 8;
    // dimensions[4] = 16;
    // dimensions[5] = 32;
    // dimensions[6] = 64;
    // dimensions[7] = 128;
    // dimensions[8] = 256;
    // dimensions[9] = 4096;

    // for (int i = 5; i < 10; i++)
    // {
    //     printf("\ndimensions: %d, %d\n", i, dimensions[i]);
    //     n = 0;
    //     for (int j = 0; j < 60; j++)
    //     {
    //         n = generateNextTestNumberOfPoints(n);
    //         TIPP(n, n, dimensions[i]);
    //     }
    // }

    TIPP(32, 32, 1);

    // TIPP(1024*1024*1024, 1024*1024*1024, 32);
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

void printHilbertCurve(int n, char *filename)
{
    FILE *fp;
    fp = fopen(filename, "w+");
    int k = n * n;
    double prevX, prevY;
    hilbertCurveD2DoubleXY(n, 0, &prevX, &prevY, 0, 100, 0, 100);
    for (int i = 1; i < k; i++)
    {
        double x, y;
        hilbertCurveD2DoubleXY(n, i, &x, &y, 0, 100, 0, 100);
        fprintf(fp, "%f, %f\n%f, %f\n\n", prevX, prevY, x, y);
        prevX = x;
        prevY = y;
    }
    fclose(fp);
}