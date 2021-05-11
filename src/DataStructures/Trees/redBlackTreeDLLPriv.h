#include "redBlackTreeDLL.h"

void restoreColoursInRedBlackTreeDLL(redBlackTreeDLL *tree, redBlackTreeDLLNode *node);
redBlackTreeDLLNode* getSiblingDLL(redBlackTreeDLLNode *node);
redBlackTreeDLLNode* getUncleDLL(redBlackTreeDLLNode *node);
void rotateRightDLL(redBlackTreeDLL *tree, redBlackTreeDLLNode *node);
void rotateLeftDLL(redBlackTreeDLL *tree, redBlackTreeDLLNode *node);
void removeWhenOneChildFromRedBlackTreeDLLNode(redBlackTreeDLL *tree, redBlackTreeDLLNode *node);
void replaceRedBlackTreeDLLNode(redBlackTreeDLL *tree, redBlackTreeDLLNode *node, redBlackTreeDLLNode *child);
void removeCase1DLL(redBlackTreeDLL *tree, redBlackTreeDLLNode *node);
void removeCase2DLL(redBlackTreeDLL *tree, redBlackTreeDLLNode *node);
void removeCase3DLL(redBlackTreeDLL *tree, redBlackTreeDLLNode *node);
void removeCase4DLL(redBlackTreeDLL *tree, redBlackTreeDLLNode *node);
void removeCase5DLL(redBlackTreeDLL *tree, redBlackTreeDLLNode *node);
void removeCase6DLL(redBlackTreeDLL *tree, redBlackTreeDLLNode *node);