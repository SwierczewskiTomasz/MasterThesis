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

redBlackTree *newRedBlackTree(double (*compare)(void *, void *), void (*freeData)(void *))
{
    redBlackTree *tree = (redBlackTree *)malloc(sizeof(redBlackTree));
    tree->compare = compare;
    tree->freeData = freeData;
    tree->first = NULL;
    tree->count = 0;
    return tree;
}

void removeRedBlackTree(redBlackTree *tree, bool removeData)
{
    redBlackTreeNode *node = tree->first;

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
                redBlackTreeNode *toRemoveNode = node;
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

    // if (node->parent->right != NULL)
    //     node->parent->right->parent = node;

    if (node->left != NULL)
        node->left->parent = node;

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

    if (node->right != NULL)
        node->right->parent = node;

    node->parent->left = node;
}

redBlackTreeNode *getFromRedBlackTree(redBlackTree *tree, void *data)
{
#if MEASURE_TIME == 1
    struct timeval start;
    gettimeofday(&start, NULL);
    long long startTime = start.tv_sec * 1000000LL + start.tv_usec;
#endif

    if (data == NULL)
    {

#if MEASURE_TIME == 1
        struct timeval end;
        gettimeofday(&end, NULL);
        long long endTime = end.tv_sec * 1000000LL + end.tv_usec;
        redBlackTreeGetTime += endTime - startTime;
#endif

        return NULL;
    }

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
            return current;
        //printf("Error in %s line %i: getFromRedBlackTree - situation with exact the same data, but different point in tree shouldn't happen. For this implementation. \n", (char *)__FILE__, __LINE__);
    }

#if MEASURE_TIME == 1
    struct timeval end;
    gettimeofday(&end, NULL);
    long long endTime = end.tv_sec * 1000000LL + end.tv_usec;
    redBlackTreeGetTime += endTime - startTime;
#endif

    return NULL;
}

redBlackTreeNode *getFromRedBlackTreeFirstSmaller(redBlackTree *tree, void *data)
{
#if MEASURE_TIME == 1
    struct timeval start;
    gettimeofday(&start, NULL);
    long long startTime = start.tv_sec * 1000000LL + start.tv_usec;
#endif

    if (data == NULL)
    {

#if MEASURE_TIME == 1
        struct timeval end;
        gettimeofday(&end, NULL);
        long long endTime = end.tv_sec * 1000000LL + end.tv_usec;
        redBlackTreeGetTime += endTime - startTime;
#endif

        return NULL;
    }

    redBlackTreeNode *current = tree->first;
    redBlackTreeNode *prevCurrent = NULL;

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
        prevCurrent = current;
        if (result > 0)
            current = current->left;
        else if (result < 0)
            current = current->right;
        else
            return current;
        //printf("Error in %s line %i: getFromRedBlackTree - situation with exact the same data, but different point in tree shouldn't happen. For this implementation. \n", (char *)__FILE__, __LINE__);
    }

#if MEASURE_TIME == 1
    struct timeval end;
    gettimeofday(&end, NULL);
    long long endTime = end.tv_sec * 1000000LL + end.tv_usec;
    redBlackTreeGetTime += endTime - startTime;
#endif
    
    return prevCurrent;
}

redBlackTreeNode *getFromRedBlackTreeFirstBigger(redBlackTree *tree, void *data)
{
#if MEASURE_TIME == 1
    struct timeval start;
    gettimeofday(&start, NULL);
    long long startTime = start.tv_sec * 1000000LL + start.tv_usec;
#endif

    if (data == NULL)
    {

#if MEASURE_TIME == 1
        struct timeval end;
        gettimeofday(&end, NULL);
        long long endTime = end.tv_sec * 1000000LL + end.tv_usec;
        redBlackTreeGetTime += endTime - startTime;
#endif

        return NULL;
    }

    redBlackTreeNode *current = tree->first;
    redBlackTreeNode *prevCurrent = NULL;

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
        // prevCurrent = current;
        if (result > 0)
        {    
            // if(current->left != NULL)
            // {
            //     prevCurrent = current;
            // }
            prevCurrent = current;
            current = current->left;
        }
        else if (result < 0)
        {    
            current = current->right;
        }
        else
        {    
            return current;
        }
        //printf("Error in %s line %i: getFromRedBlackTree - situation with exact the same data, but different point in tree shouldn't happen. For this implementation. \n", (char *)__FILE__, __LINE__);
    }

#if MEASURE_TIME == 1
    struct timeval end;
    gettimeofday(&end, NULL);
    long long endTime = end.tv_sec * 1000000LL + end.tv_usec;
    redBlackTreeGetTime += endTime - startTime;
