#include <stdlib.h>
#include "polygon.h"

PointId *removePointFromArray(PointId *array, int n, int k)
{
    PointId *result = (PointId *)malloc((n - 1) * sizeof(PointId));
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

// Creates new Edge by "removing" i vertex from simplex.
Edge *createNewEdge(Simplex *simplex, int i)
{
    Edge *result = (Edge *)malloc(sizeof(Edge));
    result->first = simplex;
    result->second = neighborOfSimplex(simplex, i);
    PointId *array = removePointFromArray(simplex->vertices, NO_DIM + 1, i);
    memcpy(result->points, array, NO_DIM * sizeof(PointId));

    if (result->second != NULL)
    {
        for (int j = 0; j < NO_DIM + 1; j++)
        {
            if (neighborOfSimplex(result->second, j) == simplex)
                result->secondIndex = j;
        }
    }

    return result;
}

// Edge* createNewEdge(PointId p1, PointId p2)
// {
//     Edge *result = (Edge*)malloc(sizeof(Edge));
//     result->points[0] = p1;
//     result->points[1] = p2;

//     return result;
// }

// #if NO_DIM==2
bool pointEquals(PointId p1, PointId p2)
{
    return p1.point.x == p2.point.x && p1.point.y == p2.point.y;
}
// #endif

bool edgeEquals(Edge *e1, Edge *e2)
{
    if (e1->first != NULL && e2->first != NULL && e1->second != NULL && e2->second != NULL)
        if ((e1->first == e2->first && e1->second == e2->second) || (e1->first == e2->second && e1->second == e2->first))
            return true;

    //Tu należałoby lepiej to sprawdzić, ale to co jest powyżej chyba zadziała ;) - Otóż nie. Bo nie zadziała gdy to są nulle xD
    if (pointEquals(e1->points[0], e2->points[0]) && pointEquals(e1->points[1], e2->points[1]))
        return true;
    if (pointEquals(e1->points[0], e2->points[1]) && pointEquals(e1->points[1], e2->points[0]))
        return true;
    return false;
}

PolygonLinkedListNode *findInPolygonList(PolygonList *list, Edge *e)
{
    PolygonLinkedListNode *node = list->first;
    while (node != NULL)
    {
        if (edgeEquals(node->edge, e) == 1)
            return node;
        node = node->next;
    }
    return NULL;
}

void insertIntoPolygonList(PolygonList *list, Edge *e)
{
    PolygonLinkedListNode *node = (PolygonLinkedListNode *)malloc(sizeof(PolygonLinkedListNode));

    node->edge = e;
    node->next = list->first;
    list->first = node;
}

void removeFromPolygonList(PolygonList *list, PolygonLinkedListNode *node)
{
    PolygonLinkedListNode *p = list->first;
    if (p == node)
    {
        list->first = p->next;
    }

    while (p != NULL)
    {
        if (p->next == node)
        {
            p->next = node->next;
            break;
        }
        p = p->next;
    }
}