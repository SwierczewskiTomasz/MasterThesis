#include <stdio.h>
#include <stdlib.h>

#if defined(WIND32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <time.h>
#include <Windows.h>
#else
#include <sys/time.h>
#include <unistd.h>
#endif

#include <math.h>
#include "serialDT.h"

void updateAndAddSimplexes(PolygonList *edges, Partition *partition)
{
    PolygonLinkedListNode *currentEdge = edges->first;

    while (currentEdge != NULL)
    {

        Simplex *result = (Simplex *)currentEdge->edge->first;

        for (int i = 1; i < NO_DIM + 1; i++)
        {
            result->neighbors[i] = currentEdge->edge->neighbors[i - 1]->first;
        }
        sortPointsInSimplex(result);
#if REDBLACKTREEDLL == 1
        insertIntoRedBlackTreeDLL(partition->triangles, result);
#else
        insertIntoRedBlackTree(partition->triangles, result);
#endif

#if DEBUG_TRIANGULATION == 1
        Simplex *simplex = result;

        saveToLogs((char *)__FILE__, __LINE__, "Created new simplex: ", printLongSimplex, simplex);
        saveToLogs((char *)__FILE__, __LINE__, "Current Edge: ", printShortEdge, currentEdge->edge);

        printf("Triangles tree: \n");
        printRedBlackTreeDLLString(partition->triangles, printLongSimplex);
#endif
        currentEdge = currentEdge->next;
        //insertIntoDoubleLinkedList2(partition->triangles, result, comparePositionOfTwoTriangles);
        // printf("Triangle inserted: %10.4f, %10.4f, %10.4f, %10.4f, %10.4f, %10.4f, %10.4f, %10.4f, %10.4f \n", result->circumcenter.x, result->circumcenter.y, result->circumradius, result->vertices[0]->point.x, result->vertices[0]->point.y, result->vertices[1]->point.x, result->vertices[1]->point.y, result->vertices[2]->point.x, result->vertices[2]->point.y);
    }
}