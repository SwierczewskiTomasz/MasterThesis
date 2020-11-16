#if defined(WIND32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <time.h>
#include <Windows.h>
#else
#include <sys/time.h>
#include <unistd.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include "redBlackTree.h"

redBlackTreeNode *getSibling(redBlackTreeNode *node)
{
    if (node->parent == NULL)
        return NULL;

    if (node->parent->left == node)
        return node->parent->right;
    else
        return node->parent->left;
}

redBlackTreeNode *getUncle(redBlackTreeNode *node)
{
    if (node->parent == NULL)
        return NULL;
    return getSibling(node->parent);
}

void rotateRight(redBlackTree *tree, redBlackTreeNode *node)
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

    if (node->parent->right != NULL)
        node->parent->right->parent = node;

    node->parent->right = node;
}

void rotateLeft(redBlackTree *tree, redBlackTreeNode *node)
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

    if (node->parent->left != NULL)
        node->parent->left->parent = node;

    node->parent->left = node;
}

redBlackTreeNode *getFromRedBlackTree(redBlackTree *tree, void *data)
{
#if MEASURE_TIME == 1
    struct timeval start;
    gettimeofday(&start, NULL);
    long long startTime = start.tv_sec * 1000000LL + start.tv_usec;
#endif

    redBlackTreeNode *current = tree->first;

    while (current != NULL)
    {
        if (current->data == data)
        {

#if MEASURE_TIME == 1
            struct timeval end;
            gettimeofday(&end, NULL);
            long long endTime = end.tv_sec * 1000000LL + end.tv_usec;
            redBlackTreeGetTime += endTime - startTime;
#endif

            return current;
        }
        double result = tree->compare(current->data, data);
        if (result > 0)
            current = current->left;
        else if (result < 0)
            current = current->right;
        else
            printf("Error in %s line %i: getFromRedBlackTree - situation with exact the same data, but different point in tree shouldn't happen. For this implementation. \n", (char *)__FILE__, __LINE__);
    }

#if MEASURE_TIME == 1
    struct timeval end;
    gettimeofday(&end, NULL);
    long long endTime = end.tv_sec * 1000000LL + end.tv_usec;
    redBlackTreeGetTime += endTime - startTime;
#endif

    return NULL;
}

redBlackTreeNode *insertIntoRedBlackTree(redBlackTree *tree, void *data)
{
#if MEASURE_TIME == 1
    struct timeval start;
    gettimeofday(&start, NULL);
    long long startTime = start.tv_sec * 1000000LL + start.tv_usec;
#endif

    redBlackTreeNode *current = tree->first;

    while (current != NULL)
    {
        if (current->data == data)
        {
            printf("Error\n");

#if MEASURE_TIME == 1
            struct timeval end;
            gettimeofday(&end, NULL);
            long long endTime = end.tv_sec * 1000000LL + end.tv_usec;
            redBlackTreeInsertTime += endTime - startTime;
#endif

            return current;
        }
        double result = tree->compare(current->data, data);
        if (result > 0)
        {
            // printf("Go on left\n");
            if (current->left == NULL)
            {
                // printf("Insert at left\n");
                redBlackTreeNode *newNode = (redBlackTreeNode *)malloc(sizeof(redBlackTreeNode));
                current->left = newNode;
                newNode->left = NULL;
                newNode->right = NULL;
                newNode->parent = current;
                newNode->data = data;
                newNode->colour = Red;
                restoreColoursInRedBlackTree(tree, newNode);
                // printf("Inserted\n");
                // printRedBlackTree(tree);

#if MEASURE_TIME == 1
                struct timeval end;
                gettimeofday(&end, NULL);
                long long endTime = end.tv_sec * 1000000LL + end.tv_usec;
                redBlackTreeInsertTime += endTime - startTime;
#endif

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
                redBlackTreeNode *newNode = (redBlackTreeNode *)malloc(sizeof(redBlackTreeNode));
                current->right = newNode;
                newNode->left = NULL;
                newNode->right = NULL;
                newNode->parent = current;
                newNode->data = data;
                newNode->colour = Red;
                restoreColoursInRedBlackTree(tree, newNode);
                // printf("Inserted\n");
                // printRedBlackTree(tree);

#if MEASURE_TIME == 1
                struct timeval end;
                gettimeofday(&end, NULL);
                long long endTime = end.tv_sec * 1000000LL + end.tv_usec;
                redBlackTreeInsertTime += endTime - startTime;
#endif

                return newNode;
            }
            else
            {
                current = current->right;
            }
        }
        else
        {
            // printf("Error in %s line %i: insertIntoRedBlackTree - situation with exact the same data is in tree shouldn't happen. For this implementation. \n", (char *)__FILE__, __LINE__);

#if MEASURE_TIME == 1
            struct timeval end;
            gettimeofday(&end, NULL);
            long long endTime = end.tv_sec * 1000000LL + end.tv_usec;
            redBlackTreeInsertTime += endTime - startTime;
#endif

            return NULL;
        }
    }
    
    redBlackTreeNode *newNode = (redBlackTreeNode *)malloc(sizeof(redBlackTreeNode));
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;
    newNode->data = data;
    newNode->colour = Black;
    tree->first = newNode;

    // printf("Create new tree-first \n");
    // printRedBlackTree(tree);

#if MEASURE_TIME == 1
    struct timeval end;
    gettimeofday(&end, NULL);
    long long endTime = end.tv_sec * 1000000LL + end.tv_usec;
    redBlackTreeInsertTime += endTime - startTime;
#endif

    return newNode;
}

