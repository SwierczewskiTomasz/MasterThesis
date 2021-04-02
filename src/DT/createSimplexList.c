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

LinkedList *createSimplexList(PolygonList *edges, PointId *point, UserOptions *options)
{
    PolygonLinkedListNode *currentEdge = edges->first;
    LinkedList *simplexList = newLinkedList(freeSimplex);

    while (currentEdge != NULL)
    {
        Simplex *result = (Simplex *)malloc(sizeof(Simplex));
        PointId *points[NO_DIM + 1]; 
        
        addPointAsFirstToArray(points, currentEdge->edge->points, point, NO_DIM + 1);
        createNewSimplex(result, points, options);

        result->neighbors[0] = currentEdge->edge->second;
        if (result->neighbors[0] != NULL)
        {
            //Tutaj trzeba naprawić wskaźnik do obecnego sympleksu, trzeba rozpoznać po drugiej stronie który to dokładnie jest. Może zapisywać to w edge? Jako i.
            result->neighbors[0]->neighbors[currentEdge->edge->secondIndex] = result;
        }

        currentEdge->edge->first = result;
        pushToLinkedList(simplexList, result);

#if DEBUG_TRIANGULATION == 1
        saveToLogs((char *)__FILE__, __LINE__, "Created Simplex: ", printLongSimplex, result);
#endif

        currentEdge = currentEdge->next;
    }

    return simplexList;
}