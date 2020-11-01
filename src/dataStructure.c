#include "dataStructure.h"
#include <stdio.h>

void *removeFromDoubleLinkedList(DoubleLinkedList *list, DoubleLinkedListNode *node)
{
    // This function return next node from remove or previous, if next doesn't exist
    DoubleLinkedListNode *result;
    if (node->next != NULL)
        result = node->next;
    else
        result = node->prev;

    if (list->first == node)
    {
        list->first = node->next;
    }

    if (node->prev != NULL)
    {
        node->prev->next = node->next;
    }

    if (node->next != NULL)
    {
        node->next->prev = node->prev;
    }
    
    node->prev = NULL;
    node->next = NULL;

    return result;
}

DoubleLinkedListNode *insertIntoDoubleLinkedList(DoubleLinkedList *list, DoubleLinkedListNode *node, void *data, double (*f)(void *, void *))
{
    // printf("Inside of function insertIntoDoubleLinkedList\n");
    // f(data, node->data);
    // printf("Mayday?\n");

    if(node == NULL || list->first == NULL)
    {
        DoubleLinkedListNode *newNode = (DoubleLinkedListNode *)malloc(sizeof(DoubleLinkedListNode));
        newNode->data = data;
        newNode->next = NULL;
        newNode->prev = NULL;
        list->first = newNode;
        return newNode;
    }

    if (f(data, node->data) > 0)
    {
        // printf("We must move always forward\n");
        while (node->next != NULL)
        {
            if (f(data, node->data) <= 0)
            {
                DoubleLinkedListNode *newNode = (DoubleLinkedListNode *)malloc(sizeof(DoubleLinkedListNode));
                newNode->data = data;
                newNode->next = node;
                newNode->prev = node->prev;
                node->prev = newNode;
                if (newNode->prev != NULL)
                {
                    newNode->prev->next = newNode;
                }
                else
                {
                    if (list->first == node)
                        list->first = newNode;
                    else
                        sprintf(stderr, "Error in %s line %i: insertIntoDoubleLinkedList - unexpected situation - node and list first node aren't the same when doesn't exists previous node. \n", (char *)__FILE__, __LINE__);
                }
                return newNode;
            }
            node = node->next;
        }
        if (f(data, node->data) <= 0)
        {
            DoubleLinkedListNode *newNode = (DoubleLinkedListNode *)malloc(sizeof(DoubleLinkedListNode));
            newNode->data = data;
            newNode->next = node;
            newNode->prev = node->prev;
            node->prev = newNode;
            if (newNode->prev != NULL)
            {
                newNode->prev->next = newNode;
            }
            else
            {
                if (list->first == node)
                    list->first = newNode;
                else
                    sprintf(stderr, "Error in %s line %i: insertIntoDoubleLinkedList - unexpected situation - node and list first node aren't the same when doesn't exists previous node. \n", (char *)__FILE__, __LINE__);
            }
            return newNode;
        }
        else
        {
            DoubleLinkedListNode *newNode = (DoubleLinkedListNode *)malloc(sizeof(DoubleLinkedListNode));
            newNode->data = data;
            newNode->next = node->next;
            newNode->prev = node;
            node->next = newNode;
            if (newNode->next != NULL)
                newNode->next->prev = newNode;
            return newNode;
        }
    }
    else
    {
        // printf("We must move always backward\n");
        while (node->prev != NULL)
        {
            if (f(data, node->data) >= 0)
            {
                DoubleLinkedListNode *newNode = (DoubleLinkedListNode *)malloc(sizeof(DoubleLinkedListNode));
                newNode->data = data;
                newNode->next = node->next;
                newNode->prev = node;
                node->next = newNode;
                if (newNode->next != NULL)
                    newNode->next->prev = newNode;
                return newNode;
            }
            node = node->prev;
        }
        if (f(data, node->data) >= 0)
        {
            DoubleLinkedListNode *newNode = (DoubleLinkedListNode *)malloc(sizeof(DoubleLinkedListNode));
            newNode->data = data;
            newNode->next = node->next;
            newNode->prev = node;
            node->next = newNode;
            if (newNode->next != NULL)
                newNode->next->prev = newNode;
            return newNode;
        }
        else
        {
            DoubleLinkedListNode *newNode = (DoubleLinkedListNode *)malloc(sizeof(DoubleLinkedListNode));
            newNode->data = data;
            newNode->next = node;
            newNode->prev = node->prev;
            node->prev = newNode;
            if (list->first == node)
            {
                list->first = newNode;
                // printf("Inserted as first\n");
            }
            else
                sprintf(stderr, "Error in %s line %i: insertIntoDoubleLinkedList - unexpected situation - node and list first node aren't the same when doesn't exists previous node. \n", (char *)__FILE__, __LINE__);

            return newNode;
        }
    }
}

