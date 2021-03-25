#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H
#include "dataStructure.h"

typedef struct DoubleLinkedListNode
{
    struct DoubleLinkedListNode *next;
    struct DoubleLinkedListNode *prev;
    void *data;
} DoubleLinkedListNode;

typedef struct DoubleLinkedList
{
    int count;
    DoubleLinkedListNode *first;
} DoubleLinkedList;

void *removeFromDoubleLinkedList(DoubleLinkedList *list, DoubleLinkedListNode *node);
DoubleLinkedListNode *insertIntoDoubleLinkedList(DoubleLinkedList *list, DoubleLinkedListNode *node, void *data, double (*f)(void *, void *));
void insertIntoDoubleLinkedList2(DoubleLinkedList *list, void *data, double (*f)(void *, void *));
#endif