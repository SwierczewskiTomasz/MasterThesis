#include <stdlib.h>
#include "../../Utilities/utilities.h"
#include "LUTRBTDLL.h"
#include "LUTRBTDLLPriv.h"


void removeLUTRBTDLLTree(LUTRBTDLL *tree, bool removeData)
{
    LUTRBTDLLNode *node = tree->first;

    if (node == NULL)
    {
        free(tree);
        return;
    }

    while (node != NULL)
    {
        if (node->left != NULL)
        {
            node = node->left;
        }
        else
        {
            if (node->right != NULL)
            {
                node = node->right;
            }
            else
            {
                LUTRBTDLLNode *toRemoveNode = node;
                node = node->parent;
                if (node == NULL)
                {
                    tree->first = NULL;
                    if (removeData)
                        tree->freeData(toRemoveNode->data);
                    free(toRemoveNode);
                    free(tree);
                    return;
                }

                if (node->left == toRemoveNode)
                    node->left = NULL;
                else
                    node->right = NULL;

                if (removeData)
                    tree->freeData(toRemoveNode->data);
                free(toRemoveNode);
            }
        }
    }
}

LUTRBTDLLNode *getSiblingLUTRBTDLL(LUTRBTDLLNode *node)
{
    if (node->parent == NULL)
        return NULL;

    if (node->parent->left == node)
        return node->parent->right;
    else
        return node->parent->left;
}

LUTRBTDLLNode *getUncleLUTRBTDLL(LUTRBTDLLNode *node)
{
    if (node->parent == NULL)
        return NULL;
    return getSiblingLUTRBTDLL(node->parent);
}

void rotateRightLUTRBTDLL(LUTRBTDLL *tree, LUTRBTDLLNode *node)
{
    if (node == NULL)
        return;

    if (node->left == NULL)
        return;

    if (node->parent == NULL)
        tree->first = node->left;
    else if (node->parent->left == node)
        node->parent->left = node->left;
    else
        node->parent->right = node->left;

    node->left->parent = node->parent;
    node->parent = node->left;
    node->left = node->left->right;

    if (node->left != NULL)
        node->left->parent = node;

    node->parent->right = node;
}

void rotateLeftLUTRBTDLL(LUTRBTDLL *tree, LUTRBTDLLNode *node)
{
    if (node == NULL)
        return;

    if (node->right == NULL)
        return;

    if (node->parent == NULL)
        tree->first = node->right;
    else if (node->parent->left == node)
        node->parent->left = node->right;
    else
        node->parent->right = node->right;

    node->right->parent = node->parent;
    node->parent = node->right;
    node->right = node->right->left;

    if (node->right != NULL)
        node->right->parent = node;

    node->parent->left = node;
}

LUTRBTDLLNode *getFromLUTRBTDLL(LUTRBTDLL *table, Simplex *simplex)
{
#if MEASURE_CALLS == 1
    LUTRBTDLLGetCount++;
#endif

    if (simplex == NULL)
    {
        return NULL;
    }

    LUTRBTDLLNode *current = table->first;

    while (current != NULL)
    {
        if (current->data == simplex)
        {
            return current;
        }
        double result = table->compare(current->data, simplex);
        if (result > 0)
            current = current->left;
        else if (result < 0)
            current = current->right;
        else
            return current;
    }

    return NULL;
}

void restoreColoursInLUTRBTDLL(LUTRBTDLL *tree, LUTRBTDLLNode *node)
{
    while (1)
    {
        if (node->parent == NULL)
        {
            node->colour = Black;
            return;
        }
        else if (node->parent->colour == Black)
        {
            //Tree is still valid.
            return;
        }
        else if (getUncleLUTRBTDLL(node) != NULL && getUncleLUTRBTDLL(node)->colour == Red)
        {
            node->parent->colour = Black;
            getUncleLUTRBTDLL(node)->colour = Black;
            node->parent->parent->colour = Red;

            // Here is loop, we are moving 2 nodes closer to root. We must restore Colours,
            // beacuse for example node->parent->parent can be a root and we just set Colour
            // on Red.
            node = node->parent->parent;
        }
        else
        {
            if (node == node->parent->right && node->parent == node->parent->parent->left)
            {
                rotateLeftLUTRBTDLL(tree, node->parent);
                node = node->left;
            }
            else if (node == node->parent->left && node->parent == node->parent->parent->right)
            {
                rotateRightLUTRBTDLL(tree, node->parent);
                node = node->right;
            }

            LUTRBTDLLNode *p = node->parent;
            LUTRBTDLLNode *g = node->parent->parent;

            if (node == p->left)
            {
                rotateRightLUTRBTDLL(tree, g);
            }
            else
            {
                rotateLeftLUTRBTDLL(tree, g);
            }

            p->colour = Black;
            g->colour = Red;

            return;
        }
    }
}