void restoreColoursInRedBlackTree(redBlackTree *tree, redBlackTreeNode *node)
{
    while (1)
    {
        if (node->parent == NULL)
        {
            // printf("1\n");
            node->colour = Black;
            return;
        }
        else if (node->parent->colour == Black)
        {
            // printf("2\n");
            //Tree is still valid.
            return;
        }
        else if (getUncle(node) != NULL && getUncle(node)->colour == Red)
        {
            // printf("3\n");
            node->parent->colour = Black;
            getUncle(node)->colour = Black;
            node->parent->parent->colour = Red;

            // Here is loop, we are moving 2 nodes closer to root. We must restore Colours,
            // beacuse for example node->parent->parent can be a root and we just set Colour
            // on Red.
            node = node->parent->parent;
        }
        else
        {
            // printf("4\n");

            if (node == node->parent->right && node->parent == node->parent->parent->left)
            {
                rotateLeft(tree, node->parent);
                node = node->left;
            }
            else if (node == node->parent->left && node->parent == node->parent->parent->right)
            {
                // printf("Before right rotation\n");
                // printRedBlackTree(tree);

                rotateRight(tree, node->parent);
                node = node->right;
                // printf("After right rotation\n");
                // printRedBlackTree(tree);
            }

            // printf("4a\n");

            redBlackTreeNode *p = node->parent;
            redBlackTreeNode *g = node->parent->parent;

            if (node == p->left)
            {
                // printf("Before right rotation 2\n");
                // printRedBlackTree(tree);
                rotateRight(tree, g);
                // printf("After right rotation 2\n");
                // printRedBlackTree(tree);
            }
            else
            {
                // printf("Before left rotation 2\n");
                // printRedBlackTree(tree);
                rotateLeft(tree, g);
                // printf("After left rotation 2\n");
                // printRedBlackTree(tree);
            }

            // printf("4b\n");
            p->colour = Black;
            g->colour = Red;
            // printf("4c\n");
            return;
        }
    }
}

void replaceRedBlackTreeNode(redBlackTree *tree, redBlackTreeNode *node, redBlackTreeNode *child)
{
    child->parent = node->parent;
    if (node->parent == NULL)
        return;
    if (node == node->parent->left)
        node->parent->left = child;
    else
        node->parent->right = child;
}

void removeCase6(redBlackTree *tree, redBlackTreeNode *node)
{
    redBlackTreeNode *sibling = getSibling(node);

    sibling->colour = node->parent->colour;
    node->parent->colour = Black;

    if (node == node->parent->left)
    {
        sibling->right->colour = Black;
        rotateLeft(tree, node->parent);
    }
    else
    {
        sibling->left->colour = Black;
        rotateRight(tree, node->parent);
    }
}

void removeCase5(redBlackTree *tree, redBlackTreeNode *node)
{
    redBlackTreeNode *sibling = getSibling(node);

    if (sibling->colour == Black)
    {
        if ((node == node->parent->left) && (sibling->right->colour == Black) && (sibling->left->colour == Red))
        {
            sibling->colour = Red;
            sibling->left->colour = Black;
            rotateRight(tree, sibling);
        }
        else if ((node == node->parent->right) && (sibling->left->colour == Black) && (sibling->right->colour == Red))
        {
            sibling->colour = Red;
            sibling->right->colour = Black;
            rotateLeft(tree, sibling);
        }
    }

    removeCase6(tree, node);
}

void removeCase4(redBlackTree *tree, redBlackTreeNode *node)
{
    redBlackTreeNode *sibling = getSibling(node);

    if (node->parent->colour == Red && sibling->colour == Black && sibling->left->colour == Black && sibling->right->colour == Black)
    {
        sibling->colour = Red;
        node->parent->colour = Black;
    }
    else
        removeCase5(tree, node);
}

void removeCase3(redBlackTree *tree, redBlackTreeNode *node)
{
    redBlackTreeNode *sibling = getSibling(node);

    if (node->parent->colour == Black && sibling->colour == Black && sibling->left->colour == Black && sibling->right->colour == Black)
    {
        sibling->colour = Red;

        //Here is loop. Try to analyze this and look how much time it can take.
        removeCase1(tree, node->parent);
    }
    else
        removeCase4(tree, node);
}

void removeCase2(redBlackTree *tree, redBlackTreeNode *node)
{
    redBlackTreeNode *sibling = getSibling(node);

    if (sibling->colour == Red)
    {
        node->parent->colour = Red;
        sibling->colour = Black;
        if (node == node->parent->left)
            rotateLeft(tree, node->parent);
        else
            rotateRight(tree, node->parent);
    }

    removeCase3(tree, node);
}

