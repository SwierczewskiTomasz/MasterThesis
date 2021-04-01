#ifndef LUTRBTDLL_H
#define LUTRBTDLL_H

typedef struct LUTRBTDLL
{
    double (*compare)(void *, void *);
    void (*freeData)(void *);
    
} LUTRBTDLL;

typedef struct redBlackTreeDLLNode
{
    enum Colour colour;
    void *data;
    struct redBlackTreeDLLNode *parent;
    struct redBlackTreeDLLNode *left;
    struct redBlackTreeDLLNode *right;
    struct redBlackTreeDLLNode *next;
    struct redBlackTreeDLLNode *prev;
} redBlackTreeDLLNode;

typedef struct redBlackTreeDLL
{
    double (*compare)(void *, void *);
    void (*freeData)(void *);
    redBlackTreeDLLNode *first;
    int count;
} redBlackTreeDLL;

#endif