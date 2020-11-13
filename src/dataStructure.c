#include "dataStructure.h"
#include <stdio.h>
#include <sys/time.h>

long long insertTime = 0;
long long insertTime2 = 0;
long long removeTime = 0;

void *removeFromDoubleLinkedList(DoubleLinkedList *list, DoubleLinkedListNode *node)
{
    // This function return next node from remove or previous, if next doesn't exist
    struct timeval te1;
    gettimeofday(&te1, NULL);
    long long time1 = te1.tv_sec * 1000000LL + te1.tv_usec / 1000;

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
    long long time2 = te2.tv_sec * 1000000LL + te2.tv_usec / 1000;
    removeTime += time2 - time1;

    return result;
}

DoubleLinkedListNode *insertIntoDoubleLinkedList(DoubleLinkedList *list, DoubleLinkedListNode *node, void *data, double (*f)(void *, void *))
{
    // printf("Inside of function insertIntoDoubleLinkedList\n");
    // f(data, node->data);
    // printf("Mayday?\n");

    struct timeval te1;
    gettimeofday(&te1, NULL);
    long long time1 = te1.tv_sec * 1000000LL + te1.tv_usec / 1000;

    if (node == NULL || list->first == NULL)
    {
        DoubleLinkedListNode *newNode = (DoubleLinkedListNode *)malloc(sizeof(DoubleLinkedListNode));
        newNode->data = data;
        newNode->next = NULL;
        newNode->prev = NULL;
        list->first = newNode;

        struct timeval te2;
        gettimeofday(&te2, NULL);
        long long time2 = te2.tv_sec * 1000000LL + te2.tv_usec / 1000;
        insertTime += time2 - time1;

        return newNode;
    }

    // DoubleLinkedListNode *newNode = (DoubleLinkedListNode *)malloc(sizeof(DoubleLinkedListNode));
    // newNode->data = data;
    // newNode->next = list->first;
    // newNode->prev = NULL;
    // // node->next = newNode;
    // if (newNode->next != NULL)
    //     newNode->next->prev = newNode;

    // list->first = newNode;

    // struct timeval te2;
    // gettimeofday(&te2, NULL);
    // long long time2 = te2.tv_sec * 1000000LL + te2.tv_usec / 1000;
    // insertTime += time2 - time1;

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

                struct timeval te2;
                gettimeofday(&te2, NULL);
                long long time2 = te2.tv_sec * 1000000LL + te2.tv_usec / 1000;
                insertTime += time2 - time1;

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

            struct timeval te2;
            gettimeofday(&te2, NULL);
            long long time2 = te2.tv_sec * 1000000LL + te2.tv_usec / 1000;
            insertTime += time2 - time1;

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

            struct timeval te2;
            gettimeofday(&te2, NULL);
            long long time2 = te2.tv_sec * 1000000LL + te2.tv_usec / 1000;
            insertTime += time2 - time1;
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

                struct timeval te2;
                gettimeofday(&te2, NULL);
                long long time2 = te2.tv_sec * 1000000LL + te2.tv_usec / 1000;
                insertTime += time2 - time1;
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

            struct timeval te2;
            gettimeofday(&te2, NULL);
            long long time2 = te2.tv_sec * 1000000LL + te2.tv_usec / 1000;
            insertTime += time2 - time1;
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

            struct timeval te2;
            gettimeofday(&te2, NULL);
            long long time2 = te2.tv_sec * 1000000LL + te2.tv_usec / 1000;
            insertTime += time2 - time1;

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

    struct timeval te1;
    gettimeofday(&te1, NULL);
    long long time1 = te1.tv_sec * 1000000LL + te1.tv_usec / 1000;

    // printf("1 \n");

    if (node == NULL || list->first == NULL)
    {
        DoubleLinkedListNode *newNode = (DoubleLinkedListNode *)malloc(sizeof(DoubleLinkedListNode));
        newNode->data = data;
        newNode->next = NULL;
        newNode->prev = NULL;
        list->first = newNode;

        struct timeval te2;
        gettimeofday(&te2, NULL);
        long long time2 = te2.tv_sec * 1000000LL + te2.tv_usec / 1000;
        insertTime2 += time2 - time1;
        return;
    }

    DoubleLinkedListNode *newNode = (DoubleLinkedListNode *)malloc(sizeof(DoubleLinkedListNode));
    newNode->data = data;
    newNode->next = node;
    newNode->prev = NULL;
    // node->next = newNode;
    if (newNode->next != NULL)
        newNode->next->prev = newNode;

    list->first = newNode;

    // printf("1\n");

    struct timeval te2;
    gettimeofday(&te2, NULL);
    long long time2 = te2.tv_sec * 1000000LL + te2.tv_usec / 1000;
    insertTime2 += time2 - time1;

    return;

    if (list->first == NULL)
    {
        DoubleLinkedListNode *newNode = (DoubleLinkedListNode *)malloc(sizeof(DoubleLinkedListNode));
        newNode->data = data;
        newNode->next = NULL;
        newNode->prev = NULL;
        list->first = newNode;

        struct timeval te2;
        gettimeofday(&te2, NULL);
        long long time2 = te2.tv_sec * 1000000LL + te2.tv_usec / 1000;
        insertTime2 += time2 - time1;

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

                struct timeval te2;
                gettimeofday(&te2, NULL);
                long long time2 = te2.tv_sec * 1000000LL + te2.tv_usec / 1000;
                insertTime2 += time2 - time1;

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

            struct timeval te2;
            gettimeofday(&te2, NULL);
            long long time2 = te2.tv_sec * 1000000LL + te2.tv_usec / 1000;
            insertTime2 += time2 - time1;

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

            struct timeval te2;
            gettimeofday(&te2, NULL);
            long long time2 = te2.tv_sec * 1000000LL + te2.tv_usec / 1000;
            insertTime2 += time2 - time1;

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

                struct timeval te2;
                gettimeofday(&te2, NULL);
                long long time2 = te2.tv_sec * 1000000LL + te2.tv_usec / 1000;
                insertTime2 += time2 - time1;

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

            struct timeval te2;
            gettimeofday(&te2, NULL);
            long long time2 = te2.tv_sec * 1000000LL + te2.tv_usec / 1000;
            insertTime2 += time2 - time1;

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

            struct timeval te2;
            gettimeofday(&te2, NULL);
            long long time2 = te2.tv_sec * 1000000LL + te2.tv_usec / 1000;
            insertTime2 += time2 - time1;

            return newNode;
        }
    }
}

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