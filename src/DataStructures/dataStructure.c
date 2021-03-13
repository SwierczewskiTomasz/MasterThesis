#if defined(WIND32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <time.h>
#include <Windows.h>
#else
#include <sys/time.h>
#include <unistd.h>
#endif

#include <stdio.h>
#include <string.h>
#include "dataStructure.h"

#if ID == 1
ID_TYPE PointIdCount = 0;
#endif

void *getNextNode(void *node)
{
    DoubleLinkedListNode *listNode = (DoubleLinkedListNode *)node;
    return listNode->next;
}

void *getDataFromNode(void *node)
{
    DoubleLinkedListNode *listNode = (DoubleLinkedListNode *)node;
    return listNode->data;
}

PointId *newPointId2D(FLOATING_POINT_PRECISION x, FLOATING_POINT_PRECISION y)
{
    PointId *result = (PointId *)malloc(sizeof(PointId));
#if ID == 1
    result->id = PointIdCount++;
#endif

    result->point.coords[0] = x;
    result->point.coords[1] = y;

    return result;
}

PointId *newPointId(FLOATING_POINT_PRECISION coords[NO_DIM])
{
    PointId *result = (PointId *)malloc(sizeof(PointId));
#if ID == 1
    result->id = PointIdCount++;
#endif
    
#warning Instead of making it in for loop, better will be using memcpy

    for(int i = 0; i < NO_DIM; i++)
    {
        result->point.coords[i] = coords[i];
    }

    return result;
}

