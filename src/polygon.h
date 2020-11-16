#include "DataStructures/dataStructure.h"

typedef struct PolygonLinkedListNode
{
    Edge *edge;
    struct PolygonLinkedListNode* next;
} PolygonLinkedListNode;

typedef struct PolygonList
{
    PolygonLinkedListNode *first;
} PolygonList;

Edge* createNewEdge(PointId p1, PointId p2);
int pointEquals(PointId p1, PointId p2);
int edgeEquals(Edge *e1, Edge *e2);
PolygonLinkedListNode* findInPolygonList(PolygonList *list, Edge *e);
void insertIntoPolygonList(PolygonList *list, Edge *e);
void removeFromPolygonList(PolygonList *list, PolygonLinkedListNode* node);

