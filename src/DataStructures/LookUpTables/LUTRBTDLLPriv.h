#ifndef LUTRBTDLLPRIV_H
#define LUTRBTDLLPRIV_H

#include "LUTRBTDLL.h"

void restoreColoursInLUTRBTDLL(LUTRBTDLL *tree, LUTRBTDLLNode *node);
LUTRBTDLLNode *insertIntoLUTRBTDLLAdditional(LUTRBTDLL *table, Simplex *simplex);
void removeLUTRBTDLLTree(LUTRBTDLL *tree, bool removeData);
LUTRBTDLLNode *getSiblingLUTRBTDLL(LUTRBTDLLNode *node);
LUTRBTDLLNode *getUncleLUTRBTDLL(LUTRBTDLLNode *node);
void rotateRightLUTRBTDLL(LUTRBTDLL *tree, LUTRBTDLLNode *node);
void rotateLeftLUTRBTDLL(LUTRBTDLL *tree, LUTRBTDLLNode *node);
LUTRBTDLLNode *minimumInSubTreeLUTRBTDLL(LUTRBTDLLNode *node);
void removeFromLUTRBTDLLTree(LUTRBTDLL *tree, LUTRBTDLLNode *node);
void removeWhenOneChildFromLUTRBTDLLNode(LUTRBTDLL *tree, LUTRBTDLLNode *node);
void replaceLUTRBTDLLNode(LUTRBTDLL *tree, LUTRBTDLLNode *node, LUTRBTDLLNode *child);
void removeCase1LUTRBTDLL(LUTRBTDLL *tree, LUTRBTDLLNode *node);
void removeCase2LUTRBTDLL(LUTRBTDLL *tree, LUTRBTDLLNode *node);
void removeCase3LUTRBTDLL(LUTRBTDLL *tree, LUTRBTDLLNode *node);
void removeCase4LUTRBTDLL(LUTRBTDLL *tree, LUTRBTDLLNode *node);
void removeCase5LUTRBTDLL(LUTRBTDLL *tree, LUTRBTDLLNode *node);
void removeCase6LUTRBTDLL(LUTRBTDLL *tree, LUTRBTDLLNode *node);

#endif