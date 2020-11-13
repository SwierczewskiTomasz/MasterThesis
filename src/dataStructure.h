#include <stdlib.h>

long long extern insertTime;
long long extern insertTime2;
long long extern removeTime;

typedef struct DataStructure
{
    void* root;
    void (*insert)(void *, void *);
    void* (*get)(void *, void *);
    void (*remove)(void *, void *);
} DataStructure;

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

void* getNextNode(void *node);

void* getDataFromNode(void *node);