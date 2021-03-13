#ifndef DATA_STRUCTURE_H
#define DATA_STRUCTURE_H

#include <stdlib.h>
#include <stdbool.h>
#include "../utilities.h"
#include "../constants.h"
#include "doubleLinkedList.h"
#include "linkedList.h"

typedef struct Point
{
    FLOATING_POINT_PRECISION coords[NO_DIM];
} Point;

typedef struct PointId
{
#if ID == 1
    ID_TYPE id;
#endif
    Point point;
} PointId;

// typedef struct DataStructure
// {
//     void* root;
//     void (*insert)(void *, void *);
//     void* (*get)(void *, void *);
//     void (*remove)(void *, void *);
// } DataStructure;

void* getNextNode(void *node);
void* getDataFromNode(void *node);

PointId* newPointId2D(FLOATING_POINT_PRECISION x, FLOATING_POINT_PRECISION y);
PointId* newPointId(FLOATING_POINT_PRECISION coords[NO_DIM]);

#endif