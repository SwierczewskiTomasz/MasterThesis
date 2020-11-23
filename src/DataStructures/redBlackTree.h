#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include <stdbool.h>
#include "../utilities.h"

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
    redBlackTreeNode *first;
    int count;
} redBlackTree;

redBlackTree* newRedBlackTree(double (*compare)(void *, void *));
void removeRedBlackTree(redBlackTree *tree, bool removeData);

redBlackTreeNode* getSibling(redBlackTreeNode *node);
redBlackTreeNode* getUncle(redBlackTreeNode *node);
void rotateRight(redBlackTree *tree, redBlackTreeNode *node);
void rotateLeft(redBlackTree *tree, redBlackTreeNode *node);
redBlackTreeNode* getFromRedBlackTree(redBlackTree *tree, void *data);
redBlackTreeNode* insertIntoRedBlackTree(redBlackTree *tree, void *data);
void restoreColoursInRedBlackTree(redBlackTree *tree, redBlackTreeNode *node);
void removeFromRedBlackTree(redBlackTree *tree, redBlackTreeNode *node);

void removeCase6(redBlackTree *tree, redBlackTreeNode *node);
void removeCase5(redBlackTree *tree, redBlackTreeNode *node);
void removeCase4(redBlackTree *tree, redBlackTreeNode *node);
void removeCase3(redBlackTree *tree, redBlackTreeNode *node);
void removeCase2(redBlackTree *tree, redBlackTreeNode *node);
void removeCase1(redBlackTree *tree, redBlackTreeNode *node);

redBlackTreeNode* getNextNodeFromRedBlackTree(redBlackTree *tree, redBlackTreeNode *node);
redBlackTreeNode *minimumInRedBlackSubTree(redBlackTreeNode *node);

#endif