#endif
    
    return prevCurrent;
}

redBlackTreeNode *insertIntoRedBlackTree(redBlackTree *tree, void *data)
{
#if MEASURE_TIME == 1
    struct timeval start;
    gettimeofday(&start, NULL);
    long long startTime = start.tv_sec * 1000000LL + start.tv_usec;
#endif

    tree->count++;

    redBlackTreeNode *current = tree->first;

    while (current != NULL)
    {
        if (current->data == data)
        {
            fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: insertIntoRedBlackTree function. \n", (char *)__FILE__, __LINE__);
            fprintf(stderr, "Trying to insert data %14p, which one exists in tree %14p. \n\n", data, tree);

            tree->count--;

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
            // If we found with the same data, try to insert at left.

            //             if (current->left == NULL)
            //             {
            //                 // printf("Insert at left\n");
            //                 redBlackTreeNode *newNode = (redBlackTreeNode *)malloc(sizeof(redBlackTreeNode));
            //                 current->left = newNode;
            //                 newNode->left = NULL;
            //                 newNode->right = NULL;
            //                 newNode->parent = current;
            //                 newNode->data = data;
            //                 newNode->colour = Red;
            //                 restoreColoursInRedBlackTree(tree, newNode);
            //                 // printf("Inserted\n");
            //                 // printRedBlackTree(tree);

            // #if MEASURE_TIME == 1
            //                 struct timeval end;
            //                 gettimeofday(&end, NULL);
            //                 long long endTime = end.tv_sec * 1000000LL + end.tv_usec;
            //                 redBlackTreeInsertTime += endTime - startTime;
            // #endif

            //                 return newNode;
            //             }
            //             else
            //             {
            //                 current = current->left;
            //             }

            // To co jest poniżej, jest dla implementacji, gdy nie dopuszczamy takich smaych danych do wstawienia.
            // Nie zawsze może to działać tak jak chcemy, np. gdy chcemy wstawić trójkąt, a chcemy wstawić kolejny trójkąt,
            // który ma mieć ten sam środek i ten sam promień, ale opierać się na innych punktach.

            printf("Error in %s line %i: insertIntoRedBlackTree - situation with exact the same data is in tree shouldn't happen. For this implementation. \n", (char *)__FILE__, __LINE__);

#if MEASURE_TIME == 1
            struct timeval end;
            gettimeofday(&end, NULL);
            long long endTime = end.tv_sec * 1000000LL + end.tv_usec;
            redBlackTreeInsertTime += endTime - startTime;
#endif

            return NULL;
        }
    }
#if DEBUG_REDBLACKTREE == 1
    printf("File %s, line %i: insertIntoRedBlackTree function.\n", (char *)__FILE__, __LINE__);
    printf("Tree: %p, data: %p \n", tree, data);
#endif
    redBlackTreeNode *newNode = (redBlackTreeNode *)malloc(sizeof(redBlackTreeNode));
#if DEBUG_REDBLACKTREE == 1
    printf("New allocated pointer for newNode: %p\n\n", newNode);
#endif
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

redBlackTreeNode *minimumInRedBlackSubTree(redBlackTreeNode *node)
{
    redBlackTreeNode *current = node;

    if (current == NULL)
        return NULL;

    while (current->left != NULL)
        current = current->left;

    return current;
}

redBlackTreeNode *maximumInRedBlackSubTree(redBlackTreeNode *node)
{
    redBlackTreeNode *current = node;

    if (current == NULL)
        return NULL;

    while (current->right != NULL)
        current = current->right;

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

    if (node->left != NULL && node->right != NULL)
    {
        // printf("removeFromRedBlackTree function: \n");
        // printf("   Node: %14p, Simplex: %14p, Parent: %14p, Left: %14p, Right: %14p, Colour: %s \n", node, node->data, node->parent, node->left, node->right, node->colour == Red ? "Red  " : "Black");
        redBlackTreeNode *newNode = minimumInRedBlackSubTree(node->right);
        redBlackTreeNode *copy = (redBlackTreeNode *)malloc(sizeof(redBlackTreeNode));

        copy->colour = newNode->colour;
        copy->left = newNode->left;
        copy->parent = newNode->parent;
        copy->right = newNode->right;

        newNode->colour = node->colour;
        newNode->left = node->left;
        newNode->parent = node->parent;
        if(node->right != newNode)
        {
            newNode->right = node->right;
        }
        else
        {
            newNode->right = node;
        }
        // printf("   Node: %14p, Simplex: %14p, Parent: %14p, Left: %14p, Right: %14p, Colour: %s \n", node, node->data, node->parent, node->left, node->right, node->colour == Red ? "Red  " : "Black");
        // printf("NewNode: %14p, Simplex: %14p, Parent: %14p, Left: %14p, Right: %14p, Colour: %s \n", newNode, newNode->data, newNode->parent, newNode->left, newNode->right, newNode->colour == Red ? "Red  " : "Black");

        if (node->right != NULL)
        {
            if(node->right != newNode)
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
            fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: removeFromRedBlackTree function. Child don't have parent. \n", (char *)__FILE__, __LINE__);
        }
        node->colour = copy->colour;
        node->left = copy->left;
        node->parent = copy->parent;
        node->right = copy->right;

        // printf("   Node: %14p, Simplex: %14p, Parent: %14p, Left: %14p, Right: %14p, Colour: %s \n", node, node->data, node->parent, node->left, node->right, node->colour == Red ? "Red  " : "Black");
        // printf("NewNode: %14p, Simplex: %14p, Parent: %14p, Left: %14p, Right: %14p, Colour: %s \n", newNode, newNode->data, newNode->parent, newNode->left, newNode->right, newNode->colour == Red ? "Red  " : "Black");
        // printf("   Copy: %14p, Simplex: %14p, Parent: %14p, Left: %14p, Right: %14p, Colour: %s \n\n", copy, copy->data, copy->parent, copy->left, copy->right, copy->colour == Red ? "Red  " : "Black");
        free(copy);
    }

    removeWhenOneChildFromRedBlackTreeNode(tree, node);

    // printf("Free node: %p\n\n", node);
    free(node);
    tree->count--;

#if MEASURE_TIME == 1
    struct timeval end;
    gettimeofday(&end, NULL);
    long long endTime = end.tv_sec * 1000000LL + end.tv_usec;
    redBlackTreeRemoveTime += endTime - startTime;
#endif
}

// For this function node should contain only one non-leaf child. Or at most one.
void removeWhenOneChildFromRedBlackTreeNode(redBlackTree *tree, redBlackTreeNode *node)
{
    redBlackTreeNode *child = node->left != NULL ? node->left : node->right;
    // if (child == NULL)
    //     return;

    // replaceRedBlackTreeNode(tree, node, child);
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
                fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: removeWhenOneChildFromRedBlackTreeNode function. Child and node shouldn't be black. \n", (char *)__FILE__, __LINE__);
                removeCase1(tree, child);
            }
        }
        else
        {
            removeCase1(tree, node);
        }
    }
    replaceRedBlackTreeNode(tree, node, child);
    //free(node);
}

