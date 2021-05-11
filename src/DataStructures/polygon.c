#include <stdlib.h>

#include "polygon.h"
#include "../Utilities/utilities.h"

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
    findInPolygonListCount++;
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