void removeCase1(redBlackTree *tree, redBlackTreeNode *node)
{
    if (node->parent != NULL)
    {
        removeCase2(tree, node);
    }
}

// For this function node should contain only one non-leaf child. Or at most one.
void removeWhenOneChildFromRedBlackTreeNode(redBlackTree *tree, redBlackTreeNode *node)
{
    redBlackTreeNode *child = node->left != NULL ? node->left : node->right;
    if (child == NULL)
        return;

    replaceRedBlackTreeNode(tree, node, child);
    if (node->colour == Black)
        if (child->colour == Red)
            child->colour = Black;
        else
            removeCase1(tree, child);

    //free(node);
}

redBlackTreeNode *minimumInRedBlackSubTree(redBlackTreeNode *node)
{
    redBlackTreeNode *current = node;

    if (current == NULL)
        return NULL;

    while (current->left != NULL)
        current = current->left;

    return current;
}

void removeFromRedBlackTree(redBlackTree *tree, redBlackTreeNode *node)
{
#if MEASURE_TIME == 1
    struct timeval start;
    gettimeofday(&start, NULL);
    long long startTime = start.tv_sec * 1000000LL + start.tv_usec;
#endif

    if (node == NULL)
    {
#if MEASURE_TIME == 1
        struct timeval end;
        gettimeofday(&end, NULL);
        long long endTime = end.tv_sec * 1000000LL + end.tv_usec;
        redBlackTreeRemoveTime += endTime - startTime;
#endif
        return;
    }

    if (node->left == NULL && node->right == NULL)
    {
        if (node->parent != NULL)
            if (node->parent->left == node)
                node->parent->left = NULL;
            else
                node->parent->right = NULL;
        else
            tree->first = NULL;
    }
    else if (node->left != NULL && node->right != NULL)
    {
        redBlackTreeNode *newNode = minimumInRedBlackSubTree(node->right);
        newNode->parent->left = NULL;
        newNode->parent = node->parent;
        if (node->parent != NULL)
            if (node->parent->left == node)
                node->parent->left = newNode;
            else
                node->parent->right = newNode;
        else
            tree->first = newNode;

        newNode->left = node->left;
        newNode->right = node->right;
        newNode->colour = node->colour;

        node->left = NULL;
        node->right = NULL;
        node->parent = NULL;
    }
    else
    {
        removeWhenOneChildFromRedBlackTreeNode(tree, node);
    }

    free(node);

#if MEASURE_TIME == 1
    struct timeval end;
    gettimeofday(&end, NULL);
    long long endTime = end.tv_sec * 1000000LL + end.tv_usec;
    redBlackTreeRemoveTime += endTime - startTime;
#endif
}

redBlackTreeNode *getNextNodeFromRedBlackTree(redBlackTree *tree, redBlackTreeNode *node)
{
#if MEASURE_TIME == 1
    struct timeval start;
    gettimeofday(&start, NULL);
    long long startTime = start.tv_sec * 1000000LL + start.tv_usec;
#endif

    if (minimumInRedBlackSubTree(node->right) != NULL)
    {
#if MEASURE_TIME == 1
        struct timeval end;
        gettimeofday(&end, NULL);
        long long endTime = end.tv_sec * 1000000LL + end.tv_usec;
        redBlackTreeNextNodeTime += endTime - startTime;
#endif

        return minimumInRedBlackSubTree(node->right);
    }

    if (node->parent == NULL)
    {
#if MEASURE_TIME == 1
        struct timeval end;
        gettimeofday(&end, NULL);
        long long endTime = end.tv_sec * 1000000LL + end.tv_usec;
        redBlackTreeNextNodeTime += endTime - startTime;
#endif

        return NULL;
    }

    redBlackTreeNode *current = node;
    while (current != NULL)
    {
        if (tree->compare(current->data, node->data) > 0)
        {
#if MEASURE_TIME == 1
            struct timeval end;
            gettimeofday(&end, NULL);
            long long endTime = end.tv_sec * 1000000LL + end.tv_usec;
            redBlackTreeNextNodeTime += endTime - startTime;
#endif

            return current;
        }
        if (current->right != NULL)
            if (tree->compare(current->right->data, node->data) > 0)
            {
#if MEASURE_TIME == 1
                struct timeval end;
                gettimeofday(&end, NULL);
                long long endTime = end.tv_sec * 1000000LL + end.tv_usec;
                redBlackTreeNextNodeTime += endTime - startTime;
#endif

                return minimumInRedBlackSubTree(current->right);
            }
        current = current->parent;
    }
#if MEASURE_TIME == 1
        struct timeval end;
        gettimeofday(&end, NULL);
        long long endTime = end.tv_sec * 1000000LL + end.tv_usec;
        redBlackTreeNextNodeTime += endTime - startTime;
#endif

    return NULL;
}
