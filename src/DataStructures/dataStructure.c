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

#if NO_DIM == 2
PointId *newPointId(FLOATING_POINT_PRECISION x, FLOATING_POINT_PRECISION y)
{
    PointId *result = (PointId *)malloc(sizeof(PointId));
#if ID == 1
    result->id = PointIdCount++;
#endif
    result->point.x = x;
    result->point.y = y;

    return result;
}
#elif NO_DIM == 3
PointId *newPointId(FLOATING_POINT_PRECISION x, FLOATING_POINT_PRECISION y, FLOATING_POINT_PRECISION z)
{
    PointId *result = (PointId *)malloc(sizeof(PointId));
#if ID == 1
    result->id = PointIdCount++;
#endif
    result->point.x = x;
    result->point.y = y;
    result->point.z = z;

    return result;
}
#else
PointId *newPointId(FLOATING_POINT_PRECISION coords[NO_DIM])
{
    PointId *result = (PointId *)malloc(sizeof(PointId));
#if ID == 1
    result->id = PointIdCount++;
#endif
    
    for(int i = 0; i < NO_DIM; i++)
    {
        result->point.coords[i] = coords[i];
    }

    return result;
}
#endif

char *printLongPointId(PointId *point)
{
    int n = NO_DIM * 20 + 40;
    char *result = (char *)malloc(n * sizeof(char));
#if NO_DIM == 2
    sprintf(result, "id: %i, %14p, x: %10.4f, y: %10.4f", point->id, point, point->point.x, point->point.y);
#elif NO_DIM == 3
    sprintf(result, "id: %5i, %14p, x: %10.4f, y: %10.4f, z: %10.4f", point->id, point, point->point.x, point->point.y, point->point.z);
#else
    sprintf(result, "%14p", point);

    for (int i = 0; i < NO_DIM; i++)
    {
        char temp[20];
        sprintf(temp, ", c%i: %10.4f", i, point->point.coords[i]);
        strcat(result, temp);
    }
#endif
    // printf("Length of printPointId: %li \n", strlen(result));
    return result;
}

#if ID == 1
char *printShortPointId(PointId *point)
{
    int n = 20;
    char *result = (char *)malloc(n * sizeof(char));
    sprintf(result, "%i", point->id);
    return result;
}
#endif