void insertIntoDoubleLinkedList2(DoubleLinkedList *list, void *data, double (*f)(void *, void *))
{
    // printf("Inside of function insertIntoDoubleLinkedList\n");
    // f(data, node->data);
    // printf("Mayday?\n");

    DoubleLinkedListNode *node = list->first;

    if(list->first == NULL)
    {
        DoubleLinkedListNode *newNode = (DoubleLinkedListNode *)malloc(sizeof(DoubleLinkedListNode));
        newNode->data = data;
        newNode->next = NULL;
        newNode->prev = NULL;
        list->first = newNode;
        return newNode;
    }

    if (f(data, node->data) > 0)
    {
        // printf("We must move always forward\n");
        while (node->next != NULL)
        {
            if (f(data, node->data) <= 0)
            {
                DoubleLinkedListNode *newNode = (DoubleLinkedListNode *)malloc(sizeof(DoubleLinkedListNode));
                newNode->data = data;
                newNode->next = node;
                newNode->prev = node->prev;
                node->prev = newNode;
                if (newNode->prev != NULL)
                {
                    newNode->prev->next = newNode;
                }
                else
                {
                    if (list->first == node)
                        list->first = newNode;
                    else
                        sprintf(stderr, "Error in %s line %i: insertIntoDoubleLinkedList - unexpected situation - node and list first node aren't the same when doesn't exists previous node. \n", (char *)__FILE__, __LINE__);
                }
                return newNode;
            }
            node = node->next;
        }
        if (f(data, node->data) <= 0)
        {
            DoubleLinkedListNode *newNode = (DoubleLinkedListNode *)malloc(sizeof(DoubleLinkedListNode));
            newNode->data = data;
            newNode->next = node;
            newNode->prev = node->prev;
            node->prev = newNode;
            if (newNode->prev != NULL)
            {
                newNode->prev->next = newNode;
            }
            else
            {
                if (list->first == node)
                    list->first = newNode;
                else
                    sprintf(stderr, "Error in %s line %i: insertIntoDoubleLinkedList - unexpected situation - node and list first node aren't the same when doesn't exists previous node. \n", (char *)__FILE__, __LINE__);
            }
            return newNode;
        }
        else
        {
            DoubleLinkedListNode *newNode = (DoubleLinkedListNode *)malloc(sizeof(DoubleLinkedListNode));
            newNode->data = data;
            newNode->next = node->next;
            newNode->prev = node;
            node->next = newNode;
            if (newNode->next != NULL)
                newNode->next->prev = newNode;
            return newNode;
        }
    }
    else
    {
        // printf("We must move always backward\n");
        while (node->prev != NULL)
        {
            if (f(data, node->data) >= 0)
            {
                DoubleLinkedListNode *newNode = (DoubleLinkedListNode *)malloc(sizeof(DoubleLinkedListNode));
                newNode->data = data;
                newNode->next = node->next;
                newNode->prev = node;
                node->next = newNode;
                if (newNode->next != NULL)
                    newNode->next->prev = newNode;
                return newNode;
            }
            node = node->prev;
        }
        if (f(data, node->data) >= 0)
        {
            DoubleLinkedListNode *newNode = (DoubleLinkedListNode *)malloc(sizeof(DoubleLinkedListNode));
            newNode->data = data;
            newNode->next = node->next;
            newNode->prev = node;
            node->next = newNode;
            if (newNode->next != NULL)
                newNode->next->prev = newNode;
            return newNode;
        }
        else
        {
            DoubleLinkedListNode *newNode = (DoubleLinkedListNode *)malloc(sizeof(DoubleLinkedListNode));
            newNode->data = data;
            newNode->next = node;
            newNode->prev = node->prev;
            node->prev = newNode;
            if (list->first == node)
            {
                list->first = newNode;
                // printf("Inserted as first\n");
            }
            else
                sprintf(stderr, "Error in %s line %i: insertIntoDoubleLinkedList - unexpected situation - node and list first node aren't the same when doesn't exists previous node. \n", (char *)__FILE__, __LINE__);

            return newNode;
        }
    }
}

void* getNextNode(void *node)
{
    DoubleLinkedListNode *listNode = (DoubleLinkedListNode*)node;
    return listNode->next; 
}

void* getDataFromNode(void *node)
{
    DoubleLinkedListNode *listNode = (DoubleLinkedListNode*)node;
    return listNode->data;
}