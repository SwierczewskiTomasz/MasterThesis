#ifndef EDGEOFEDGE_H
#define EDGEOFEDGE_H

#include "DataStructures/dataStructure.h"
#include "simplex.h"
#include "polygon.h"

typedef struct EdgeOfEdge
{
    PointId points[NO_DIM - 1];
    Edge *first;
    Edge *second;
} EdgeOfEdge;

double compareTwoEdgesOfEdges(void *p1, void *p2);
double pointsArrayEquals(PointId *array1, PointId *array2, int n);
void sortPointsArray(PointId **array, int n);
PointId* addPointToSortedArray(PointId *array, PointId *p, int n);
void addPointAsFirstToArray(PointId *result, PointId *array, PointId *p, int n);
EdgeOfEdge *newEdgeOfEdge(Edge *e, int i);


#endif