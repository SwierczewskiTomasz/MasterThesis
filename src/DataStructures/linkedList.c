#include "stdio.h"
#include "linkedList.h"

LinkedList *newLinkedList(void (*freeData)(void *))
{
    LinkedList *result = (LinkedList *)malloc(sizeof(LinkedList));
    result->count = 0;
    result->first = NULL;
    result->freeData = freeData;
    return result;
}

void removeLinkedList(LinkedList *list, bool removeData)
{
    while (list->count != 0)
    {
        void *data = popFromLinkedList(list);
        if(removeData)
            list->freeData(data);
    }
    free(list);
}

void pushToLinkedList(LinkedList *list, void *data)
{
    LinkedListNode *node = (LinkedListNode *)malloc(sizeof(LinkedListNode));
    if (list == NULL)
    {
        fprintf(stderr, "Error in %s line %i: pushToLinkedList - list doesn't exists \n", (char *)__FILE__, __LINE__);
        return;
    }

    node->data = data;
    node->next = list->first;
    list->first = node;
    list->count++;
}

void *popFromLinkedList(LinkedList *list)
{
    if (list == NULL)
    {
        fprintf(stderr, "Error in %s line %i: pushToLinkedList - list doesn't exists \n", (char *)__FILE__, __LINE__);
        return NULL;
    }

    if (list->first == NULL)
        return NULL;
    
    list->count--;
    LinkedListNode *node = list->first;
    void *result = node->data;
    list->first = list->first->next;

    free(node);

    return result;
}