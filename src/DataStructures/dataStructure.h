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
#if NO_DIM==2
    FLOATING_POINT_PRECISION x;
    FLOATING_POINT_PRECISION y;
#elif NO_DIM==3
    FLOATING_POINT_PRECISION x;
    FLOATING_POINT_PRECISION y;
    FLOATING_POINT_PRECISION z;
#else
    FLOATING_POINT_PRECISION coords[NO_DIM];
#endif

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

#if NO_DIM == 2
PointId* newPointId(FLOATING_POINT_PRECISION x, FLOATING_POINT_PRECISION y);
#elif NO_DIM == 3
PointId* newPointId(FLOATING_POINT_PRECISION x, FLOATING_POINT_PRECISION y, FLOATING_POINT_PRECISION z);
#else
PointId* newPointId(FLOATING_POINT_PRECISION coords[NO_DIM]);
#endif

char* printLongPointId(PointId *point);
#if ID == 1
char* printShortPointId(PointId *point);
#endif

#endif