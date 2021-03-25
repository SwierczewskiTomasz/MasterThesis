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

LinkedList *createSimplexList(PolygonList *edges, PointId *point, int hilbertDimension)
{
    PolygonLinkedListNode *currentEdge = edges->first;
    LinkedList *simplexList = newLinkedList(freeSimplex);

    while (currentEdge != NULL)
    {
        Simplex *result = (Simplex *)malloc(sizeof(Simplex));
        // PointId points[NO_DIM + 1] = addPointToSortedArray(currentEdge->edge->points, point, NO_DIM + 1);
        // sortPointsArray(&points, NO_DIM + 1);
        PointId *points[NO_DIM + 1]; // = addPointAsFirstToArray(currentEdge->edge->points, point, NO_DIM + 1);
        addPointAsFirstToArray(points, currentEdge->edge->points, point, NO_DIM + 1);
        createNewSimplex(result, points, hilbertDimension);

        result->neighbors[0] = currentEdge->edge->second;
        if (result->neighbors[0] != NULL)
        {
            //Tutaj trzeba naprawić wskaźnik do obecnego sympleksu, trzeba rozpoznać po drugiej stronie który to dokładnie jest. Może zapisywać to w edge? Jako i.
            result->neighbors[0]->neighbors[currentEdge->edge->secondIndex] = result;
        }

        currentEdge->edge->first = result;
        pushToLinkedList(simplexList, result);

#if DEBUG_TRIANGULATION == 1
        Simplex *simplex = result;
        printf("File %s, line %i: createSimplexList function.\n", (char *)__FILE__, __LINE__);
        printf("Created Simplex: %14p, center: x: %10.4f, y: %10.4f, radius: %10.4f\n", simplex, simplex->circumcenter.x, simplex->circumcenter.y, simplex->circumradius);
        printf("Points: p1: x: %10.4f, y: %10.4f, p2: x: %10.4f, y: %10.4f, p3: x: %10.4f, y: %10.4f\n", simplex->vertices[0]->point.x, simplex->vertices[0]->point.y,
               simplex->vertices[1]->point.x, simplex->vertices[1]->point.y, simplex->vertices[2]->point.x, simplex->vertices[2]->point.y);
        printf("Neighbors: 0: %14p, 1: %14p, 2: %14p\n", simplex->neighbors[0], simplex->neighbors[1], simplex->neighbors[2]);
        printf("Current Edge: %14p, Points: p1: x: %10.4f, y: %10.4f, p2: x: %10.4f, y: %10.4f, first: %14p, second: %14p, secondIndex: %d, neighbors: n1: %14p, n2: %14p \n\n",
               currentEdge->edge, currentEdge->edge->points[0]->point.x, currentEdge->edge->points[0]->point.y,
               currentEdge->edge->points[1]->point.x, currentEdge->edge->points[1]->point.y, currentEdge->edge->first, currentEdge->edge->second,
               currentEdge->edge->secondIndex, currentEdge->edge->neighbors[0], currentEdge->edge->neighbors[1]);
#endif

        currentEdge = currentEdge->next;
    }

    return simplexList;
}