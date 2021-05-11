#include <stdlib.h>
#include "edge.h"
#include "../Utilities/utilities.h"

#if ID == 1
ID_TYPE EdgeIdCount = 0;
#endif

/**
 * This function create new Edge by "removing" i vertex from simplex.
 */
Edge *newEdge(Simplex *simplex, int i)
{
    Edge *result = (Edge *)malloc(sizeof(Edge));

#if ID == 1
    result->id = EdgeIdCount++;
#endif

    result->first = simplex;
    result->second = neighborOfSimplex(simplex, i);
    PointId **array = removePointFromArray(simplex->vertices, NO_DIM + 1, i);
    memcpy(result->points, array, NO_DIM * sizeof(PointId *));
    free(array);

    if (result->second != NULL)
    {
        for (int j = 0; j < NO_DIM + 1; j++)
        {
            if (neighborOfSimplex(result->second, j) == simplex)
                result->secondIndex = j;
        }
    }

    for (int i = 0; i < NO_DIM; i++)
        result->neighbors[i] = NULL;

    return result;
}

void freeEdge(void *e)
{
    Edge *edge = (Edge *)e;
    free(edge);
}

PointId **removePointFromArray(PointId **array, int n, int k)
{
    PointId **result = (PointId **)malloc((n - 1) * sizeof(PointId *));
    if (k > n)
        return NULL;
    for (int i = 0; i < k; i++)
    {
        result[i] = array[i];
    }
    for (int i = k + 1; i < n; i++)
    {
        result[i - 1] = array[i];
    }
    return result;
}

bool pointEquals(PointId *p1, PointId *p2)
{
    bool equal = true;;
    for(int i = 0; i < NO_DIM; i++)
    {
        if(p1->point.coords[i] != p2->point.coords[i])
        {
            equal = false;
            break;
        }
    }
    return equal;
}

bool edgeEquals(Edge *e1, Edge *e2)
{
#if DEBUG_TRIANGULATION == 1
    // printf("File %s, line %i: edgeEquals function.\n", (char *)__FILE__, __LINE__);
    //     printf("Current Edge: %14p, Points: p1: x: %10.4f, y: %10.4f, p2: x: %10.4f, y: %10.4f, first: %14p, second: %14p, secondIndex: %d, neighbors: n1: %14p, n2: %14p \n\n",
    //            edge, edge->points[0]->point.x, edge->points[0]->point.y,
    //            edge->points[1]->point.x, edge->points[1]->point.y, edge->first, edge->second,
    //            edge->secondIndex, edge->neighbors[0], edge->neighbors[1]);
    // printf(" e1: %s e2: %s \n\n", printShortEdge(e1), printShortEdge(e2));
#endif

    if (e1->first != NULL && e2->first != NULL && e1->second != NULL && e2->second != NULL)
        if ((e1->first == e2->first && e1->second == e2->second) || (e1->first == e2->second && e1->second == e2->first))
            return true;

    bool equal = true;
    for (int i = 0; i < NO_DIM; i++)
    {
        if (!pointEquals(e1->points[i], e2->points[i]))
            equal = false;
    }

    if (equal)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: Edge equal. You should think about 3D? \n\n", (char *)__FILE__, __LINE__);
        return true;
    }

    return false;
    //Tu należałoby lepiej to sprawdzić, ale to co jest powyżej chyba zadziała ;) - Otóż nie. Bo nie zadziała gdy to są nulle xD
    if (pointEquals(e1->points[0], e2->points[0]) && pointEquals(e1->points[1], e2->points[1]))
        return true;
    if (pointEquals(e1->points[0], e2->points[1]) && pointEquals(e1->points[1], e2->points[0]))
        return true;
    return false;
}