#ifndef POLYGON_H
#define POLYGON_H

#include "DataStructures/dataStructure.h"
#include "simplex.h"

// Edge of simplex - it can be edge in 2D, face in 3D, tetrahedron in 4D etc. It connects 2 simplexes. 
typedef struct Edge
{
    PointId *points[NO_DIM];
    Simplex *first;
    Simplex *second;
    // secondIndex - in the simplex we know who is our neighbor, but we don't know on wich position is stored our position in other simplex. 
    // In this variable we will store index of simplex first in simplex second. 
    // neighbor(second, secondIndex) will return first simplex. 
    int secondIndex;
    struct Edge *neighbors[NO_DIM]; 
} Edge;

typedef struct PolygonLinkedListNode
{
    Edge *edge;
    struct PolygonLinkedListNode* next;
} PolygonLinkedListNode;

typedef struct PolygonList
{
    PolygonLinkedListNode *first;
    void (*freeData)(void *);
} PolygonList;

Edge* createNewEdge(Simplex *simplex, int i);
void freeEdge(void *e);

PointId **removePointFromArray(PointId **array, int n, int k);
bool pointEquals(PointId *p1, PointId *p2);
bool edgeEquals(Edge *e1, Edge *e2);

PolygonList *newPolygonList(void (*freeData)(void *));
void removePolygonList(PolygonList *list, bool removeData);

PolygonLinkedListNode* findInPolygonList(PolygonList *list, Edge *e);
void insertIntoPolygonList(PolygonList *list, Edge *e);
void removeFromPolygonList(PolygonList *list, PolygonLinkedListNode* node);

#endif