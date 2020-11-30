#include "edgeOfEdge.h"

double compareTwoEdgesOfEdges(void *p1, void *p2)
{
    EdgeOfEdge *e1 = (EdgeOfEdge*)p1;
    EdgeOfEdge *e2 = (EdgeOfEdge*)p2;
    return pointsArrayEquals(e1->points, e2->points, NO_DIM - 1);
}

double pointsArrayEquals(PointId *array1, PointId *array2, int n)
{
    //Zakładamy, że punkty są posortowane
    for (int i = 0; i < n; i++)
    {
        PointId p1 = array1[i];
        PointId p2 = array2[i];
        double result = comparePoints(p1.point, p2.point);
        if (result != 0)
            return result;
    }

    return 0;
}

void sortPointsArray(PointId **array, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1 - i; j++)
        {
            if (comparePoints(array[j]->point, array[j + 1]->point) > 0)
            {
                // Nie jestem pewien, czy to będzie dobrze działać, bo pracujemy tak de facto na PointId *, a rzeczywiście są PointId, a ja dałem PointId **array, aby można było ją modyfikować.
                PointId *copy = array[j];
                array[j] = array[j + 1];
                array[j + 1] = copy;
            }
        }
    }
}

PointId *addPointToSortedArray(PointId *array, PointId *p, int n)
{
    // Nie wiem, czy to dobre rozwiązanie
    PointId *result = (PointId *)malloc(n * sizeof(PointId));
    int j = 0;
    for (int i = 0; i < n - 1; i++)
    {
        if (i == j)
        {
            if (comparePoints(array[i].point, p->point) > 0)
            {
                result[j] = *p;
                j++;
                result[j] = array[i];
            }
            else
            {
                result[j] = array[i];
            }
        }
        else
        {
            result[j] = array[i];
        }
    }

    return result;
}

void addPointAsFirstToArray(PointId *result, PointId *array, PointId *p, int n)
{
    result[0] = *p;
    for(int i = 1; i < n; i++)
    {
        result[i] = array[i - 1];
    }
}

EdgeOfEdge *newEdgeOfEdge(Edge *e, int i)
{
    EdgeOfEdge *result = (EdgeOfEdge *)malloc(sizeof(EdgeOfEdge));
    result->first = e;
    result->second = NULL;
    PointId *array = removePointFromArray(e->points, NO_DIM, i);
    memcpy(result->points, array, (NO_DIM - 1) * sizeof(PointId));
    free(array);
#if DEBUG_EDGEOFEDGE == 1
    printf("File %s, line %i: newEdgeOfEdge function.\n", (char *)__FILE__, __LINE__);
    printf("Creating new Edge of edge. Edge: %p, i: %d, Points: p1: x: %f, y: %f, p2: x: %f, y: %f, first: %p, second: %p, secondIndex: %d, neighbors: n1: %p, n2: %p\n", 
        e, i, e->points[0].point.x, e->points[0].point.y, e->points[1].point.x, e->points[1].point.y, e->first, e->second, e->secondIndex, e->neighbors[0], e->neighbors[1]);
    printf("Created Edge of Edge: %p, first: %p, second: %p, p1: x: %f, y: %f\n\n", result, result->first, result->second, result->points[0].point.x, result->points[0].point.y);
#endif
    return result;
}

void freeEdgeOfEdge(void* e)
{
    EdgeOfEdge *edge = (EdgeOfEdge*)e;
    free(edge);
}