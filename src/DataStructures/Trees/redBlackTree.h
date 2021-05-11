#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include <stdbool.h>

enum Colour 
{
    Red,
    Black
};

typedef struct redBlackTreeNode
{
    enum Colour colour;
    void *data;
    struct redBlackTreeNode *parent;
    struct redBlackTreeNode *left;
    struct redBlackTreeNode *right;
} redBlackTreeNode;

typedef struct redBlackTree
{
    double (*compare)(void *, void *);
    void (*freeData)(void *);
    redBlackTreeNode *first;
    int count;
} redBlackTree;

redBlackTree* newRedBlackTree(double (*compare)(void *, void *), void (*freeData)(void *));
void removeRedBlackTree(redBlackTree *tree, bool removeData);

redBlackTreeNode* getFromRedBlackTree(redBlackTree *tree, void *data);
redBlackTreeNode* insertIntoRedBlackTree(redBlackTree *tree, void *data);
void removeFromRedBlackTree(redBlackTree *tree, redBlackTreeNode *node);

redBlackTreeNode* getNextNodeFromRedBlackTree(redBlackTree *tree, redBlackTreeNode *node);
redBlackTreeNode *getPrevNodeFromRedBlackTree(redBlackTree *tree, redBlackTreeNode *node);
redBlackTreeNode *minimumInRedBlackSubTree(redBlackTreeNode *node);
redBlackTreeNode *maximumInRedBlackSubTree(redBlackTreeNode *node);

redBlackTreeNode *getFromRedBlackTreeFirstSmaller(redBlackTree *tree, void *data);
redBlackTreeNode *getFromRedBlackTreeFirstBigger(redBlackTree *tree, void *data);

#endif