#ifndef POLYGON_H
#define POLYGON_H

#include "simplex.h"
#include "edge.h"

typedef struct PolygonLinkedListNode
{
    Edge *edge;
    struct PolygonLinkedListNode *next;
} PolygonLinkedListNode;

typedef struct PolygonList
{
    PolygonLinkedListNode *first;
    void (*freeData)(void *);
} PolygonList;



PolygonList *newPolygonList(void (*freeData)(void *));
void removePolygonList(PolygonList *list, bool removeData);

PolygonLinkedListNode *findInPolygonList(PolygonList *list, Edge *e);
void insertIntoPolygonList(PolygonList *list, Edge *e);
void removeFromPolygonList(PolygonList *list, PolygonLinkedListNode *node);



#endif