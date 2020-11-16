#if defined(WIND32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <time.h>
#include <Windows.h>
#else
#include <sys/time.h>
#include <unistd.h>
#endif

#include <stdio.h>
#include "dataStructure.h"

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