LUTRBTDLLNode *insertIntoLUTRBTDLLAdditional(LUTRBTDLL *table, Simplex *simplex)
{
#if MEASURE_CALLS == 1
    LUTRBTDLLInsertCount++;
#endif

    LUTRBTDLLNode *current = table->first;

    while (current != NULL)
    {
        if (current->data == simplex)
        {
            fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: insertIntoLUTRBTDLL function. \n", (char *)__FILE__, __LINE__);
            fprintf(stderr, "Trying to insert simplex %14p, which one exists in table %14p. \n\n", simplex, table);

            table->count--;

            return current;
        }
        double result = table->compare(current->data, simplex);
        if (result > 0)
        {
            // printf("Go on left\n");
            if (current->left == NULL)
            {
                // printf("Insert at left\n");
                LUTRBTDLLNode *newNode = (LUTRBTDLLNode *)malloc(sizeof(LUTRBTDLLNode));
                current->left = newNode;
                newNode->left = NULL;
                newNode->right = NULL;
                newNode->parent = current;
                newNode->data = simplex;
                newNode->colour = Red;
                newNode->prev = current->prev;
                newNode->next = current;
                current->prev = newNode;
                if (newNode->prev != NULL)
                    newNode->prev->next = newNode;
                restoreColoursInLUTRBTDLL(table, newNode);

                return newNode;
            }
            else
            {
                current = current->left;
            }
        }
        else if (result < 0)
        {
            // printf("Go on right\n");
            if (current->right == NULL)
            {
                // printf("Insert at right\n");
                LUTRBTDLLNode *newNode = (LUTRBTDLLNode *)malloc(sizeof(LUTRBTDLLNode));
                current->right = newNode;
                newNode->left = NULL;
                newNode->right = NULL;
                newNode->parent = current;
                newNode->data = simplex;
                newNode->colour = Red;
                newNode->prev = current;
                newNode->next = current->next;
                current->next = newNode;
                if (newNode->next != NULL)
                    newNode->next->prev = newNode;
                restoreColoursInLUTRBTDLL(table, newNode);

                return newNode;
            }
            else
            {
                current = current->right;
            }
        }
        else
        {
            return NULL;
        }
    }

    LUTRBTDLLNode *newNode = (LUTRBTDLLNode *)malloc(sizeof(LUTRBTDLLNode));
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;
    newNode->data = simplex;
    newNode->colour = Black;
    newNode->next = NULL;
    newNode->prev = NULL;
    table->first = newNode;

    return newNode;
}

LUTRBTDLLNode *minimumInSubTreeLUTRBTDLL(LUTRBTDLLNode *node)
{
    LUTRBTDLLNode *current = node;

    if (current == NULL)
        return NULL;

    while (current->left != NULL)
        current = current->left;

    return current;
}

void removeFromLUTRBTDLLTree(LUTRBTDLL *tree, LUTRBTDLLNode *node)
{
#if MEASURE_CALLS == 1
    LUTRBTDLLRemoveCount++;
#endif

    if (node == NULL)
    {
        return;
    }

    if (node->next != NULL)
        node->next->prev = node->prev;
    if (node->prev != NULL)
        node->prev->next = node->next;

    if (node->left != NULL && node->right != NULL)
    {
        LUTRBTDLLNode *newNode = minimumInSubTreeLUTRBTDLL(node->right);
        LUTRBTDLLNode *copy = (LUTRBTDLLNode *)malloc(sizeof(LUTRBTDLLNode));

        copy->colour = newNode->colour;
        copy->left = newNode->left;
        copy->parent = newNode->parent;
        copy->right = newNode->right;

        newNode->colour = node->colour;
        newNode->left = node->left;
        newNode->parent = node->parent;
        if (node->right != newNode)
        {
            newNode->right = node->right;
        }
        else
        {
            newNode->right = node;
        }

        if (node->right != NULL)
        {
            if (node->right != newNode)
            {
                node->right->parent = newNode;
            }
            else
            {
                copy->parent = newNode;
            }
        }

        if (node->left != NULL)
        {
            node->left->parent = newNode;
        }

        if (node->parent == NULL)
        {
            tree->first = newNode;
        }
        else
        {
            if (node->parent->left == node)
            {
                node->parent->left = newNode;
            }
            else
            {
                node->parent->right = newNode;
            }
        }

        if (copy->parent != NULL)
        {
            if (copy->parent->left == newNode)
            {
                copy->parent->left = node;
            }
            else
            {
                copy->parent->right = node;
            }
        }
        else
        {
            fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: removeFromLUTRBTDLLTree function. Child don't have parent. \n", (char *)__FILE__, __LINE__);
        }
        node->colour = copy->colour;
        node->left = copy->left;
        node->parent = copy->parent;
        node->right = copy->right;

        free(copy);
    }

    removeWhenOneChildFromLUTRBTDLLNode(tree, node);

    // free(node);
    tree->count--;
}

