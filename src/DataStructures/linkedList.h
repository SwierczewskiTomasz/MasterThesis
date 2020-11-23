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

LinkedList *newLinkedList();
void removeLinkedList(LinkedList *list);
void pushToLinkedList(LinkedList *list, void *data);
void* popFromLinkedList(LinkedList *list);

#endif