void replaceRedBlackTreeNode(redBlackTree *tree, redBlackTreeNode *node, redBlackTreeNode *child)
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

void removeCase1(redBlackTree *tree, redBlackTreeNode *node)
{
    if (node->parent != NULL)
    {
        removeCase2(tree, node);
    }
}

void removeCase2(redBlackTree *tree, redBlackTreeNode *node)
{
    redBlackTreeNode *sibling = getSibling(node);

    if (sibling == NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: removeCase2 function. Sibling should exists. \n", (char *)__FILE__, __LINE__);
    }

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

void removeCase3(redBlackTree *tree, redBlackTreeNode *node)
{
    redBlackTreeNode *sibling = getSibling(node);

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
                removeCase1(tree, node->parent);
            }
            else if (sibling->right->colour == Black)
            {
                sibling->colour = Red;

                //Here is loop. Try to analyze this and look how much time it can take.
                removeCase1(tree, node->parent);
            }
            else
            {
                removeCase4(tree, node);
            }
        }
        else if (sibling->left->colour == Black)
        {
            if (sibling->right == NULL)
            {
                sibling->colour = Red;

                //Here is loop. Try to analyze this and look how much time it can take.
                removeCase1(tree, node->parent);
            }
            else if (sibling->right->colour == Black)
            {
                sibling->colour = Red;

                //Here is loop. Try to analyze this and look how much time it can take.
                removeCase1(tree, node->parent);
            }
            else
            {
                removeCase4(tree, node);
            }
        }
        else
        {
            removeCase4(tree, node);
        }
    }
    else
    {
        removeCase4(tree, node);
    }
}

void removeCase4(redBlackTree *tree, redBlackTreeNode *node)
{
    redBlackTreeNode *sibling = getSibling(node);

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
                removeCase5(tree, node);
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
                removeCase5(tree, node);
            }
        }
        else
        {
            removeCase5(tree, node);
        }
    }
    else
    {
        removeCase5(tree, node);
    }
}

