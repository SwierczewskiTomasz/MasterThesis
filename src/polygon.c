#include <stdlib.h>
#include "polygon.h"

// Creates new Edge by "removing" i vertex from simplex.
Edge *createNewEdge(Simplex *simplex, int i)
{
    Edge *result = (Edge *)malloc(sizeof(Edge));
    result->first = simplex;
    result->second = neighborOfSimplex(simplex, i);
    PointId *array = removePointFromArray(simplex->vertices, NO_DIM + 1, i);
    memcpy(result->points, array, NO_DIM * sizeof(PointId));
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

// Edge* createNewEdge(PointId p1, PointId p2)
// {
//     Edge *result = (Edge*)malloc(sizeof(Edge));
//     result->points[0] = p1;
//     result->points[1] = p2;

//     return result;
// }

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

PolygonList *newPolygonList(void (*freeData)(void *))
{
    PolygonList *result = (PolygonList *)malloc(sizeof(PolygonList));
    result->freeData = freeData;
    result->first = NULL;
    return result;
}

void removePolygonList(PolygonList *list, bool removeData)
{
    if (list == NULL)
        return;

    PolygonLinkedListNode *node = list->first;
    while (node != NULL)
    {
        PolygonLinkedListNode *temp = node;
        if (removeData)
            list->freeData(temp->edge);
        node = node->next;
        free(temp);
    }
    free(list);
}

PolygonLinkedListNode *findInPolygonList(PolygonList *list, Edge *e)
{
    if (list == NULL || e == NULL)
        return NULL;

    PolygonLinkedListNode *node = list->first;

#if DEBUG_POLYGON == 1
    printf("File %s, line %i: findInPolygonList function.\n", (char *)__FILE__, __LINE__);
    printf("List: %14p, Node: %14p, e: %14p \n\n", list, node, e);
#endif
    while (node != NULL)
    {
#if DEBUG_POLYGON == 1
        Edge *edge = node->edge;
        printf("File %s, line %i: findInPolygonList function.\n", (char *)__FILE__, __LINE__);
        printf("Node: %14p, Edge: %14p\n", node, edge);
        printf("Edge from list: %14p, Points: p1: x: %10.4f, y: %10.4f, p2: x: %10.4f, y: %10.4f, first: %14p, second: %14p, secondIndex: %d, neighbors: n1: %14p, n2: %14p \n\n",
               edge, edge->points[0].point.x, edge->points[0].point.y,
               edge->points[1].point.x, edge->points[1].point.y, edge->first, edge->second,
               edge->secondIndex, edge->neighbors[0], edge->neighbors[1]);
#endif

        if (edgeEquals(node->edge, e) == 1)
            return node;

        node = node->next;
    }
    return NULL;
}

void insertIntoPolygonList(PolygonList *list, Edge *e)
{
    PolygonLinkedListNode *node = (PolygonLinkedListNode *)malloc(sizeof(PolygonLinkedListNode));

    if (e == NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: Something very weird - You try to insert empty Edge! List: %14p, Edge: %14p \n", (char *)__FILE__, __LINE__, list, e);
        return;
    }

    node->edge = e;
    node->next = list->first;
    list->first = node;
}

void removeFromPolygonList(PolygonList *list, PolygonLinkedListNode *node)
{
    if(list == NULL || node == NULL)
        return;
    
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
    free(node);
}