// For this function node should contain only one non-leaf child. Or at most one.
void removeWhenOneChildFromLUTRBTDLLNode(LUTRBTDLL *tree, LUTRBTDLLNode *node)
{
    LUTRBTDLLNode *child = node->left != NULL ? node->left : node->right;

    if (node->colour == Black)
    {
        if (child != NULL)
        {
            if (child->colour == Red)
            {
                child->colour = Black;
            }
            else
            {
                fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: removeWhenOneChildFromLUTRBTDLLNode function. Child and node shouldn't be black. \n", (char *)__FILE__, __LINE__);
                removeCase1LUTRBTDLL(tree, child);
            }
        }
        else
        {
            removeCase1LUTRBTDLL(tree, node);
        }
    }
    replaceLUTRBTDLLNode(tree, node, child);
}

void replaceLUTRBTDLLNode(LUTRBTDLL *tree, LUTRBTDLLNode *node, LUTRBTDLLNode *child)
{
    if (child != NULL)
    {
        child->parent = node->parent;
    }
    if (node->parent == NULL)
    {
        tree->first = child;
    }
    else
    {
        if (node == node->parent->left)
            node->parent->left = child;
        else
            node->parent->right = child;
    }
}

void removeCase1LUTRBTDLL(LUTRBTDLL *tree, LUTRBTDLLNode *node)
{
    if (node->parent != NULL)
    {
        removeCase2LUTRBTDLL(tree, node);
    }
}

void removeCase2LUTRBTDLL(LUTRBTDLL *tree, LUTRBTDLLNode *node)
{
    LUTRBTDLLNode *sibling = getSiblingLUTRBTDLL(node);

    if (sibling == NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: removeCase2 function. Sibling should exists. \n", (char *)__FILE__, __LINE__);
    }

    if (sibling->colour == Red)
    {
        node->parent->colour = Red;
        sibling->colour = Black;
        if (node == node->parent->left)
            rotateLeftLUTRBTDLL(tree, node->parent);
        else
            rotateRightLUTRBTDLL(tree, node->parent);
    }

    removeCase3LUTRBTDLL(tree, node);
}

void removeCase3LUTRBTDLL(LUTRBTDLL *tree, LUTRBTDLLNode *node)
{
    LUTRBTDLLNode *sibling = getSiblingLUTRBTDLL(node);

    if (sibling == NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: removeCase3 function. Sibling should exists. \n", (char *)__FILE__, __LINE__);
    }

    if (node->parent->colour == Black && sibling->colour == Black)
    {
        if (sibling->left == NULL)
        {
            if (sibling->right == NULL)
            {
                sibling->colour = Red;

                //Here is loop. Try to analyze this and look how much time it can take.
                removeCase1LUTRBTDLL(tree, node->parent);
            }
            else if (sibling->right->colour == Black)
            {
                sibling->colour = Red;

                //Here is loop. Try to analyze this and look how much time it can take.
                removeCase1LUTRBTDLL(tree, node->parent);
            }
            else
            {
                removeCase4LUTRBTDLL(tree, node);
            }
        }
        else if (sibling->left->colour == Black)
        {
            if (sibling->right == NULL)
            {
                sibling->colour = Red;

                //Here is loop. Try to analyze this and look how much time it can take.
                removeCase1LUTRBTDLL(tree, node->parent);
            }
            else if (sibling->right->colour == Black)
            {
                sibling->colour = Red;

                //Here is loop. Try to analyze this and look how much time it can take.
                removeCase1LUTRBTDLL(tree, node->parent);
            }
            else
            {
                removeCase4LUTRBTDLL(tree, node);
            }
        }
        else
        {
            removeCase4LUTRBTDLL(tree, node);
        }
    }
    else
    {
        removeCase4LUTRBTDLL(tree, node);
    }
}