void removeCase5(redBlackTree *tree, redBlackTreeNode *node)
{
    redBlackTreeNode *sibling = getSibling(node);

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
                            rotateRight(tree, sibling);
                        }
                    }
                    else
                    {

                        sibling->colour = Red;
                        sibling->left->colour = Black;
                        rotateRight(tree, sibling);
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
                            rotateLeft(tree, sibling);
                        }
                    }
                    else
                    {
                        sibling->colour = Red;
                        sibling->right->colour = Black;
                        rotateLeft(tree, sibling);
                    }
                }
            }
        }
    }

    removeCase6(tree, node);
}

void removeCase6(redBlackTree *tree, redBlackTreeNode *node)
{
    redBlackTreeNode *sibling = getSibling(node);

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
        rotateLeft(tree, node->parent);
    }
    else
    {
        if (sibling->left != NULL)
        {
            sibling->left->colour = Black;
        }
        rotateRight(tree, node->parent);
    }
}

redBlackTreeNode *getNextNodeFromRedBlackTree(redBlackTree *tree, redBlackTreeNode *node)
{
#if MEASURE_TIME == 1
    struct timeval start;
    gettimeofday(&start, NULL);
    long long startTime = start.tv_sec * 1000000LL + start.tv_usec;
#endif

    //     if (minimumInRedBlackSubTree(node->right) != NULL)
    //     {
    // #if MEASURE_TIME == 1
    //         struct timeval end;
    //         gettimeofday(&end, NULL);
    //         long long endTime = end.tv_sec * 1000000LL + end.tv_usec;
    //         redBlackTreeNextNodeTime += endTime - startTime;
    // #endif

    //         return minimumInRedBlackSubTree(node->right);
    //     }

#if DEBUG == 1
    if (node->right == node || node->left == node || node->parent == node)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: Something very weird - We have here loop! \n", (char *)__FILE__, __LINE__);
        fprintf(stderr, "Node: %14p, Data: %14p, Parent: %14p, Left: %14p, Right: %14p, Colour: %s \n", node, node->data, node->parent, node->left, node->right, node->colour == Red ? "Red  " : "Black");
        sleep(10);
        return NULL;
    }
#endif

    if (node->right != NULL)
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
        if (tree->compare(current->data, node->data) >= 0 && current != node)
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

redBlackTreeNode *getPrevNodeFromRedBlackTree(redBlackTree *tree, redBlackTreeNode *node)
{
#if MEASURE_TIME == 1
    struct timeval start;
    gettimeofday(&start, NULL);
    long long startTime = start.tv_sec * 1000000LL + start.tv_usec;
#endif

#if DEBUG == 1
    if (node->right == node || node->left == node || node->parent == node)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: Something very weird - We have here loop! \n", (char *)__FILE__, __LINE__);
        fprintf(stderr, "Node: %14p, Data: %14p, Parent: %14p, Left: %14p, Right: %14p, Colour: %s \n", node, node->data, node->parent, node->left, node->right, node->colour == Red ? "Red  " : "Black");
        sleep(10);
        return NULL;
    }
#endif

    if (node->left != NULL)
    {
#if MEASURE_TIME == 1
        struct timeval end;
        gettimeofday(&end, NULL);
        long long endTime = end.tv_sec * 1000000LL + end.tv_usec;
        redBlackTreePrevNodeTime += endTime - startTime;
#endif

        return maximumInRedBlackSubTree(node->left);
    }

    if (node->parent == NULL)
    {
#if MEASURE_TIME == 1
        struct timeval end;
        gettimeofday(&end, NULL);
        long long endTime = end.tv_sec * 1000000LL + end.tv_usec;
        redBlackTreePrevNodeTime += endTime - startTime;
#endif

        return NULL;
    }

    redBlackTreeNode *current = node;
    while (current != NULL)
    {
        if (tree->compare(current->data, node->data) <= 0 && current != node)
        {
#if MEASURE_TIME == 1
            struct timeval end;
            gettimeofday(&end, NULL);
            long long endTime = end.tv_sec * 1000000LL + end.tv_usec;
            redBlackTreePrevNodeTime += endTime - startTime;
#endif

            return current;
        }

        if (current->left != NULL)
            if (tree->compare(current->left->data, node->data) < 0)
            {
#if MEASURE_TIME == 1
                struct timeval end;
                gettimeofday(&end, NULL);
                long long endTime = end.tv_sec * 1000000LL + end.tv_usec;
                redBlackTreePrevNodeTime += endTime - startTime;
#endif

                return maximumInRedBlackSubTree(current->left);
            }
        current = current->parent;
    }
#if MEASURE_TIME == 1
    struct timeval end;
    gettimeofday(&end, NULL);
    long long endTime = end.tv_sec * 1000000LL + end.tv_usec;
    redBlackTreePrevNodeTime += endTime - startTime;
#endif

    return NULL;
}
