#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdbool.h>

typedef struct LinkedListNode 
{
    struct LinkedListNode *next;
    void *data;
    int n;
} LinkedListNode;

typedef struct LinkedList
{
    int count;
    LinkedListNode *first;
    void (*freeData)(void *);
} LinkedList;

LinkedList *newLinkedList(void (*freeData)(void *));
void removeLinkedList(LinkedList *list, bool removeData);
void pushToLinkedList(LinkedList *list, void *data);
void* popFromLinkedList(LinkedList *list);

#endif