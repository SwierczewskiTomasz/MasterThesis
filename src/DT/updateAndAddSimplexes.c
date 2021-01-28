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
            //result->neighbors[i] = currentEdge->edge->neighbors[i - 1]->first;
            result->neighbors[i] = currentEdge->edge->neighbors[i - 1]->first;
        }
        sortPointsInSimplex(result);
        insertIntoRedBlackTree(partition->triangles, result);

#if DEBUG_TRIANGULATION == 1
        Simplex *simplex = result;
        printf("File %s, line %i: updateAndAddSimplexes function.\n", (char *)__FILE__, __LINE__);
        // printf("Created new simplex: %14p, center: x: %10.4f, y: %10.4f, radius: %10.4f\n", simplex, simplex->circumcenter.x, simplex->circumcenter.y, simplex->circumradius);
        // printf("Points: p1: x: %10.4f, y: %10.4f, p2: x: %10.4f, y: %10.4f, p3: x: %10.4f, y: %10.4f\n", simplex->vertices[0]->point.x, simplex->vertices[0]->point.y,
        //        simplex->vertices[1]->point.x, simplex->vertices[1]->point.y, simplex->vertices[2]->point.x, simplex->vertices[2]->point.y);
        // printf("Neighbors: 0: %14p, 1: %14p, 2: %14p\n", simplex->neighbors[0], simplex->neighbors[1], simplex->neighbors[2]);
        printf("Created new simplex: %s\n\n", printShortSimplex(simplex));
        // printf("Current Edge: %14p, Points: p1: x: %10.4f, y: %10.4f, p2: x: %10.4f, y: %10.4f, first: %14p, second: %14p, secondIndex: %d, neighbors: n1: %14p, n2: %14p \n\n",
        //        currentEdge->edge, currentEdge->edge->points[0]->point.x, currentEdge->edge->points[0]->point.y,
        //        currentEdge->edge->points[1]->point.x, currentEdge->edge->points[1]->point.y, currentEdge->edge->first, currentEdge->edge->second,
        //        currentEdge->edge->secondIndex, currentEdge->edge->neighbors[0], currentEdge->edge->neighbors[1]);
        printf("Current Edge: %s\n\n", printShortEdge(currentEdge->edge));
        printf("Triangles tree: \n");
        printRedBlackTreeString(partition->triangles, printShortSimplex);
        // printf("Tadam\n");
        // sleep(2);
#endif
        currentEdge = currentEdge->next;
        //insertIntoDoubleLinkedList2(partition->triangles, result, comparePositionOfTwoTriangles);
        // printf("Triangle inserted: %10.4f, %10.4f, %10.4f, %10.4f, %10.4f, %10.4f, %10.4f, %10.4f, %10.4f \n", result->circumcenter.x, result->circumcenter.y, result->circumradius, result->vertices[0]->point.x, result->vertices[0]->point.y, result->vertices[1]->point.x, result->vertices[1]->point.y, result->vertices[2]->point.x, result->vertices[2]->point.y);
    }
}