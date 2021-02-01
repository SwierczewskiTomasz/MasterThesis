#include "edgeOfEdge.h"

#if ID == 1
ID_TYPE EdgeOfEdgeIdCount = 0;
#endif

double compareTwoEdgesOfEdges(void *p1, void *p2)
{
    EdgeOfEdge *e1 = (EdgeOfEdge *)p1;
    EdgeOfEdge *e2 = (EdgeOfEdge *)p2;
    return pointsArrayEquals(e1->points, e2->points, NO_DIM - 1);
}

double pointsArrayEquals(PointId **array1, PointId **array2, int n)
{
    //Zakładamy, że punkty są posortowane
    for (int i = 0; i < n; i++)
    {
        PointId *p1 = array1[i];
        PointId *p2 = array2[i];
        double result = comparePoints(p1->point, p2->point);
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

PointId **addPointToSortedArray(PointId **array, PointId *p, int n)
{
    // Nie wiem, czy to dobre rozwiązanie
    PointId **result = (PointId **)malloc(n * sizeof(PointId *));
    int j = 0;
    for (int i = 0; i < n - 1; i++)
    {
        if (i == j)
        {
            if (comparePoints(array[i]->point, p->point) > 0)
            {
                result[j] = p;
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

void addPointAsFirstToArray(PointId **result, PointId **array, PointId *p, int n)
{
    result[0] = p;
    for (int i = 1; i < n; i++)
    {
        result[i] = array[i - 1];
    }
}

EdgeOfEdge *newEdgeOfEdge(Edge *e, int i)
{
    EdgeOfEdge *result = (EdgeOfEdge *)malloc(sizeof(EdgeOfEdge));
#if ID == 1
    result->id = EdgeOfEdgeIdCount++;
#endif
    result->first = e;
    result->second = NULL;
    PointId **array = removePointFromArray(e->points, NO_DIM, i);
    memcpy(result->points, array, (NO_DIM - 1) * sizeof(PointId *));
    free(array);
#if DEBUG_EDGEOFEDGE == 1
    printf("File %s, line %i: newEdgeOfEdge function.\n", (char *)__FILE__, __LINE__);
    printf("Creating new Edge of edge. Edge: %p, i: %d, Points: p1: x: %f, y: %f, p2: x: %f, y: %f, first: %p, second: %p, secondIndex: %d, neighbors: n1: %p, n2: %p\n",
           e, i, e->points[0]->point.x, e->points[0]->point.y, e->points[1]->point.x, e->points[1]->point.y, e->first, e->second, e->secondIndex, e->neighbors[0], e->neighbors[1]);
    printf("Created Edge of Edge: %p, first: %p, second: %p, p1: x: %f, y: %f\n\n", result, result->first, result->second, result->points[0]->point.x, result->points[0]->point.y);
#endif
    return result;
}

void freeEdgeOfEdge(void *e)
{
    EdgeOfEdge *edge = (EdgeOfEdge *)e;
    free(edge);
}

char *printLongEdgeOfEdge(EdgeOfEdge *edge)
{
    int n = (NO_DIM * 20 + 20) * NO_DIM + 200;
    char *result = (char *)malloc(n * sizeof(char));
#if NO_DIM == 2
    char *pointIdString = printLongPointId(edge->points[0]);
    sprintf(result, "EdgeOfEdge: %14p, first: %14p, second: %14p, p1: %s \n", edge, edge->first, edge->second, pointIdString);
    free(pointIdString);
#elif NO_DIM == 3
    char *pointIdString0 = printLongPointId(edge->points[0]);
    char *pointIdString1 = printLongPointId(edge->points[1]);
    sprintf(result, "EdgeOfEdge: %14p, first: %14p, second: %14p, p1: %s, p2: %s \n", edge, edge->first, edge->second, pointIdString0, pointIdString1);
    free(pointIdString0);
    free(pointIdString1);
#else
    sprintf(result, "EdgeOfEdge: %14p, first: %14p, second: %14p", edge, edge->first, edge->second);
    for (int i = 0; i < NO_DIM; i++)
    {
        int n = NO_DIM * 20 + 30;
        char *temp = (char *)malloc(n * sizeof(char));
        char *pointIdString = printLongPointId(edge->points[i]);
        sprintf(temp, ", p%i: %s", i, pointIdString);
        strcat(result, temp);
        free(pointIdString);
        free(temp);
    }
    strcat(result, "\n");
#endif
    return result;
}

#if ID == 1
char *printShortEdgeOfEdge(EdgeOfEdge *edge)
{
    int n = 300;
    char *result = (char*)malloc(n * sizeof(char));
#if NO_DIM == 2
    sprintf(result, "EdgeOfEdge: %i, first: %i, second: %i, p1: %i \n", edge->id, edge->first == NULL?-1:edge->first->id, edge->second == NULL?-1:edge->second->id, edge->points[0]->id);
#elif NO_DIM == 3
    sprintf(result, "EdgeOfEdge: %i, first: %i, second: %i, p1: %i, p2: %i \n", edge->id, edge->first == NULL?-1:edge->first->id, edge->second == NULL?-1:edge->second->id, edge->points[0]->id, edge->points[1]->id);
#else
    sprintf(result, "EdgeOfEdge: %i, first: %i, second: %i", edge->id, edge->first == NULL?-1:edge->first->id, edge->second == NULL?-1:edge->second->id);

    for(int i = 0; i < NO_DIM; i++)
    {
        char temp[10];
        sprintf(temp, ", p%i: %i", i, edge->points[i]->id);
        strcat(result, temp);
    }
    strcat(result, "\n");
#endif
    return result;
}
#endif