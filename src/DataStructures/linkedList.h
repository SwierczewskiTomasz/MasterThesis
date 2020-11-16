#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdlib.h>
#include "../utilities.h"

typedef struct LinkedListNode 
{
    struct LinkedListNode *next;
    void *data;
} LinkedListNode;

typedef struct LinkedList
{
    int count;
    LinkedListNode *first;
} LinkedList;

#endif