#include "redBlackTree.h"

redBlackTreeNode* getSibling(redBlackTreeNode *node);
redBlackTreeNode* getUncle(redBlackTreeNode *node);
void rotateRight(redBlackTree *tree, redBlackTreeNode *node);
void rotateLeft(redBlackTree *tree, redBlackTreeNode *node);
void restoreColoursInRedBlackTree(redBlackTree *tree, redBlackTreeNode *node);
void removeWhenOneChildFromRedBlackTreeNode(redBlackTree *tree, redBlackTreeNode *node);
void replaceRedBlackTreeNode(redBlackTree *tree, redBlackTreeNode *node, redBlackTreeNode *child);
void removeCase1(redBlackTree *tree, redBlackTreeNode *node);
void removeCase2(redBlackTree *tree, redBlackTreeNode *node);
void removeCase3(redBlackTree *tree, redBlackTreeNode *node);
void removeCase4(redBlackTree *tree, redBlackTreeNode *node);
void removeCase5(redBlackTree *tree, redBlackTreeNode *node);
void removeCase6(redBlackTree *tree, redBlackTreeNode *node);