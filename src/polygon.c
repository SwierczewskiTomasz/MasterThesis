#include <stdlib.h>
#include "polygon.h"

#if ID == 1
ID_TYPE EdgeIdCount = 0;
#endif

// Creates new Edge by "removing" i vertex from simplex.
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

// Edge* newEdge(PointId p1, PointId p2)
// {
//     Edge *result = (Edge*)malloc(sizeof(Edge));
//     result->points[0] = p1;
//     result->points[1] = p2;

//     return result;
// }

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

#if NO_DIM == 2
bool pointEquals(PointId *p1, PointId *p2)
{
    return p1->point.x == p2->point.x && p1->point.y == p2->point.y;
}
#endif

#if NO_DIM == 3
bool pointEquals(PointId *p1, PointId *p2)
{
    return p1->point.x == p2->point.x && p1->point.y == p2->point.y && p1->point.z == p2->point.z;
}
#endif

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
               edge, edge->points[0]->point.x, edge->points[0]->point.y,
               edge->points[1]->point.x, edge->points[1]->point.y, edge->first, edge->second,
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
    if (list == NULL || node == NULL)
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

char *printLongEdge(Edge *edge)
{
    int n = 600;
    char *result = (char *)malloc(n * sizeof(char));

    sprintf(result, "Edge: %14p, points: ", edge);

    for (int i = 0; i < NO_DIM; i++)
    {
        char *temp = printLongPointId(edge->points[i]);
        int length = strlen(temp) + 10;
        char *temp2 = (char *)malloc(length * sizeof(char));
        sprintf(temp2, ", p%i: %s", i, temp);
        strcat(result, temp2);
        free(temp);
        free(temp2);
    }

    char *printFirst = printLongSimplex(edge->first);
    char *printSecond = printLongSimplex(edge->second);

    char temp[300];
    sprintf(temp, ", first: %s, second: %s, secondIndex: %i, neighbors: ", printFirst, printSecond, edge->secondIndex);
    strcat(result, temp);

    for (int i = 0; i < NO_DIM; i++)
    {
        char temp2[20];
        sprintf(temp2, ", n%i: %14p", i, edge->neighbors[i]);
        strcat(result, temp2);
    }

    strcat(result, "\n");

    free(printFirst);
    free(printSecond);

    return result;
}

#if ID == 1
char *printShortEdge(Edge *edge)
{
    int n = 600;
    char *result = (char *)malloc(n * sizeof(char));
    sprintf(result, "Edge: %3i, points: ", edge->id);

    for (int i = 0; i < NO_DIM; i++)
    {
        char temp[10];
        sprintf(temp, ", p%i: %3i", i, edge->points[i]->id);
        strcat(result, temp);
    }

    char temp[300];
    sprintf(temp, ", first: %3i, second: %3i, secondIndex: %3i, neighbors: ", edge->first == NULL ? -1 : edge->first->id,
            edge->second == NULL ? -1 : edge->second->id, edge->secondIndex);
    strcat(result, temp);

    for (int i = 0; i < NO_DIM; i++)
    {
        char temp2[20];
        sprintf(temp2, ", n%i: %3i", i, edge->neighbors[i] == NULL ? -1 : edge->neighbors[i]->id);
        strcat(result, temp2);
    }

    strcat(result, "\n");

    return result;
}

#endif