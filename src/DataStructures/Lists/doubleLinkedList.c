#if defined(WIND32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <time.h>
#include <Windows.h>
#else
#include <sys/time.h>
#include <unistd.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include "doubleLinkedList.h"
#include "../../Utilities/utilities.h"

void *getNextNode(void *node)
{
    DoubleLinkedListNode *listNode = (DoubleLinkedListNode *)node;
    if (listNode == NULL)
        return NULL;
    return listNode->next;
}

void *getDataFromNode(void *node)
{
    DoubleLinkedListNode *listNode = (DoubleLinkedListNode *)node;
    if (listNode == NULL)
        return NULL;
    return listNode->data;
}

void *removeFromDoubleLinkedList(DoubleLinkedList *list, DoubleLinkedListNode *node)
{
    // This function return next node from remove or previous, if next doesn't exist
    struct timeval te1;
    gettimeofday(&te1, NULL);
    long long time1 = te1.tv_sec * 1000000LL + te1.tv_usec;

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

    struct timeval te2;
    gettimeofday(&te2, NULL);
    long long time2 = te2.tv_sec * 1000000LL + te2.tv_usec;
    doubleLinkedListRemoveTime += time2 - time1;

    return result;
}

DoubleLinkedListNode *insertIntoDoubleLinkedList(DoubleLinkedList *list, DoubleLinkedListNode *node, void *data, double (*f)(void *, void *))
{
#if MEASURE_TIME == 2
    struct timeval te1;
    gettimeofday(&te1, NULL);
    long long time1 = te1.tv_sec * 1000000LL + te1.tv_usec;
#endif

    if (node == NULL || list->first == NULL)
    {
        DoubleLinkedListNode *newNode = (DoubleLinkedListNode *)malloc(sizeof(DoubleLinkedListNode));
        newNode->data = data;
        newNode->next = NULL;
        newNode->prev = NULL;
        list->first = newNode;

#if MEASURE_TIME == 2
        struct timeval te2;
        gettimeofday(&te2, NULL);
        long long time2 = te2.tv_sec * 1000000LL + te2.tv_usec;
        doubleLinkedListInsertTime += time2 - time1;
#endif

        return newNode;
    }

    if (f(data, node->data) > 0)
    {
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
                        fprintf(stderr, "Error in %s line %i: insertIntoDoubleLinkedList - unexpected situation - node and list first node aren't the same when doesn't exists previous node. \n", (char *)__FILE__, __LINE__);
                }

#if MEASURE_TIME == 2
                struct timeval te2;
                gettimeofday(&te2, NULL);
                long long time2 = te2.tv_sec * 1000000LL + te2.tv_usec;
                doubleLinkedListInsertTime += time2 - time1;
#endif

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
                    fprintf(stderr, "Error in %s line %i: insertIntoDoubleLinkedList - unexpected situation - node and list first node aren't the same when doesn't exists previous node. \n", (char *)__FILE__, __LINE__);
            }

#if MEASURE_TIME == 2
            struct timeval te2;
            gettimeofday(&te2, NULL);
            long long time2 = te2.tv_sec * 1000000LL + te2.tv_usec;
            doubleLinkedListInsertTime += time2 - time1;
#endif

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

#if MEASURE_TIME == 2
            struct timeval te2;
            gettimeofday(&te2, NULL);
            long long time2 = te2.tv_sec * 1000000LL + te2.tv_usec;
            doubleLinkedListInsertTime += time2 - time1;
#endif

            return newNode;
        }
    }
    else
    {
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

#if MEASURE_TIME == 2
                struct timeval te2;
                gettimeofday(&te2, NULL);
                long long time2 = te2.tv_sec * 1000000LL + te2.tv_usec;
                doubleLinkedListInsertTime += time2 - time1;
#endif
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

#if MEASURE_TIME == 2
            struct timeval te2;
            gettimeofday(&te2, NULL);
            long long time2 = te2.tv_sec * 1000000LL + te2.tv_usec;
            doubleLinkedListInsertTime += time2 - time1;
#endif

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
            }
            else
                fprintf(stderr, "Error in %s line %i: insertIntoDoubleLinkedList - unexpected situation - node and list first node aren't the same when doesn't exists previous node. \n", (char *)__FILE__, __LINE__);

#if MEASURE_TIME == 2
            struct timeval te2;
            gettimeofday(&te2, NULL);
            long long time2 = te2.tv_sec * 1000000LL + te2.tv_usec;
            doubleLinkedListInsertTime += time2 - time1;
#endif

            return newNode;
        }
    }
}

void insertIntoDoubleLinkedList2(DoubleLinkedList *list, void *data, double (*f)(void *, void *))
{
    DoubleLinkedListNode *node = list->first;

#if MEASURE_TIME == 2
    struct timeval te1;
    gettimeofday(&te1, NULL);
    long long time1 = te1.tv_sec * 1000000LL + te1.tv_usec;
#endif

    if (node == NULL || list->first == NULL)
    {
        DoubleLinkedListNode *newNode = (DoubleLinkedListNode *)malloc(sizeof(DoubleLinkedListNode));
        newNode->data = data;
        newNode->next = NULL;
        newNode->prev = NULL;
        list->first = newNode;

#if MEASURE_TIME == 2
        struct timeval te2;
        gettimeofday(&te2, NULL);
        long long time2 = te2.tv_sec * 1000000LL + te2.tv_usec;
        doubleLinkedListInsertTime2 += time2 - time1;
#endif

        return;
    }

    DoubleLinkedListNode *newNode = (DoubleLinkedListNode *)malloc(sizeof(DoubleLinkedListNode));
    newNode->data = data;
    newNode->next = node;
    newNode->prev = NULL;

    if (newNode->next != NULL)
        newNode->next->prev = newNode;

    list->first = newNode;

#if MEASURE_TIME == 2
    struct timeval te2;
    gettimeofday(&te2, NULL);
    long long time2 = te2.tv_sec * 1000000LL + te2.tv_usec;
    doubleLinkedListInsertTime2 += time2 - time1;
#endif

    return;
}