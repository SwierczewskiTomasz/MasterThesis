#include <stdlib.h>
#include "polygon.h"


Edge* createNewEdge(PointId p1, PointId p2)
{
    Edge *result = (Edge*)malloc(sizeof(Edge));
    result->points[0] = p1;
    result->points[1] = p2;

    return result;
}

int pointEquals(PointId p1, PointId p2)
{
    return p1.point.x == p2.point.x && p1.point.y == p2.point.y;
}

int edgeEquals(Edge *e1, Edge *e2)
{
    if(pointEquals(e1->points[0], e2->points[0]) && pointEquals(e1->points[1], e2->points[1]))
        return 1;
    if(pointEquals(e1->points[0], e2->points[1]) && pointEquals(e1->points[1], e2->points[0]))
        return 1;
    return 0;
}

PolygonLinkedListNode *findInPolygonList(PolygonList *list, Edge *e)
{
    PolygonLinkedListNode *node = list->first;
    while(node != NULL)
    {
        if(edgeEquals(node->edge, e) == 1)
            return node;
        node = node->next;
    }
    return NULL;
}

void insertIntoPolygonList(PolygonList *list, Edge *e)
{
    PolygonLinkedListNode *node = (PolygonLinkedListNode*)malloc(sizeof(PolygonLinkedListNode));
    node->edge = e;
    node->next = list->first;
    list->first = node;
}

void removeFromPolygonList(PolygonList *list, PolygonLinkedListNode* node)
{
    PolygonLinkedListNode *p = list->first;
    if(p == node)
    {
        list->first = p->next;
    }

    while(p != NULL)
    {
        if(p->next == node)
        {
            p->next = node->next;
            break;
        }
        p = p->next;
    }
    
}