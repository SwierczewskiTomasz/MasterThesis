#ifndef REDBLACKTREEDLL_H
#define REDBLACKTREEDLL_H

#include <stdbool.h>
#include "redBlackTree.h"

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

redBlackTreeDLL* newRedBlackTreeDLL(double (*compare)(void *, void *), void (*freeData)(void *));
void removeRedBlackTreeDLL(redBlackTreeDLL *tree, bool removeData);

redBlackTreeDLLNode* getFromRedBlackTreeDLL(redBlackTreeDLL *tree, void *data);
redBlackTreeDLLNode* insertIntoRedBlackTreeDLL(redBlackTreeDLL *tree, void *data);
void removeFromRedBlackTreeDLL(redBlackTreeDLL *tree, redBlackTreeDLLNode *node);

redBlackTreeDLLNode* getNextNodeFromRedBlackTreeDLL(redBlackTreeDLL *tree, redBlackTreeDLLNode *node);
redBlackTreeDLLNode *getPrevNodeFromRedBlackTreeDLL(redBlackTreeDLL *tree, redBlackTreeDLLNode *node);
redBlackTreeDLLNode *minimumInRedBlackSubTreeDLL(redBlackTreeDLLNode *node);

redBlackTreeDLLNode *getFromRedBlackTreeFirstSmallerDLL(redBlackTreeDLL *tree, void *data);
redBlackTreeDLLNode *getFromRedBlackTreeFirstBiggerDLL(redBlackTreeDLL *tree, void *data);

#endif