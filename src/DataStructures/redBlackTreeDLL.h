#ifndef REDBLACKTREEDLL_H
#define REDBLACKTREEDLL_H

#include <stdbool.h>
#include "../utilities.h"
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

redBlackTreeDLLNode* getSiblingDLL(redBlackTreeDLLNode *node);
redBlackTreeDLLNode* getUncleDLL(redBlackTreeDLLNode *node);
void rotateRightDLL(redBlackTreeDLL *tree, redBlackTreeDLLNode *node);
void rotateLeftDLL(redBlackTreeDLL *tree, redBlackTreeDLLNode *node);
redBlackTreeDLLNode* getFromRedBlackTreeDLL(redBlackTreeDLL *tree, void *data);
redBlackTreeDLLNode* insertIntoRedBlackTreeDLL(redBlackTreeDLL *tree, void *data);
void restoreColoursInRedBlackTreeDLL(redBlackTreeDLL *tree, redBlackTreeDLLNode *node);

void removeFromRedBlackTreeDLL(redBlackTreeDLL *tree, redBlackTreeDLLNode *node);

void removeWhenOneChildFromRedBlackTreeDLLNode(redBlackTreeDLL *tree, redBlackTreeDLLNode *node);
void replaceRedBlackTreeDLLNode(redBlackTreeDLL *tree, redBlackTreeDLLNode *node, redBlackTreeDLLNode *child);
void removeCase1DLL(redBlackTreeDLL *tree, redBlackTreeDLLNode *node);
void removeCase2DLL(redBlackTreeDLL *tree, redBlackTreeDLLNode *node);
void removeCase3DLL(redBlackTreeDLL *tree, redBlackTreeDLLNode *node);
void removeCase4DLL(redBlackTreeDLL *tree, redBlackTreeDLLNode *node);
void removeCase5DLL(redBlackTreeDLL *tree, redBlackTreeDLLNode *node);
void removeCase6DLL(redBlackTreeDLL *tree, redBlackTreeDLLNode *node);

redBlackTreeDLLNode* getNextNodeFromRedBlackTreeDLL(redBlackTreeDLL *tree, redBlackTreeDLLNode *node);
redBlackTreeDLLNode *getPrevNodeFromRedBlackTreeDLL(redBlackTreeDLL *tree, redBlackTreeDLLNode *node);
redBlackTreeDLLNode *minimumInRedBlackSubTreeDLL(redBlackTreeDLLNode *node);


#endif