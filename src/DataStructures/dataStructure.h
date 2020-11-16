#ifndef DATA_STRUCTURE_H
#define DATA_STRUCTURE_H

#include <stdlib.h>
#include "../utilities.h"
#include "doubleLinkedList.h"
#include "linkedList.h"

typedef struct Point
{
    double x;
    double y;
#if NO_DIM==3
    double z;
#endif
} Point;

typedef struct PointId
{
    unsigned long id;
    Point point;
} PointId;

typedef struct Edge
{
    PointId points[2];
} Edge;

typedef struct DataStructure
{
    void* root;
    void (*insert)(void *, void *);
    void* (*get)(void *, void *);
    void (*remove)(void *, void *);
} DataStructure;



void* getNextNode(void *node);
void* getDataFromNode(void *node);

#endif