void removeCase4LUTRBTDLL(LUTRBTDLL *tree, LUTRBTDLLNode *node)
{
    LUTRBTDLLNode *sibling = getSiblingLUTRBTDLL(node);

    if (sibling == NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: removeCase4 function. Sibling should exists. \n", (char *)__FILE__, __LINE__);
    }

    if (node->parent->colour == Red && sibling->colour == Black)
    {
        if (sibling->left == NULL)
        {
            if (sibling->right == NULL)
            {
                sibling->colour = Red;
                node->parent->colour = Black;
            }
            else if (sibling->right->colour == Black)
            {
                sibling->colour = Red;
                node->parent->colour = Black;
            }
            else
            {
                removeCase5LUTRBTDLL(tree, node);
            }
        }
        else if (sibling->left->colour == Black)
        {
            if (sibling->right == NULL)
            {
                sibling->colour = Red;
                node->parent->colour = Black;
            }
            else if (sibling->right->colour == Black)
            {
                sibling->colour = Red;
                node->parent->colour = Black;
            }
            else
            {
                removeCase5LUTRBTDLL(tree, node);
            }
        }
        else
        {
            removeCase5LUTRBTDLL(tree, node);
        }
    }
    else
    {
        removeCase5LUTRBTDLL(tree, node);
    }
}

void removeCase5LUTRBTDLL(LUTRBTDLL *tree, LUTRBTDLLNode *node)
{
    LUTRBTDLLNode *sibling = getSiblingLUTRBTDLL(node);

    if (sibling == NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: removeCase5 function. Sibling should exists. \n", (char *)__FILE__, __LINE__);
    }

    if (sibling->colour == Black)
    {
        if (node == node->parent->left)
        {
            if (sibling->left != NULL)
            {
                if (sibling->left->colour == Red)
                {
                    if (sibling->right != NULL)
                    {
                        if (sibling->right->colour == Black)
                        {
                            sibling->colour = Red;
                            sibling->left->colour = Black;
                            rotateRightLUTRBTDLL(tree, sibling);
                        }
                    }
                    else
                    {

                        sibling->colour = Red;
                        sibling->left->colour = Black;
                        rotateRightLUTRBTDLL(tree, sibling);
                    }
                }
            }
        }
        else // if (node == node->parent->right)
        {
            if (sibling->right != NULL)
            {
                if (sibling->right->colour == Red)
                {
                    if (sibling->left != NULL)
                    {
                        if (sibling->left->colour == Black)
                        {
                            sibling->colour = Red;
                            sibling->right->colour = Black;
                            rotateLeftLUTRBTDLL(tree, sibling);
                        }
                    }
                    else
                    {
                        sibling->colour = Red;
                        sibling->right->colour = Black;
                        rotateLeftLUTRBTDLL(tree, sibling);
                    }
                }
            }
        }
    }

    removeCase6LUTRBTDLL(tree, node);
}

void removeCase6LUTRBTDLL(LUTRBTDLL *tree, LUTRBTDLLNode *node)
{
    LUTRBTDLLNode *sibling = getSiblingLUTRBTDLL(node);

    if (sibling == NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: removeCase6 function. Sibling should exists. \n", (char *)__FILE__, __LINE__);
    }

    sibling->colour = node->parent->colour;
    node->parent->colour = Black;

    if (node == node->parent->left)
    {
        if (sibling->right != NULL)
        {
            sibling->right->colour = Black;
        }
        rotateLeftLUTRBTDLL(tree, node->parent);
    }
    else
    {
        if (sibling->left != NULL)
        {
            sibling->left->colour = Black;
        }
        rotateRightLUTRBTDLL(tree, node->parent);
    }
}

LUTRBTDLLNode *getNextNodeFromLUTRBTDLL(LUTRBTDLLNode *node)
{
#if MEASURE_CALLS == 1
    LUTRBTDLLNextNodeCount++;
#endif

    return node->next;
}

LUTRBTDLLNode *getPrevNodeFromLUTRBTDLL(LUTRBTDLLNode *node)
{
#if MEASURE_CALLS == 1
    LUTRBTDLLPrevNodeCount++;
#endif
    return node->prev;
}
