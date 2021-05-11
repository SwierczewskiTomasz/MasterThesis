#include <stdio.h>
#include <stdlib.h>
#include "testRedBlackTree.h"

double compareTwoPointsForRedBlackTreeTests(void *p1, void *p2)
{
    PointForRedBlackTreeTests *point1 = (PointForRedBlackTreeTests *)p1;
    PointForRedBlackTreeTests *point2 = (PointForRedBlackTreeTests *)p2;
    return (double)(point1->x - point2->x);
}

PointForRedBlackTreeTests *newPointForRedBlackTreeTests(int x)
{
    PointForRedBlackTreeTests *point = (PointForRedBlackTreeTests *)malloc(sizeof(PointForRedBlackTreeTests));
    point->x = x;
    return point;
}

char *printPointForRedBlackTreeTests(void *point)
{
    char *result = (char *)malloc(15 * sizeof(char));
    PointForRedBlackTreeTests *p = (PointForRedBlackTreeTests *)point;
    sprintf(result, "Point: %3d", p->x);
    return result;
}

void testRedBlackTree(int *testCounter)
{
    testRedBlackTreeCreating(testCounter);
    testRedBlackTreeInserting(testCounter);
    testRedBlackTreeRemoving(testCounter);
}

void testRedBlackTreeRemoving(int *testCounter)
{
    testRedBlackTreeRemovingCase1(testCounter);
    testRedBlackTreeRemovingCase2(testCounter);
    testRedBlackTreeRemovingCase3(testCounter);
    testRedBlackTreeRemovingCase4(testCounter);
    testRedBlackTreeRemovingCase5(testCounter);
    testRedBlackTreeRemovingCase6(testCounter);
    testRedBlackTreeRemovingCase7(testCounter);
    testRedBlackTreeRemovingCase8(testCounter);
    testRedBlackTreeRemovingCase9(testCounter);
    testRedBlackTreeRemovingCase10(testCounter);
}

void testRedBlackTreeCreating(int *testCounter)
{
    printTestName("testRedBlackTreeCreating", (*testCounter)++);

    redBlackTree *tree = newRedBlackTree(compareTwoPointsForRedBlackTreeTests, free);

    if (tree == NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeCreating function. Tree is NULL. \n", (char *)__FILE__, __LINE__);
    }
    if (tree->first != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeCreating function. First node of tree isn't NULL. \n", (char *)__FILE__, __LINE__);
    }
    if (tree->count != 0)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeCreating function. Counter in tree isn't 0. \n", (char *)__FILE__, __LINE__);
    }
    if (tree->compare != compareTwoPointsForRedBlackTreeTests)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeCreating function. Compare function in tree is incorrect. \n", (char *)__FILE__, __LINE__);
    }
    if (tree->freeData != free)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeCreating function. Function to free data in tree is incorrect. \n", (char *)__FILE__, __LINE__);
    }
}

void testRedBlackTreeInserting(int *testCounter)
{
    printTestName("testRedBlackTreeInserting", (*testCounter)++);

    redBlackTree *tree = newRedBlackTree(compareTwoPointsForRedBlackTreeTests, free);

    if (tree == NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Tree is NULL. \n", (char *)__FILE__, __LINE__);
    }

    PointForRedBlackTreeTests *point0 = newPointForRedBlackTreeTests(0);
    PointForRedBlackTreeTests *point1 = newPointForRedBlackTreeTests(1);
    PointForRedBlackTreeTests *point2 = newPointForRedBlackTreeTests(2);

    // Inserting first node.

    redBlackTreeNode *node0 = insertIntoRedBlackTree(tree, point0);

    if (tree->count != 1)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Counter in tree isn't 1. \n", (char *)__FILE__, __LINE__);
    }

    if (node0 != tree->first)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. First node in tree is \
        different than returned node: node: %14p, tree->first: %14p \n",
                (char *)__FILE__, __LINE__, node0, tree->first);
    }

    if (node0->colour != Black)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. First node in tree isn't black. \n", (char *)__FILE__, __LINE__);
    }

    if (node0->data != point0)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Pointer to data in first node in tree isn't on inserting point. \
        node->data: %14p, point0: %14p \n",
                (char *)__FILE__, __LINE__, node0->data, point0);
    }

    if (point0->x != 0)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. This function change data inside point and isn't 0. Now x is %d \n",
                (char *)__FILE__, __LINE__, point0->x);
    }

    if (node0->parent != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Parent of node isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node0->parent);
    }

    if (node0->left != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Left child of node isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node0->left);
    }

    if (node0->right != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Right child of node isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node0->right);
    }

    // Inserting second node

    redBlackTreeNode *node1 = insertIntoRedBlackTree(tree, point1);

    if (tree->count != 2)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Counter in tree isn't 2. \n", (char *)__FILE__, __LINE__);
    }

    if (node0 != tree->first)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. First node in tree isn't node0: node0: %14p, tree->first: %14p \n",
                (char *)__FILE__, __LINE__, node0, tree->first);
    }

    if (node0->colour != Black)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Node0 in tree isn't black. \n", (char *)__FILE__, __LINE__);
    }

    if (node0->data != point0)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Pointer to data in node0 in tree isn't on point0. \
        node0->data: %14p, point0: %14p \n",
                (char *)__FILE__, __LINE__, node0->data, point0);
    }

    if (point0->x != 0)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. This function change data inside point0 and isn't 0. Now x is %d \n",
                (char *)__FILE__, __LINE__, point0->x);
    }

    if (node0->parent != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Parent of node0 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node0->parent);
    }

    if (node0->left != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Left child of node0 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node0->left);
    }

    if (node0->right != node1)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Right child of node0 isn't node1. There is %14p. \n", (char *)__FILE__, __LINE__, node0->right);
    }

    if (node1->colour != Red)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Inserted node1 in tree isn't red. \n", (char *)__FILE__, __LINE__);
    }

    if (node1->data != point1)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Pointer to data in node1 in tree isn't on inserting point. \
        node->data: %14p, point1: %14p \n",
                (char *)__FILE__, __LINE__, node1->data, point1);
    }

    if (point1->x != 1)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. This function change data inside point1 and isn't 0. Now x is %d \n",
                (char *)__FILE__, __LINE__, point1->x);
    }

    if (node1->parent != node0)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Parent of node1 isn't node0. There is %14p. \n", (char *)__FILE__, __LINE__, node1->parent);
    }

    if (node1->left != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Left child of node1 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node1->left);
    }

    if (node1->right != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Right child of node1 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node1->right);
    }

    // Inserting third node

    redBlackTreeNode *node2 = insertIntoRedBlackTree(tree, point2);

    if (tree->count != 3)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Counter in tree isn't 3. \n", (char *)__FILE__, __LINE__);
    }

    if (node1 != tree->first)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. First node in tree isn't the node1: node1: %14p, tree->first: %14p \n",
                (char *)__FILE__, __LINE__, node1, tree->first);
    }

    if (node0->colour != Red)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Node0 in tree isn't red. \n", (char *)__FILE__, __LINE__);
    }

    if (node0->data != point0)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Pointer to data in node0 in tree isn't on point0. \
        node0->data: %14p, point0: %14p \n",
                (char *)__FILE__, __LINE__, node0->data, point0);
    }

    if (point0->x != 0)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. This function change data inside point0 and isn't 0. Now x is %d \n",
                (char *)__FILE__, __LINE__, point0->x);
    }

    if (node0->parent != node1)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Parent of node isn't node1. There is %14p. \n", (char *)__FILE__, __LINE__, node0->parent);
    }

    if (node0->left != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Left child of node isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node0->left);
    }

    if (node0->right != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Right child of node isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node0->right);
    }

    if (node1->colour != Black)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Node1 in tree isn't black. \n", (char *)__FILE__, __LINE__);
    }

    if (node1->data != point1)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Pointer to data in node1 in tree isn't on point1. \
        node->data: %14p, point1: %14p \n",
                (char *)__FILE__, __LINE__, node1->data, point1);
    }

    if (point1->x != 1)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. This function change data inside point1 and isn't 1. Now x is %d \n",
                (char *)__FILE__, __LINE__, point1->x);
    }

    if (node1->parent != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Parent of node1 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node1->parent);
    }

    if (node1->left != node0)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Left child of node isn't node0. There is %14p. \n", (char *)__FILE__, __LINE__, node1->left);
    }

    if (node1->right != node2)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Right child of node isn't node2. There is %14p. \n", (char *)__FILE__, __LINE__, node1->right);
    }

    if (node2->colour != Red)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Node2 in tree isn't red. \n", (char *)__FILE__, __LINE__);
    }

    if (node2->data != point2)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Pointer to data in node2 in tree isn't on point2. \
        node->data: %14p, point1: %14p \n",
                (char *)__FILE__, __LINE__, node1->data, point1);
    }

    if (point2->x != 2)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. This function change data inside point2 and isn't 2. Now x is %d \n",
                (char *)__FILE__, __LINE__, point1->x);
    }

    if (node2->parent != node1)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Parent of node1 isn't node1. There is %14p. \n", (char *)__FILE__, __LINE__, node1->parent);
    }

    if (node2->left != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Left child of node isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node1->left);
    }

    if (node2->right != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Right child of node isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node1->right);
    }

    // In this case was tested left rotation. Now we would like to try insert 3 points, but with right rotation. I will insert in this order: 2, 1, 0.

    removeRedBlackTree(tree, false);
    node0 = node1 = node2 = NULL;

    tree = newRedBlackTree(compareTwoPointsForRedBlackTreeTests, free);

    // Inserting first node.

    node2 = insertIntoRedBlackTree(tree, point2);

    if (tree->count != 1)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Counter in tree isn't 1. \n", (char *)__FILE__, __LINE__);
    }

    if (node2 != tree->first)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. First node in tree is \
        different than returned node: node: %14p, tree->first: %14p \n",
                (char *)__FILE__, __LINE__, node2, tree->first);
    }

    if (node2->colour != Black)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. First node in tree isn't black. \n", (char *)__FILE__, __LINE__);
    }

    if (node2->data != point2)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Pointer to data in first node in tree isn't on inserting point. \
        node->data: %14p, point2: %14p \n",
                (char *)__FILE__, __LINE__, node0->data, point0);
    }

    if (point2->x != 2)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. This function change data inside point and isn't 2. Now x is %d \n",
                (char *)__FILE__, __LINE__, point0->x);
    }

    if (node2->parent != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Parent of node isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node0->parent);
    }

    if (node2->left != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Left child of node isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node0->left);
    }

    if (node2->right != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Right child of node isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node0->right);
    }

    // Inserting second node

    node1 = insertIntoRedBlackTree(tree, point1);

    if (tree->count != 2)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Counter in tree isn't 2. \n", (char *)__FILE__, __LINE__);
    }

    if (node2 != tree->first)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. First node in tree isn't node2: node2: %14p, tree->first: %14p \n",
                (char *)__FILE__, __LINE__, node2, tree->first);
    }

    if (node2->colour != Black)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Node0 in tree isn't black. \n", (char *)__FILE__, __LINE__);
    }

    if (node2->data != point2)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Pointer to data in node2 in tree isn't on point2. \
        node2->data: %14p, point2: %14p \n",
                (char *)__FILE__, __LINE__, node2->data, point2);
    }

    if (point2->x != 2)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. This function change data inside point2 and isn't 2. Now x is %d \n",
                (char *)__FILE__, __LINE__, point0->x);
    }

    if (node2->parent != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Parent of node2 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node0->parent);
    }

    if (node2->left != node1)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Left child of node2 isn't node1. There is %14p. \n", (char *)__FILE__, __LINE__, node0->left);
    }

    if (node2->right != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Right child of node0 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node0->right);
    }

    if (node1->colour != Red)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Inserted node1 in tree isn't red. \n", (char *)__FILE__, __LINE__);
    }

    if (node1->data != point1)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Pointer to data in node1 in tree isn't on inserting point. \
        node->data: %14p, point1: %14p \n",
                (char *)__FILE__, __LINE__, node1->data, point1);
    }

    if (point1->x != 1)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. This function change data inside point1 and isn't 0. Now x is %d \n",
                (char *)__FILE__, __LINE__, point1->x);
    }

    if (node1->parent != node2)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Parent of node1 isn't node0. There is %14p. \n", (char *)__FILE__, __LINE__, node1->parent);
    }

    if (node1->left != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Left child of node1 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node1->left);
    }

    if (node1->right != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Right child of node1 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node1->right);
    }

    // Inserting third node

    node0 = insertIntoRedBlackTree(tree, point0);

    if (tree->count != 3)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Counter in tree isn't 3. \n", (char *)__FILE__, __LINE__);
    }

    if (node1 != tree->first)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. First node in tree isn't the node1: node1: %14p, tree->first: %14p \n",
                (char *)__FILE__, __LINE__, node1, tree->first);
    }

    if (node0->colour != Red)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Node0 in tree isn't red. \n", (char *)__FILE__, __LINE__);
    }

    if (node0->data != point0)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Pointer to data in node0 in tree isn't on point0. \
        node0->data: %14p, point0: %14p \n",
                (char *)__FILE__, __LINE__, node0->data, point0);
    }

    if (point0->x != 0)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. This function change data inside point0 and isn't 0. Now x is %d \n",
                (char *)__FILE__, __LINE__, point0->x);
    }

    if (node0->parent != node1)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Parent of node isn't node1. There is %14p. \n", (char *)__FILE__, __LINE__, node0->parent);
    }

    if (node0->left != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Left child of node isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node0->left);
    }

    if (node0->right != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Right child of node isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node0->right);
    }

    if (node1->colour != Black)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Node1 in tree isn't black. \n", (char *)__FILE__, __LINE__);
    }

    if (node1->data != point1)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Pointer to data in node1 in tree isn't on point1. \
        node->data: %14p, point1: %14p \n",
                (char *)__FILE__, __LINE__, node1->data, point1);
    }

    if (point1->x != 1)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. This function change data inside point1 and isn't 1. Now x is %d \n",
                (char *)__FILE__, __LINE__, point1->x);
    }

    if (node1->parent != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Parent of node1 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node1->parent);
    }

    if (node1->left != node0)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Left child of node isn't node0. There is %14p. \n", (char *)__FILE__, __LINE__, node1->left);
    }

    if (node1->right != node2)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Right child of node isn't node2. There is %14p. \n", (char *)__FILE__, __LINE__, node1->right);
    }

    if (node2->colour != Red)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Node2 in tree isn't red. \n", (char *)__FILE__, __LINE__);
    }

    if (node2->data != point2)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Pointer to data in node2 in tree isn't on point2. \
        node->data: %14p, point1: %14p \n",
                (char *)__FILE__, __LINE__, node1->data, point1);
    }

    if (point2->x != 2)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. This function change data inside point2 and isn't 2. Now x is %d \n",
                (char *)__FILE__, __LINE__, point1->x);
    }

    if (node2->parent != node1)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Parent of node1 isn't node1. There is %14p. \n", (char *)__FILE__, __LINE__, node1->parent);
    }

    if (node2->left != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Left child of node isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node1->left);
    }

    if (node2->right != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Right child of node isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node1->right);
    }

    // Now we will try to insert again the same point - point0.

    printf("Now we will try to insert again the same point - point0. Please ignore next error from redBlackTree.c file. \n");

    redBlackTreeNode *node = insertIntoRedBlackTree(tree, point0);

    if (node != node0)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. We try to insert existing data to tree, but node isn't node0 and returned pointer: %14p, node0: %14p. \n",
                (char *)__FILE__, __LINE__, node, node0);
    }

    if (tree->count != 3)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Counter in tree isn't 3. \n", (char *)__FILE__, __LINE__);
    }

    if (node1 != tree->first)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. First node in tree isn't the node1: node1: %14p, tree->first: %14p \n",
                (char *)__FILE__, __LINE__, node1, tree->first);
    }

    if (node0->colour != Red)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Node0 in tree isn't red. \n", (char *)__FILE__, __LINE__);
    }

    if (node0->data != point0)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Pointer to data in node0 in tree isn't on point0. \
        node0->data: %14p, point0: %14p \n",
                (char *)__FILE__, __LINE__, node0->data, point0);
    }

    if (point0->x != 0)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. This function change data inside point0 and isn't 0. Now x is %d \n",
                (char *)__FILE__, __LINE__, point0->x);
    }

    if (node0->parent != node1)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Parent of node isn't node1. There is %14p. \n", (char *)__FILE__, __LINE__, node0->parent);
    }

    if (node0->left != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Left child of node isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node0->left);
    }

    if (node0->right != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Right child of node isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node0->right);
    }

    if (node1->colour != Black)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Node1 in tree isn't black. \n", (char *)__FILE__, __LINE__);
    }

    if (node1->data != point1)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Pointer to data in node1 in tree isn't on point1. \
        node->data: %14p, point1: %14p \n",
                (char *)__FILE__, __LINE__, node1->data, point1);
    }

    if (point1->x != 1)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. This function change data inside point1 and isn't 1. Now x is %d \n",
                (char *)__FILE__, __LINE__, point1->x);
    }

    if (node1->parent != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Parent of node1 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node1->parent);
    }

    if (node1->left != node0)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Left child of node isn't node0. There is %14p. \n", (char *)__FILE__, __LINE__, node1->left);
    }

    if (node1->right != node2)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Right child of node isn't node2. There is %14p. \n", (char *)__FILE__, __LINE__, node1->right);
    }

    if (node2->colour != Red)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Node2 in tree isn't red. \n", (char *)__FILE__, __LINE__);
    }

    if (node2->data != point2)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Pointer to data in node2 in tree isn't on point2. \
        node->data: %14p, point1: %14p \n",
                (char *)__FILE__, __LINE__, node1->data, point1);
    }

    if (point2->x != 2)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. This function change data inside point2 and isn't 2. Now x is %d \n",
                (char *)__FILE__, __LINE__, point1->x);
    }

    if (node2->parent != node1)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Parent of node1 isn't node1. There is %14p. \n", (char *)__FILE__, __LINE__, node1->parent);
    }

    if (node2->left != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Left child of node isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node1->left);
    }

    if (node2->right != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeInserting function. Right child of node isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node1->right);
    }

    removeRedBlackTree(tree, true);
}

// Case 1 - we are removing red node, which one doesn't have children.
void testRedBlackTreeRemovingCase1(int *testCounter)
{
    printTestName("testRedBlackTreeRemovingCase1", (*testCounter)++);

    redBlackTree *tree;

    PointForRedBlackTreeTests *point0 = newPointForRedBlackTreeTests(0);
    PointForRedBlackTreeTests *point1 = newPointForRedBlackTreeTests(1);
    PointForRedBlackTreeTests *point2 = newPointForRedBlackTreeTests(2);
    PointForRedBlackTreeTests *point3 = newPointForRedBlackTreeTests(3);
    PointForRedBlackTreeTests *point4 = newPointForRedBlackTreeTests(4);
    PointForRedBlackTreeTests *point5 = newPointForRedBlackTreeTests(5);
    PointForRedBlackTreeTests *point6 = newPointForRedBlackTreeTests(6);
    PointForRedBlackTreeTests *point7 = newPointForRedBlackTreeTests(7);

    tree = newRedBlackTree(compareTwoPointsForRedBlackTreeTests, free);

    if (tree == NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase1 function. Tree is NULL. \n", (char *)__FILE__, __LINE__);
    }

    redBlackTreeNode *node3 = insertIntoRedBlackTree(tree, point3);
    redBlackTreeNode *node5 = insertIntoRedBlackTree(tree, point5);
    redBlackTreeNode *node1 = insertIntoRedBlackTree(tree, point1);

    if (tree->count != 3)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase1 function. Counter in tree isn't 3. \n", (char *)__FILE__, __LINE__);
    }

    if (node3 != tree->first)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase1 function. Node3 isn't the root of tree. There is %14p. Node3: %14p \n", (char *)__FILE__, __LINE__, tree->first, node3);
    }

    if (node3->left != node1)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase1 function. Left child of node3 isn't node1. There is %14p. \n", (char *)__FILE__, __LINE__, node3->left);
    }

    if (node1->left != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase1 function. Left child of node1 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node1->left);
    }

    if (node1->right != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase1 function. Right child of node1 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node1->right);
    }

    if (node3->right != node5)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase1 function. Right child of node3 isn't node5. There is %14p. \n", (char *)__FILE__, __LINE__, node3->right);
    }

    if (node5->left != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase1 function. Left child of node5 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node5->left);
    }

    if (node5->right != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase1 function. Right child of node5 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node5->right);
    }

    if (node1->parent != node3)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase1 function. Parent of node1 isn't node3. There is %14p. \n", (char *)__FILE__, __LINE__, node1->parent);
    }

    if (node3->parent != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase1 function. Parent of node3 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node3->parent);
    }

    if (node5->parent != node3)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase1 function. Parent of node5 isn't node3. There is %14p. \n", (char *)__FILE__, __LINE__, node5->parent);
    }

    if (node1->colour != Red)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase1 function. Node1 isn't red. \n", (char *)__FILE__, __LINE__);
    }

    if (node3->colour != Black)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase1 function. Node3 isn't black. \n", (char *)__FILE__, __LINE__);
    }

    if (node5->colour != Red)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase1 function. Node5 isn't red. \n", (char *)__FILE__, __LINE__);
    }

    // Now time to remove node1.

    removeFromRedBlackTree(tree, node1);

    if (tree->count != 2)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase1 function. Counter in tree isn't 2. \n", (char *)__FILE__, __LINE__);
    }

    if (node3 != tree->first)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase1 function. Node3 isn't the root of tree. There is %14p. Node3: %14p \n", (char *)__FILE__, __LINE__, tree->first, node3);
    }

    if (node3->left != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase1 function. Left child of node3 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node3->left);
    }

    if (node3->right != node5)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase1 function. Right child of node3 isn't node5. There is %14p. \n", (char *)__FILE__, __LINE__, node3->right);
    }

    if (node5->left != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase1 function. Left child of node5 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node5->left);
    }

    if (node5->right != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase1 function. Right child of node5 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node5->right);
    }

    if (node3->parent != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase1 function. Parent of node3 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node3->parent);
    }

    if (node5->parent != node3)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase1 function. Parent of node5 isn't node3. There is %14p. \n", (char *)__FILE__, __LINE__, node5->parent);
    }

    if (node3->colour != Black)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase1 function. Node3 isn't black. \n", (char *)__FILE__, __LINE__);
    }

    if (node5->colour != Red)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase1 function. Node5 isn't red. \n", (char *)__FILE__, __LINE__);
    }

    removeRedBlackTree(tree, false);
    free(point0);
    free(point1);
    free(point2);
    free(point3);
    free(point4);
    free(point5);
    free(point6);
    free(point7);
}

// Case 2 - we are removing black node, which one have one red child.
void testRedBlackTreeRemovingCase2(int *testCounter)
{
    printTestName("testRedBlackTreeRemovingCase2", (*testCounter)++);

    redBlackTree *tree;

    PointForRedBlackTreeTests *point0 = newPointForRedBlackTreeTests(0);
    PointForRedBlackTreeTests *point1 = newPointForRedBlackTreeTests(1);
    PointForRedBlackTreeTests *point2 = newPointForRedBlackTreeTests(2);
    PointForRedBlackTreeTests *point3 = newPointForRedBlackTreeTests(3);
    PointForRedBlackTreeTests *point4 = newPointForRedBlackTreeTests(4);
    PointForRedBlackTreeTests *point5 = newPointForRedBlackTreeTests(5);
    PointForRedBlackTreeTests *point6 = newPointForRedBlackTreeTests(6);
    PointForRedBlackTreeTests *point7 = newPointForRedBlackTreeTests(7);

    tree = newRedBlackTree(compareTwoPointsForRedBlackTreeTests, free);

    if (tree == NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase2 function. Tree is NULL. \n", (char *)__FILE__, __LINE__);
    }

    redBlackTreeNode *node3 = insertIntoRedBlackTree(tree, point3);
    redBlackTreeNode *node5 = insertIntoRedBlackTree(tree, point5);
    redBlackTreeNode *node1 = insertIntoRedBlackTree(tree, point1);
    redBlackTreeNode *node2 = insertIntoRedBlackTree(tree, point2);

    if (tree->count != 4)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase2 function. Counter in tree isn't 4. \n", (char *)__FILE__, __LINE__);
    }

    if (node3 != tree->first)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase2 function. Node3 isn't the root of tree. There is %14p. Node3: %14p \n", (char *)__FILE__, __LINE__, tree->first, node3);
    }

    if (node3->left != node1)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase2 function. Left child of node3 isn't node1. There is %14p. \n", (char *)__FILE__, __LINE__, node3->left);
    }

    if (node1->left != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase2 function. Left child of node1 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node1->left);
    }

    if (node1->right != node2)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase2 function. Right child of node1 isn't node2. There is %14p. \n", (char *)__FILE__, __LINE__, node1->right);
    }

    if (node2->left != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase2 function. Left child of node2 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node2->left);
    }

    if (node2->right != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase2 function. Right child of node2 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node2->right);
    }

    if (node3->right != node5)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase2 function. Right child of node3 isn't node5. There is %14p. \n", (char *)__FILE__, __LINE__, node3->right);
    }

    if (node5->left != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase2 function. Left child of node5 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node5->left);
    }

    if (node5->right != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase2 function. Right child of node5 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node5->right);
    }

    if (node1->parent != node3)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase2 function. Parent of node1 isn't node3. There is %14p. \n", (char *)__FILE__, __LINE__, node1->parent);
    }

    if (node2->parent != node1)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase2 function. Parent of node2 isn't node1. There is %14p. \n", (char *)__FILE__, __LINE__, node2->parent);
    }

    if (node3->parent != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase2 function. Parent of node3 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node3->parent);
    }

    if (node5->parent != node3)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase2 function. Parent of node5 isn't node3. There is %14p. \n", (char *)__FILE__, __LINE__, node5->parent);
    }

    if (node1->colour != Black)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase2 function. Node1 isn't black. \n", (char *)__FILE__, __LINE__);
    }

    if (node2->colour != Red)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase2 function. Node2 isn't red. \n", (char *)__FILE__, __LINE__);
    }

    if (node3->colour != Black)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase2 function. Node3 isn't black. \n", (char *)__FILE__, __LINE__);
    }

    if (node5->colour != Black)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase2 function. Node5 isn't black. \n", (char *)__FILE__, __LINE__);
    }

    // Now time to remove node1.

    removeFromRedBlackTree(tree, node1);

    if (tree->count != 3)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase2 function. Counter in tree isn't 3. \n", (char *)__FILE__, __LINE__);
    }

    if (node3 != tree->first)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase2 function. Node3 isn't the root of tree. There is %14p. Node3: %14p \n", (char *)__FILE__, __LINE__, tree->first, node3);
    }

    if (node3->left != node2)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase2 function. Left child of node3 isn't node2. There is %14p. \n", (char *)__FILE__, __LINE__, node3->left);
    }

    if (node3->right != node5)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase2 function. Right child of node3 isn't node5. There is %14p. \n", (char *)__FILE__, __LINE__, node3->right);
    }

    if (node2->left != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase2 function. Left child of node2 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node2->left);
    }

    if (node2->right != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase2 function. Right child of node2 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node2->right);
    }

    if (node5->left != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase2 function. Left child of node5 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node5->left);
    }

    if (node5->right != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase2 function. Right child of node5 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node5->right);
    }

    if (node2->parent != node3)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase2 function. Parent of node2 isn't node3. There is %14p. \n", (char *)__FILE__, __LINE__, node2->parent);
    }

    if (node3->parent != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase2 function. Parent of node3 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node3->parent);
    }

    if (node5->parent != node3)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase2 function. Parent of node5 isn't node3. There is %14p. \n", (char *)__FILE__, __LINE__, node5->parent);
    }

    if (node2->colour != Black)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase2 function. Node2 isn't black. \n", (char *)__FILE__, __LINE__);
    }

    if (node3->colour != Black)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase2 function. Node3 isn't black. \n", (char *)__FILE__, __LINE__);
    }

    if (node5->colour != Black)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase2 function. Node5 isn't black. \n", (char *)__FILE__, __LINE__);
    }

    removeRedBlackTree(tree, false);
    free(point0);
    free(point1);
    free(point2);
    free(point3);
    free(point4);
    free(point5);
    free(point6);
    free(point7);
}

// Case 3 - we are removing black node, which one doesn't have children. His parent is black, he had sibling, which one also is black.
void testRedBlackTreeRemovingCase3(int *testCounter)
{
    printTestName("testRedBlackTreeRemovingCase3", (*testCounter)++);

    redBlackTree *tree;

    PointForRedBlackTreeTests *point0 = newPointForRedBlackTreeTests(0);
    PointForRedBlackTreeTests *point1 = newPointForRedBlackTreeTests(1);
    PointForRedBlackTreeTests *point2 = newPointForRedBlackTreeTests(2);
    PointForRedBlackTreeTests *point3 = newPointForRedBlackTreeTests(3);
    PointForRedBlackTreeTests *point4 = newPointForRedBlackTreeTests(4);
    PointForRedBlackTreeTests *point5 = newPointForRedBlackTreeTests(5);
    PointForRedBlackTreeTests *point6 = newPointForRedBlackTreeTests(6);
    PointForRedBlackTreeTests *point7 = newPointForRedBlackTreeTests(7);

    tree = newRedBlackTree(compareTwoPointsForRedBlackTreeTests, free);

    if (tree == NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase3 function. Tree is NULL. \n", (char *)__FILE__, __LINE__);
    }

    redBlackTreeNode *node3 = insertIntoRedBlackTree(tree, point3);
    redBlackTreeNode *node5 = insertIntoRedBlackTree(tree, point5);
    redBlackTreeNode *node1 = insertIntoRedBlackTree(tree, point1);
    redBlackTreeNode *node2 = insertIntoRedBlackTree(tree, point2);
    removeFromRedBlackTree(tree, node2);

    if (tree->count != 3)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase3 function. Counter in tree isn't 3. \n", (char *)__FILE__, __LINE__);
    }

    if (node3 != tree->first)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase3 function. Node3 isn't the root of tree. There is %14p. Node3: %14p \n", (char *)__FILE__, __LINE__, tree->first, node3);
    }

    if (node3->left != node1)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase3 function. Left child of node3 isn't node1. There is %14p. \n", (char *)__FILE__, __LINE__, node3->left);
    }

    if (node1->left != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase3 function. Left child of node1 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node1->left);
    }

    if (node1->right != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase3 function. Right child of node1 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node1->right);
    }

    if (node3->right != node5)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase3 function. Right child of node3 isn't node5. There is %14p. \n", (char *)__FILE__, __LINE__, node3->right);
    }

    if (node5->left != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase3 function. Left child of node5 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node5->left);
    }

    if (node5->right != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase3 function. Right child of node5 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node5->right);
    }

    if (node1->parent != node3)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase3 function. Parent of node1 isn't node3. There is %14p. \n", (char *)__FILE__, __LINE__, node1->parent);
    }

    if (node3->parent != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase3 function. Parent of node3 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node3->parent);
    }

    if (node5->parent != node3)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase3 function. Parent of node5 isn't node3. There is %14p. \n", (char *)__FILE__, __LINE__, node5->parent);
    }

    if (node1->colour != Black)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase3 function. Node1 isn't black. \n", (char *)__FILE__, __LINE__);
    }

    if (node3->colour != Black)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase3 function. Node3 isn't black. \n", (char *)__FILE__, __LINE__);
    }

    if (node5->colour != Black)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase3 function. Node5 isn't black. \n", (char *)__FILE__, __LINE__);
    }

    // Now time to remove node1.

    removeFromRedBlackTree(tree, node1);

    if (tree->count != 2)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase3 function. Counter in tree isn't 2. \n", (char *)__FILE__, __LINE__);
    }

    if (node3 != tree->first)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase3 function. Node3 isn't the root of tree. There is %14p. Node3: %14p \n", (char *)__FILE__, __LINE__, tree->first, node3);
    }

    if (node3->left != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase3 function. Left child of node3 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node3->left);
    }

    if (node3->right != node5)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase3 function. Right child of node3 isn't node5. There is %14p. \n", (char *)__FILE__, __LINE__, node3->right);
    }

    if (node5->left != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase3 function. Left child of node5 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node5->left);
    }

    if (node5->right != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase3 function. Right child of node5 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node5->right);
    }

    if (node3->parent != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase3 function. Parent of node3 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node3->parent);
    }

    if (node5->parent != node3)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase3 function. Parent of node5 isn't node3. There is %14p. \n", (char *)__FILE__, __LINE__, node5->parent);
    }

    if (node3->colour != Black)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase3 function. Node3 isn't black. \n", (char *)__FILE__, __LINE__);
    }

    if (node5->colour != Red)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase1 function. Node5 isn't red. \n", (char *)__FILE__, __LINE__);
    }

    removeRedBlackTree(tree, false);
    free(point0);
    free(point1);
    free(point2);
    free(point3);
    free(point4);
    free(point5);
    free(point6);
    free(point7);
}

// Case 4 - we are removing black node, which one doesn't have children. His parent is red, he had sibling, which one also is black.
void testRedBlackTreeRemovingCase4(int *testCounter)
{
    printTestName("testRedBlackTreeRemovingCase4", (*testCounter)++);

    redBlackTree *tree;

    PointForRedBlackTreeTests *point_1 = newPointForRedBlackTreeTests(-1);
    PointForRedBlackTreeTests *point0 = newPointForRedBlackTreeTests(0);
    PointForRedBlackTreeTests *point1 = newPointForRedBlackTreeTests(1);
    PointForRedBlackTreeTests *point2 = newPointForRedBlackTreeTests(2);
    PointForRedBlackTreeTests *point3 = newPointForRedBlackTreeTests(3);
    PointForRedBlackTreeTests *point4 = newPointForRedBlackTreeTests(4);
    PointForRedBlackTreeTests *point5 = newPointForRedBlackTreeTests(5);
    PointForRedBlackTreeTests *point6 = newPointForRedBlackTreeTests(6);
    PointForRedBlackTreeTests *point7 = newPointForRedBlackTreeTests(7);

    tree = newRedBlackTree(compareTwoPointsForRedBlackTreeTests, free);

    if (tree == NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase4 function. Tree is NULL. \n", (char *)__FILE__, __LINE__);
    }

    redBlackTreeNode *node3 = insertIntoRedBlackTree(tree, point3);
    redBlackTreeNode *node5 = insertIntoRedBlackTree(tree, point5);
    redBlackTreeNode *node1 = insertIntoRedBlackTree(tree, point1);
    redBlackTreeNode *node2 = insertIntoRedBlackTree(tree, point2);
    redBlackTreeNode *node0 = insertIntoRedBlackTree(tree, point0);
    redBlackTreeNode *node4 = insertIntoRedBlackTree(tree, point4);
    redBlackTreeNode *node6 = insertIntoRedBlackTree(tree, point6);
    redBlackTreeNode *node_1 = insertIntoRedBlackTree(tree, point_1);
    removeFromRedBlackTree(tree, node_1);

    if (tree->count != 7)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase4 function. Counter in tree isn't 7. \n", (char *)__FILE__, __LINE__);
    }

    if (node3 != tree->first)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase4 function. Node3 isn't the root of tree. There is %14p. Node3: %14p \n", (char *)__FILE__, __LINE__, tree->first, node3);
    }

    if (node3->left != node1)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase4 function. Left child of node3 isn't node1. There is %14p. \n", (char *)__FILE__, __LINE__, node3->left);
    }

    if (node3->right != node5)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase4 function. Right child of node3 isn't node5. There is %14p. \n", (char *)__FILE__, __LINE__, node3->right);
    }

    if (node1->left != node0)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase4 function. Left child of node1 isn't node0. There is %14p. \n", (char *)__FILE__, __LINE__, node1->left);
    }

    if (node1->right != node2)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase4 function. Right child of node1 isn't node2. There is %14p. \n", (char *)__FILE__, __LINE__, node1->right);
    }

    if (node0->left != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase4 function. Left child of node0 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node0->left);
    }

    if (node0->right != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase4 function. Right child of node0 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node0->right);
    }

    if (node2->left != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase4 function. Left child of node2 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node2->left);
    }

    if (node2->right != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase4 function. Right child of node2 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node2->right);
    }

    if (node5->left != node4)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase4 function. Left child of node5 isn't node4. There is %14p. \n", (char *)__FILE__, __LINE__, node5->left);
    }

    if (node5->right != node6)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase4 function. Right child of node5 isn't node6. There is %14p. \n", (char *)__FILE__, __LINE__, node5->right);
    }

    if (node4->left != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase4 function. Left child of node4 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node4->left);
    }

    if (node4->right != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase4 function. Right child of node4 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node4->right);
    }

    if (node6->left != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase4 function. Left child of node6 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node6->left);
    }

    if (node6->right != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase4 function. Right child of node6 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node6->right);
    }

    if (node0->parent != node1)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase4 function. Parent of node0 isn't node1. There is %14p. \n", (char *)__FILE__, __LINE__, node0->parent);
    }

    if (node1->parent != node3)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase4 function. Parent of node1 isn't node3. There is %14p. \n", (char *)__FILE__, __LINE__, node1->parent);
    }

    if (node2->parent != node1)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase4 function. Parent of node2 isn't node1. There is %14p. \n", (char *)__FILE__, __LINE__, node2->parent);
    }

    if (node3->parent != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase4 function. Parent of node3 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node3->parent);
    }

    if (node4->parent != node5)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase4 function. Parent of node4 isn't node5. There is %14p. \n", (char *)__FILE__, __LINE__, node4->parent);
    }

    if (node5->parent != node3)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase4 function. Parent of node5 isn't node3. There is %14p. \n", (char *)__FILE__, __LINE__, node5->parent);
    }

    if (node6->parent != node5)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase4 function. Parent of node6 isn't node5. There is %14p. \n", (char *)__FILE__, __LINE__, node6->parent);
    }

    if (node0->colour != Black)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase4 function. Node0 isn't black. \n", (char *)__FILE__, __LINE__);
    }

    if (node1->colour != Red)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase4 function. Node1 isn't red. \n", (char *)__FILE__, __LINE__);
    }

    if (node2->colour != Black)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase4 function. Node2 isn't black. \n", (char *)__FILE__, __LINE__);
    }

    if (node3->colour != Black)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase4 function. Node3 isn't black. \n", (char *)__FILE__, __LINE__);
    }

    if (node4->colour != Red)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase4 function. Node4 isn't red. \n", (char *)__FILE__, __LINE__);
    }

    if (node5->colour != Black)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase4 function. Node5 isn't black. \n", (char *)__FILE__, __LINE__);
    }

    if (node6->colour != Red)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase4 function. Node6 isn't red. \n", (char *)__FILE__, __LINE__);
    }

    // Now time to remove node0.

    removeFromRedBlackTree(tree, node0);

    if (tree->count != 6)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase4 function. Counter in tree isn't 6. \n", (char *)__FILE__, __LINE__);
    }

    if (node3 != tree->first)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase4 function. Node3 isn't the root of tree. There is %14p. Node3: %14p \n", (char *)__FILE__, __LINE__, tree->first, node3);
    }

    if (node3->left != node1)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase4 function. Left child of node3 isn't node1. There is %14p. \n", (char *)__FILE__, __LINE__, node3->left);
    }

    if (node3->right != node5)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase4 function. Right child of node3 isn't node5. There is %14p. \n", (char *)__FILE__, __LINE__, node3->right);
    }

    if (node1->left != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase4 function. Left child of node1 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node1->left);
    }

    if (node1->right != node2)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase4 function. Right child of node1 isn't node2. There is %14p. \n", (char *)__FILE__, __LINE__, node1->right);
    }

    if (node2->left != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase4 function. Left child of node2 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node2->left);
    }

    if (node2->right != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase4 function. Right child of node2 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node2->right);
    }

    if (node5->left != node4)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase4 function. Left child of node5 isn't node4. There is %14p. \n", (char *)__FILE__, __LINE__, node5->left);
    }

    if (node5->right != node6)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase4 function. Right child of node5 isn't node6. There is %14p. \n", (char *)__FILE__, __LINE__, node5->right);
    }

    if (node4->left != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase4 function. Left child of node4 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node4->left);
    }

    if (node4->right != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase4 function. Right child of node4 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node4->right);
    }

    if (node6->left != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase4 function. Left child of node6 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node6->left);
    }

    if (node6->right != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase4 function. Right child of node6 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node6->right);
    }

    if (node1->parent != node3)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase4 function. Parent of node1 isn't node3. There is %14p. \n", (char *)__FILE__, __LINE__, node1->parent);
    }

    if (node2->parent != node1)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase4 function. Parent of node2 isn't node1. There is %14p. \n", (char *)__FILE__, __LINE__, node2->parent);
    }

    if (node3->parent != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase4 function. Parent of node3 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node3->parent);
    }

    if (node4->parent != node5)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase4 function. Parent of node4 isn't node5. There is %14p. \n", (char *)__FILE__, __LINE__, node4->parent);
    }

    if (node5->parent != node3)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase4 function. Parent of node5 isn't node3. There is %14p. \n", (char *)__FILE__, __LINE__, node5->parent);
    }

    if (node6->parent != node5)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase4 function. Parent of node6 isn't node5. There is %14p. \n", (char *)__FILE__, __LINE__, node6->parent);
    }

    if (node1->colour != Black)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase4 function. Node1 isn't black. \n", (char *)__FILE__, __LINE__);
    }

    if (node2->colour != Red)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase4 function. Node2 isn't red. \n", (char *)__FILE__, __LINE__);
    }

    if (node3->colour != Black)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase4 function. Node3 isn't black. \n", (char *)__FILE__, __LINE__);
    }

    if (node4->colour != Red)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase4 function. Node4 isn't red. \n", (char *)__FILE__, __LINE__);
    }

    if (node5->colour != Black)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase4 function. Node5 isn't black. \n", (char *)__FILE__, __LINE__);
    }

    if (node6->colour != Red)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase4 function. Node6 isn't red. \n", (char *)__FILE__, __LINE__);
    }

    removeRedBlackTree(tree, false);
    free(point_1);
    free(point0);
    free(point1);
    free(point2);
    free(point3);
    free(point4);
    free(point5);
    free(point6);
    free(point7);
}

// Case 5 - we are removing black node, which one doesn't have children. His parent is black, he had sibling, which one also is black. This sibling have only one red (left) child.
void testRedBlackTreeRemovingCase5(int *testCounter)
{
    printTestName("testRedBlackTreeRemovingCase5", (*testCounter)++);

    redBlackTree *tree;

    PointForRedBlackTreeTests *point0 = newPointForRedBlackTreeTests(0);
    PointForRedBlackTreeTests *point1 = newPointForRedBlackTreeTests(1);
    PointForRedBlackTreeTests *point2 = newPointForRedBlackTreeTests(2);
    PointForRedBlackTreeTests *point3 = newPointForRedBlackTreeTests(3);
    PointForRedBlackTreeTests *point4 = newPointForRedBlackTreeTests(4);
    PointForRedBlackTreeTests *point5 = newPointForRedBlackTreeTests(5);
    PointForRedBlackTreeTests *point6 = newPointForRedBlackTreeTests(6);
    PointForRedBlackTreeTests *point7 = newPointForRedBlackTreeTests(7);

    tree = newRedBlackTree(compareTwoPointsForRedBlackTreeTests, free);

    if (tree == NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase5 function. Tree is NULL. \n", (char *)__FILE__, __LINE__);
    }

    redBlackTreeNode *node3 = insertIntoRedBlackTree(tree, point3);
    redBlackTreeNode *node5 = insertIntoRedBlackTree(tree, point5);
    redBlackTreeNode *node1 = insertIntoRedBlackTree(tree, point1);
    redBlackTreeNode *node4 = insertIntoRedBlackTree(tree, point4);

    // printRedBlackTreeString(tree, printPointForRedBlackTreeTests);

    if (tree->count != 4)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase5 function. Counter in tree isn't 4. \n", (char *)__FILE__, __LINE__);
    }

    if (node3 != tree->first)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase5 function. Node3 isn't the root of tree. There is %14p. Node3: %14p \n", (char *)__FILE__, __LINE__, tree->first, node3);
    }

    if (node3->left != node1)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase5 function. Left child of node3 isn't node1. There is %14p. \n", (char *)__FILE__, __LINE__, node3->left);
    }

    if (node3->right != node5)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase5 function. Right child of node3 isn't node5. There is %14p. \n", (char *)__FILE__, __LINE__, node3->right);
    }

    if (node1->left != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase5 function. Left child of node1 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node1->left);
    }

    if (node1->right != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase5 function. Right child of node1 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node1->right);
    }

    if (node5->left != node4)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase5 function. Left child of node5 isn't node4. There is %14p. \n", (char *)__FILE__, __LINE__, node5->left);
    }

    if (node5->right != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase5 function. Right child of node5 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node5->right);
    }

    if (node4->left != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase5 function. Left child of node4 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node4->left);
    }

    if (node4->right != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase5 function. Right child of node4 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node4->right);
    }

    if (node1->parent != node3)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase5 function. Parent of node1 isn't node3. There is %14p. \n", (char *)__FILE__, __LINE__, node1->parent);
    }

    if (node3->parent != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase5 function. Parent of node3 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node3->parent);
    }

    if (node4->parent != node5)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase5 function. Parent of node4 isn't node5. There is %14p. \n", (char *)__FILE__, __LINE__, node4->parent);
    }

    if (node5->parent != node3)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase5 function. Parent of node5 isn't node3. There is %14p. \n", (char *)__FILE__, __LINE__, node5->parent);
    }

    if (node1->colour != Black)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase5 function. Node1 isn't black. \n", (char *)__FILE__, __LINE__);
    }

    if (node3->colour != Black)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase5 function. Node3 isn't black. \n", (char *)__FILE__, __LINE__);
    }

    if (node4->colour != Red)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase5 function. Node4 isn't red. \n", (char *)__FILE__, __LINE__);
    }

    if (node5->colour != Black)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase5 function. Node5 isn't black. \n", (char *)__FILE__, __LINE__);
    }

    // Now time to remove node1.

    removeFromRedBlackTree(tree, node1);
    // printRedBlackTreeString(tree, printPointForRedBlackTreeTests);

    if (tree->count != 3)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase5 function. Counter in tree isn't 6. \n", (char *)__FILE__, __LINE__);
    }

    if (node4 != tree->first)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase5 function. Node4 isn't the root of tree. There is %14p. Node4: %14p \n", (char *)__FILE__, __LINE__, tree->first, node4);
    }

    if (node3->left != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase5 function. Left child of node3 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node3->left);
    }

    if (node3->right != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase5 function. Right child of node3 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node3->right);
    }

    if (node4->left != node3)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase5 function. Left child of node4 isn't node3. There is %14p. \n", (char *)__FILE__, __LINE__, node4->left);
    }

    if (node4->right != node5)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase5 function. Right child of node4 isn't node5. There is %14p. \n", (char *)__FILE__, __LINE__, node4->right);
    }

    if (node5->left != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase5 function. Left child of node5 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node5->left);
    }

    if (node5->right != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase5 function. Right child of node5 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node5->right);
    }

    if (node3->parent != node4)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase5 function. Parent of node3 isn't node4. There is %14p. \n", (char *)__FILE__, __LINE__, node3->parent);
    }

    if (node4->parent != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase5 function. Parent of node4 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node4->parent);
    }

    if (node5->parent != node4)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase5 function. Parent of node5 isn't node4. There is %14p. \n", (char *)__FILE__, __LINE__, node5->parent);
    }

    if (node3->colour != Black)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase5 function. Node3 isn't black. \n", (char *)__FILE__, __LINE__);
    }

    if (node4->colour != Black)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase5 function. Node4 isn't black. \n", (char *)__FILE__, __LINE__);
    }

    if (node5->colour != Black)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase5 function. Node5 isn't black. \n", (char *)__FILE__, __LINE__);
    }

    removeRedBlackTree(tree, false);
    free(point0);
    free(point1);
    free(point2);
    free(point3);
    free(point4);
    free(point5);
    free(point6);
    free(point7);
}

// Case 6 - we are removing black node, which one doesn't have children. His parent is black, he had sibling, which one is red. Sibling have 2 children, both black.
void testRedBlackTreeRemovingCase6(int *testCounter)
{
    printTestName("testRedBlackTreeRemovingCase6", (*testCounter)++);

    redBlackTree *tree;

    PointForRedBlackTreeTests *point0 = newPointForRedBlackTreeTests(0);
    PointForRedBlackTreeTests *point1 = newPointForRedBlackTreeTests(1);
    PointForRedBlackTreeTests *point2 = newPointForRedBlackTreeTests(2);
    PointForRedBlackTreeTests *point3 = newPointForRedBlackTreeTests(3);
    PointForRedBlackTreeTests *point4 = newPointForRedBlackTreeTests(4);
    PointForRedBlackTreeTests *point5 = newPointForRedBlackTreeTests(5);
    PointForRedBlackTreeTests *point6 = newPointForRedBlackTreeTests(6);
    PointForRedBlackTreeTests *point7 = newPointForRedBlackTreeTests(7);

    tree = newRedBlackTree(compareTwoPointsForRedBlackTreeTests, free);

    if (tree == NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase6 function. Tree is NULL. \n", (char *)__FILE__, __LINE__);
    }

    redBlackTreeNode *node3 = insertIntoRedBlackTree(tree, point3);
    redBlackTreeNode *node5 = insertIntoRedBlackTree(tree, point5);
    redBlackTreeNode *node1 = insertIntoRedBlackTree(tree, point1);
    redBlackTreeNode *node4 = insertIntoRedBlackTree(tree, point4);
    redBlackTreeNode *node6 = insertIntoRedBlackTree(tree, point6);
    redBlackTreeNode *node7 = insertIntoRedBlackTree(tree, point7);

    if (tree->count != 6)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase6 function. Counter in tree isn't 6. \n", (char *)__FILE__, __LINE__);
    }

    if (node3 != tree->first)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase6 function. Node3 isn't the root of tree. There is %14p. Node3: %14p \n", (char *)__FILE__, __LINE__, tree->first, node3);
    }

    if (node3->left != node1)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase6 function. Left child of node3 isn't node1. There is %14p. \n", (char *)__FILE__, __LINE__, node3->left);
    }

    if (node3->right != node5)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase6 function. Right child of node3 isn't node5. There is %14p. \n", (char *)__FILE__, __LINE__, node3->right);
    }

    if (node1->left != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase6 function. Left child of node1 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node1->left);
    }

    if (node1->right != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase6 function. Right child of node1 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node1->right);
    }

    if (node5->left != node4)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase6 function. Left child of node5 isn't node4. There is %14p. \n", (char *)__FILE__, __LINE__, node5->left);
    }

    if (node5->right != node6)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase6 function. Right child of node5 isn't node6. There is %14p. \n", (char *)__FILE__, __LINE__, node5->right);
    }

    if (node4->left != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase6 function. Left child of node4 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node4->left);
    }

    if (node4->right != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase6 function. Right child of node4 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node4->right);
    }

    if (node6->left != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase6 function. Left child of node6 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node6->left);
    }

    if (node6->right != node7)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase6 function. Right child of node6 isn't node7. There is %14p. \n", (char *)__FILE__, __LINE__, node6->right);
    }

    if (node7->left != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase6 function. Left child of node7 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node7->left);
    }

    if (node7->right != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase6 function. Right child of node7 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node7->right);
    }

    if (node1->parent != node3)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase6 function. Parent of node1 isn't node3. There is %14p. \n", (char *)__FILE__, __LINE__, node1->parent);
    }

    if (node3->parent != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase6 function. Parent of node3 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node3->parent);
    }

    if (node4->parent != node5)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase6 function. Parent of node4 isn't node5. There is %14p. \n", (char *)__FILE__, __LINE__, node4->parent);
    }

    if (node5->parent != node3)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase6 function. Parent of node5 isn't node3. There is %14p. \n", (char *)__FILE__, __LINE__, node5->parent);
    }

    if (node6->parent != node5)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase6 function. Parent of node6 isn't node5. There is %14p. \n", (char *)__FILE__, __LINE__, node6->parent);
    }

    if (node7->parent != node6)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase6 function. Parent of node7 isn't node6. There is %14p. \n", (char *)__FILE__, __LINE__, node7->parent);
    }

    if (node1->colour != Black)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase6 function. Node1 isn't black. \n", (char *)__FILE__, __LINE__);
    }

    if (node3->colour != Black)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase6 function. Node3 isn't black. \n", (char *)__FILE__, __LINE__);
    }

    if (node4->colour != Black)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase6 function. Node4 isn't black. \n", (char *)__FILE__, __LINE__);
    }

    if (node5->colour != Red)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase6 function. Node5 isn't red. \n", (char *)__FILE__, __LINE__);
    }

    if (node6->colour != Black)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase6 function. Node6 isn't black. \n", (char *)__FILE__, __LINE__);
    }

    if (node7->colour != Red)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase6 function. Node7 isn't red. \n", (char *)__FILE__, __LINE__);
    }

    // Now time to remove node1.

    removeFromRedBlackTree(tree, node1);

    if (tree->count != 5)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase6 function. Counter in tree isn't 5. \n", (char *)__FILE__, __LINE__);
    }

    if (node5 != tree->first)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase6 function. Node5 isn't the root of tree. There is %14p. Node5: %14p \n", (char *)__FILE__, __LINE__, tree->first, node5);
    }

    if (node3->left != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase6 function. Left child of node3 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node3->left);
    }

    if (node3->right != node4)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase6 function. Right child of node3 isn't node4. There is %14p. \n", (char *)__FILE__, __LINE__, node3->right);
    }

    if (node5->left != node3)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase6 function. Left child of node5 isn't node3. There is %14p. \n", (char *)__FILE__, __LINE__, node5->left);
    }

    if (node5->right != node6)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase6 function. Right child of node5 isn't node6. There is %14p. \n", (char *)__FILE__, __LINE__, node5->right);
    }

    if (node4->left != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase6 function. Left child of node4 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node4->left);
    }

    if (node4->right != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase6 function. Right child of node4 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node4->right);
    }

    if (node6->left != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase6 function. Left child of node6 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node6->left);
    }

    if (node6->right != node7)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase6 function. Right child of node6 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node6->right);
    }

    if (node7->left != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase6 function. Left child of node7 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node7->left);
    }

    if (node7->right != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase6 function. Right child of node7 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node7->right);
    }

    if (node3->parent != node5)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase6 function. Parent of node3 isn't node5. There is %14p. \n", (char *)__FILE__, __LINE__, node3->parent);
    }

    if (node4->parent != node3)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase6 function. Parent of node4 isn't node5. There is %14p. \n", (char *)__FILE__, __LINE__, node4->parent);
    }

    if (node5->parent != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase6 function. Parent of node5 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node5->parent);
    }

    if (node6->parent != node5)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase6 function. Parent of node6 isn't node5. There is %14p. \n", (char *)__FILE__, __LINE__, node6->parent);
    }

    if (node7->parent != node6)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase6 function. Parent of node7 isn't node6. There is %14p. \n", (char *)__FILE__, __LINE__, node6->parent);
    }

    if (node3->colour != Black)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase6 function. Node3 isn't black. \n", (char *)__FILE__, __LINE__);
    }

    if (node4->colour != Red)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase6 function. Node4 isn't red. \n", (char *)__FILE__, __LINE__);
    }

    if (node5->colour != Black)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase6 function. Node5 isn't black. \n", (char *)__FILE__, __LINE__);
    }

    if (node6->colour != Black)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase6 function. Node6 isn't black. \n", (char *)__FILE__, __LINE__);
    }

    if (node7->colour != Red)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase6 function. Node7 isn't red. \n", (char *)__FILE__, __LINE__);
    }

    removeRedBlackTree(tree, false);
    free(point0);
    free(point1);
    free(point2);
    free(point3);
    free(point4);
    free(point5);
    free(point6);
    free(point7);
}

// Case 7 - we are removing black node, which one doesn't have children. His parent is black, he had sibling, which one also is black. Sibling have 2 children - both are red.
void testRedBlackTreeRemovingCase7(int *testCounter)
{
    printTestName("testRedBlackTreeRemovingCase7", (*testCounter)++);

    redBlackTree *tree;

    PointForRedBlackTreeTests *point0 = newPointForRedBlackTreeTests(0);
    PointForRedBlackTreeTests *point1 = newPointForRedBlackTreeTests(1);
    PointForRedBlackTreeTests *point2 = newPointForRedBlackTreeTests(2);
    PointForRedBlackTreeTests *point3 = newPointForRedBlackTreeTests(3);
    PointForRedBlackTreeTests *point4 = newPointForRedBlackTreeTests(4);
    PointForRedBlackTreeTests *point5 = newPointForRedBlackTreeTests(5);
    PointForRedBlackTreeTests *point6 = newPointForRedBlackTreeTests(6);
    PointForRedBlackTreeTests *point7 = newPointForRedBlackTreeTests(7);

    tree = newRedBlackTree(compareTwoPointsForRedBlackTreeTests, free);

    if (tree == NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase7 function. Tree is NULL. \n", (char *)__FILE__, __LINE__);
    }

    redBlackTreeNode *node3 = insertIntoRedBlackTree(tree, point3);
    redBlackTreeNode *node5 = insertIntoRedBlackTree(tree, point5);
    redBlackTreeNode *node1 = insertIntoRedBlackTree(tree, point1);
    redBlackTreeNode *node4 = insertIntoRedBlackTree(tree, point4);
    redBlackTreeNode *node6 = insertIntoRedBlackTree(tree, point6);

    if (tree->count != 5)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase7 function. Counter in tree isn't 5. \n", (char *)__FILE__, __LINE__);
    }

    if (node3 != tree->first)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase7 function. Node3 isn't the root of tree. There is %14p. Node3: %14p \n", (char *)__FILE__, __LINE__, tree->first, node3);
    }

    if (node3->left != node1)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase7 function. Left child of node3 isn't node1. There is %14p. \n", (char *)__FILE__, __LINE__, node3->left);
    }

    if (node3->right != node5)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase7 function. Right child of node3 isn't node5. There is %14p. \n", (char *)__FILE__, __LINE__, node3->right);
    }

    if (node1->left != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase7 function. Left child of node1 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node1->left);
    }

    if (node1->right != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase7 function. Right child of node1 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node1->right);
    }

    if (node5->left != node4)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase7 function. Left child of node5 isn't node4. There is %14p. \n", (char *)__FILE__, __LINE__, node5->left);
    }

    if (node5->right != node6)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase7 function. Right child of node5 isn't node6. There is %14p. \n", (char *)__FILE__, __LINE__, node5->right);
    }

    if (node4->left != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase7 function. Left child of node4 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node4->left);
    }

    if (node4->right != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase7 function. Right child of node4 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node4->right);
    }

    if (node6->left != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase7 function. Left child of node6 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node6->left);
    }

    if (node6->right != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase7 function. Right child of node6 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node6->right);
    }

    if (node1->parent != node3)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase7 function. Parent of node1 isn't node3. There is %14p. \n", (char *)__FILE__, __LINE__, node1->parent);
    }

    if (node3->parent != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase7 function. Parent of node3 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node3->parent);
    }

    if (node4->parent != node5)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase7 function. Parent of node4 isn't node5. There is %14p. \n", (char *)__FILE__, __LINE__, node4->parent);
    }

    if (node5->parent != node3)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase7 function. Parent of node5 isn't node3. There is %14p. \n", (char *)__FILE__, __LINE__, node5->parent);
    }

    if (node6->parent != node5)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase7 function. Parent of node6 isn't node5. There is %14p. \n", (char *)__FILE__, __LINE__, node6->parent);
    }

    if (node1->colour != Black)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase7 function. Node1 isn't black. \n", (char *)__FILE__, __LINE__);
    }

    if (node3->colour != Black)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase7 function. Node3 isn't black. \n", (char *)__FILE__, __LINE__);
    }

    if (node4->colour != Red)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase7 function. Node4 isn't red. \n", (char *)__FILE__, __LINE__);
    }

    if (node5->colour != Black)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase7 function. Node5 isn't black. \n", (char *)__FILE__, __LINE__);
    }

    if (node6->colour != Red)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase7 function. Node6 isn't red. \n", (char *)__FILE__, __LINE__);
    }

    // Now time to remove node1.

    removeFromRedBlackTree(tree, node1);

    if (tree->count != 4)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase7 function. Counter in tree isn't 4. \n", (char *)__FILE__, __LINE__);
    }

    if (node5 != tree->first)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase7 function. Node5 isn't the root of tree. There is %14p. Node5: %14p \n", (char *)__FILE__, __LINE__, tree->first, node5);
    }

    if (node3->left != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase7 function. Left child of node3 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node3->left);
    }

    if (node3->right != node4)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase7 function. Right child of node3 isn't node4. There is %14p. \n", (char *)__FILE__, __LINE__, node3->right);
    }

    if (node5->left != node3)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase7 function. Left child of node5 isn't node3. There is %14p. \n", (char *)__FILE__, __LINE__, node5->left);
    }

    if (node5->right != node6)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase7 function. Right child of node5 isn't node6. There is %14p. \n", (char *)__FILE__, __LINE__, node5->right);
    }

    if (node4->left != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase7 function. Left child of node4 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node4->left);
    }

    if (node4->right != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase7 function. Right child of node4 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node4->right);
    }

    if (node6->left != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase7 function. Left child of node6 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node6->left);
    }

    if (node6->right != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase7 function. Right child of node6 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node6->right);
    }

    if (node3->parent != node5)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase7 function. Parent of node3 isn't node5. There is %14p. \n", (char *)__FILE__, __LINE__, node3->parent);
    }

    if (node4->parent != node3)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase7 function. Parent of node4 isn't node3. There is %14p. \n", (char *)__FILE__, __LINE__, node4->parent);
    }

    if (node5->parent != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase7 function. Parent of node5 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node5->parent);
    }

    if (node6->parent != node5)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase7 function. Parent of node6 isn't node5. There is %14p. \n", (char *)__FILE__, __LINE__, node6->parent);
    }

    if (node3->colour != Black)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase7 function. Node3 isn't black. \n", (char *)__FILE__, __LINE__);
    }

    if (node4->colour != Red)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase7 function. Node4 isn't red. \n", (char *)__FILE__, __LINE__);
    }

    if (node5->colour != Black)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase7 function. Node5 isn't black. \n", (char *)__FILE__, __LINE__);
    }

    if (node6->colour != Black)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase7 function. Node6 isn't black. \n", (char *)__FILE__, __LINE__);
    }

    removeRedBlackTree(tree, false);
    free(point0);
    free(point1);
    free(point2);
    free(point3);
    free(point4);
    free(point5);
    free(point6);
    free(point7);
}

// Case 8 - we are removing black node, which one doesn't have children. His parent is red, he had sibling, which one is black. Sibling have 2 children, both are red.
void testRedBlackTreeRemovingCase8(int *testCounter)
{
    printTestName("testRedBlackTreeRemovingCase8", (*testCounter)++);

    redBlackTree *tree;

    PointForRedBlackTreeTests *point0 = newPointForRedBlackTreeTests(0);
    PointForRedBlackTreeTests *point1 = newPointForRedBlackTreeTests(1);
    PointForRedBlackTreeTests *point2 = newPointForRedBlackTreeTests(2);
    PointForRedBlackTreeTests *point3 = newPointForRedBlackTreeTests(3);
    PointForRedBlackTreeTests *point4 = newPointForRedBlackTreeTests(4);
    PointForRedBlackTreeTests *point5 = newPointForRedBlackTreeTests(5);
    PointForRedBlackTreeTests *point6 = newPointForRedBlackTreeTests(6);
    PointForRedBlackTreeTests *point7 = newPointForRedBlackTreeTests(7);
    PointForRedBlackTreeTests *point8 = newPointForRedBlackTreeTests(8);

    tree = newRedBlackTree(compareTwoPointsForRedBlackTreeTests, free);

    if (tree == NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase8 function. Tree is NULL. \n", (char *)__FILE__, __LINE__);
    }

    redBlackTreeNode *node3 = insertIntoRedBlackTree(tree, point3);
    redBlackTreeNode *node5 = insertIntoRedBlackTree(tree, point5);
    redBlackTreeNode *node1 = insertIntoRedBlackTree(tree, point1);
    redBlackTreeNode *node4 = insertIntoRedBlackTree(tree, point4);
    redBlackTreeNode *node6 = insertIntoRedBlackTree(tree, point6);
    redBlackTreeNode *node7 = insertIntoRedBlackTree(tree, point7);
    redBlackTreeNode *node8 = insertIntoRedBlackTree(tree, point8);

    if (tree->count != 7)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase8 function. Counter in tree isn't 7. \n", (char *)__FILE__, __LINE__);
    }

    if (node3 != tree->first)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase8 function. Node3 isn't the root of tree. There is %14p. Node3: %14p \n", (char *)__FILE__, __LINE__, tree->first, node3);
    }

    if (node3->left != node1)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase8 function. Left child of node3 isn't node1. There is %14p. \n", (char *)__FILE__, __LINE__, node3->left);
    }

    if (node3->right != node5)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase8 function. Right child of node3 isn't node5. There is %14p. \n", (char *)__FILE__, __LINE__, node3->right);
    }

    if (node1->left != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase8 function. Left child of node1 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node1->left);
    }

    if (node1->right != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase8 function. Right child of node1 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node1->right);
    }

    if (node5->left != node4)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase8 function. Left child of node5 isn't node4. There is %14p. \n", (char *)__FILE__, __LINE__, node5->left);
    }

    if (node5->right != node7)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase8 function. Right child of node5 isn't node7. There is %14p. \n", (char *)__FILE__, __LINE__, node5->right);
    }

    if (node4->left != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase8 function. Left child of node4 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node4->left);
    }

    if (node4->right != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase8 function. Right child of node4 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node4->right);
    }

    if (node7->left != node6)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase8 function. Left child of node7 isn't node6. There is %14p. \n", (char *)__FILE__, __LINE__, node7->left);
    }

    if (node7->right != node8)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase8 function. Right child of node6 isn't node8. There is %14p. \n", (char *)__FILE__, __LINE__, node7->right);
    }

    if (node6->left != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase8 function. Left child of node6 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node6->left);
    }

    if (node6->right != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase8 function. Right child of node6 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node6->right);
    }

    if (node8->left != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase8 function. Left child of node8 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node8->left);
    }

    if (node8->right != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase8 function. Right child of node8 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node8->right);
    }

    if (node1->parent != node3)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase8 function. Parent of node1 isn't node3. There is %14p. \n", (char *)__FILE__, __LINE__, node1->parent);
    }

    if (node3->parent != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase8 function. Parent of node3 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node3->parent);
    }

    if (node4->parent != node5)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase8 function. Parent of node4 isn't node5. There is %14p. \n", (char *)__FILE__, __LINE__, node4->parent);
    }

    if (node5->parent != node3)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase8 function. Parent of node5 isn't node3. There is %14p. \n", (char *)__FILE__, __LINE__, node5->parent);
    }

    if (node6->parent != node7)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase8 function. Parent of node6 isn't node7. There is %14p. \n", (char *)__FILE__, __LINE__, node6->parent);
    }

    if (node7->parent != node5)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase8 function. Parent of node7 isn't node5. There is %14p. \n", (char *)__FILE__, __LINE__, node7->parent);
    }

    if (node8->parent != node7)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase8 function. Parent of node8 isn't node7. There is %14p. \n", (char *)__FILE__, __LINE__, node8->parent);
    }

    if (node1->colour != Black)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase8 function. Node1 isn't black. \n", (char *)__FILE__, __LINE__);
    }

    if (node3->colour != Black)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase8 function. Node3 isn't black. \n", (char *)__FILE__, __LINE__);
    }

    if (node4->colour != Black)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase8 function. Node4 isn't black. \n", (char *)__FILE__, __LINE__);
    }

    if (node5->colour != Red)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase8 function. Node5 isn't red. \n", (char *)__FILE__, __LINE__);
    }

    if (node6->colour != Red)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase8 function. Node6 isn't red. \n", (char *)__FILE__, __LINE__);
    }

    if (node7->colour != Black)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase8 function. Node7 isn't black. \n", (char *)__FILE__, __LINE__);
    }

    if (node8->colour != Red)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase8 function. Node8 isn't red. \n", (char *)__FILE__, __LINE__);
    }

    // Now time to remove node0.

    removeFromRedBlackTree(tree, node4);

    if (tree->count != 6)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase8 function. Counter in tree isn't 6. \n", (char *)__FILE__, __LINE__);
    }

    if (node3 != tree->first)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase8 function. Node3 isn't the root of tree. There is %14p. Node3: %14p \n", (char *)__FILE__, __LINE__, tree->first, node3);
    }

    if (node3->left != node1)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase8 function. Left child of node3 isn't node1. There is %14p. \n", (char *)__FILE__, __LINE__, node3->left);
    }

    if (node3->right != node7)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase8 function. Right child of node3 isn't node7. There is %14p. \n", (char *)__FILE__, __LINE__, node3->right);
    }

    if (node5->left != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase8 function. Left child of node5 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node5->left);
    }

    if (node5->right != node6)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase8 function. Right child of node5 isn't node6. There is %14p. \n", (char *)__FILE__, __LINE__, node5->right);
    }

    if (node6->left != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase8 function. Left child of node6 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node6->left);
    }

    if (node6->right != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase8 function. Right child of node6 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node6->right);
    }

    if (node7->left != node5)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase8 function. Left child of node7 isn't node5. There is %14p. \n", (char *)__FILE__, __LINE__, node7->left);
    }

    if (node7->right != node8)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase8 function. Right child of node7 isn't node8. There is %14p. \n", (char *)__FILE__, __LINE__, node7->right);
    }

    if (node8->left != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase8 function. Left child of node8 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node8->left);
    }

    if (node8->right != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase8 function. Right child of node8 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node8->right);
    }

    if (node1->parent != node3)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase8 function. Parent of node1 isn't node3. There is %14p. \n", (char *)__FILE__, __LINE__, node1->parent);
    }

    if (node3->parent != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase8 function. Parent of node3 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node3->parent);
    }

    if (node5->parent != node7)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase8 function. Parent of node5 isn't node7. There is %14p. \n", (char *)__FILE__, __LINE__, node5->parent);
    }

    if (node6->parent != node5)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase8 function. Parent of node6 isn't node5. There is %14p. \n", (char *)__FILE__, __LINE__, node6->parent);
    }

    if (node7->parent != node3)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase8 function. Parent of node7 isn't node3. There is %14p. \n", (char *)__FILE__, __LINE__, node7->parent);
    }

    if (node8->parent != node7)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase8 function. Parent of node8 isn't node7. There is %14p. \n", (char *)__FILE__, __LINE__, node8->parent);
    }

    if (node1->colour != Black)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase8 function. Node1 isn't black. \n", (char *)__FILE__, __LINE__);
    }

    if (node3->colour != Black)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase8 function. Node3 isn't black. \n", (char *)__FILE__, __LINE__);
    }

    if (node5->colour != Black)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase8 function. Node5 isn't black. \n", (char *)__FILE__, __LINE__);
    }

    if (node6->colour != Red)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase8 function. Node6 isn't red. \n", (char *)__FILE__, __LINE__);
    }

    if (node7->colour != Red)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase8 function. Node7 isn't red. \n", (char *)__FILE__, __LINE__);
    }

    if (node8->colour != Black)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase8 function. Node8 isn't black. \n", (char *)__FILE__, __LINE__);
    }

    removeRedBlackTree(tree, false);
    free(point0);
    free(point1);
    free(point2);
    free(point3);
    free(point4);
    free(point5);
    free(point6);
    free(point7);
    free(point8);
}

// Case 9 - we are removing black node, which one doesn't have children. He is root.
void testRedBlackTreeRemovingCase9(int *testCounter)
{
    printTestName("testRedBlackTreeRemovingCase9", (*testCounter)++);

    redBlackTree *tree;

    PointForRedBlackTreeTests *point1 = newPointForRedBlackTreeTests(1);

    tree = newRedBlackTree(compareTwoPointsForRedBlackTreeTests, free);

    if (tree == NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase9 function. Tree is NULL. \n", (char *)__FILE__, __LINE__);
    }

    redBlackTreeNode *node1 = insertIntoRedBlackTree(tree, point1);

    if (tree->count != 1)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase9 function. Counter in tree isn't 1. \n", (char *)__FILE__, __LINE__);
    }

    if (node1 != tree->first)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase9 function. Node3 isn't the root of tree. There is %14p. Node1: %14p \n", (char *)__FILE__, __LINE__, tree->first, node1);
    }

    if (node1->left != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase9 function. Left child of node3 isn't node1. There is %14p. \n", (char *)__FILE__, __LINE__, node1->left);
    }

    if (node1->right != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase9 function. Right child of node3 isn't node5. There is %14p. \n", (char *)__FILE__, __LINE__, node1->right);
    }

    removeFromRedBlackTree(tree, node1);

    if (tree->count != 0)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase9 function. Counter in tree isn't 0. \n", (char *)__FILE__, __LINE__);
    }

    if (tree->first != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase9 function. Root isn't NULL. There is %14p. Node1: %14p \n", (char *)__FILE__, __LINE__, tree->first, node1);
    }

    removeRedBlackTree(tree, false);
    free(point1);
}

// Case 8 - we are removing black node, which one doesn't have children. His parent is red, he had sibling, which one is black. Sibling have 2 children, both are red.
void testRedBlackTreeRemovingCase10(int *testCounter)
{
    printTestName("testRedBlackTreeRemovingCase10", (*testCounter)++);

    redBlackTree *tree;

    PointForRedBlackTreeTests *point0 = newPointForRedBlackTreeTests(0);
    PointForRedBlackTreeTests *point1 = newPointForRedBlackTreeTests(1);
    PointForRedBlackTreeTests *point2 = newPointForRedBlackTreeTests(2);
    PointForRedBlackTreeTests *point3 = newPointForRedBlackTreeTests(3);
    PointForRedBlackTreeTests *point4 = newPointForRedBlackTreeTests(4);
    PointForRedBlackTreeTests *point5 = newPointForRedBlackTreeTests(5);
    PointForRedBlackTreeTests *point6 = newPointForRedBlackTreeTests(6);
    PointForRedBlackTreeTests *point7 = newPointForRedBlackTreeTests(7);
    PointForRedBlackTreeTests *point8 = newPointForRedBlackTreeTests(8);

    tree = newRedBlackTree(compareTwoPointsForRedBlackTreeTests, free);

    if (tree == NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase10 function. Tree is NULL. \n", (char *)__FILE__, __LINE__);
    }

    redBlackTreeNode *node3 = insertIntoRedBlackTree(tree, point3);
    redBlackTreeNode *node5 = insertIntoRedBlackTree(tree, point5);
    redBlackTreeNode *node1 = insertIntoRedBlackTree(tree, point1);
    redBlackTreeNode *node4 = insertIntoRedBlackTree(tree, point4);
    redBlackTreeNode *node6 = insertIntoRedBlackTree(tree, point6);
    redBlackTreeNode *node7 = insertIntoRedBlackTree(tree, point7);
    redBlackTreeNode *node8 = insertIntoRedBlackTree(tree, point8);
    // printRedBlackTreeString(tree, printPointForRedBlackTreeTests);

    if (tree->count != 7)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase10 function. Counter in tree isn't 7. \n", (char *)__FILE__, __LINE__);
    }

    if (node3 != tree->first)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase10 function. Node3 isn't the root of tree. There is %14p. Node3: %14p \n", (char *)__FILE__, __LINE__, tree->first, node3);
    }

    if (node3->left != node1)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase10 function. Left child of node3 isn't node1. There is %14p. \n", (char *)__FILE__, __LINE__, node3->left);
    }

    if (node3->right != node5)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase10 function. Right child of node3 isn't node5. There is %14p. \n", (char *)__FILE__, __LINE__, node3->right);
    }

    if (node1->left != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase10 function. Left child of node1 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node1->left);
    }

    if (node1->right != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase10 function. Right child of node1 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node1->right);
    }

    if (node5->left != node4)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase10 function. Left child of node5 isn't node4. There is %14p. \n", (char *)__FILE__, __LINE__, node5->left);
    }

    if (node5->right != node7)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase10 function. Right child of node5 isn't node7. There is %14p. \n", (char *)__FILE__, __LINE__, node5->right);
    }

    if (node4->left != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase10 function. Left child of node4 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node4->left);
    }

    if (node4->right != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase10 function. Right child of node4 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node4->right);
    }

    if (node7->left != node6)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase10 function. Left child of node7 isn't node6. There is %14p. \n", (char *)__FILE__, __LINE__, node7->left);
    }

    if (node7->right != node8)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase10 function. Right child of node6 isn't node8. There is %14p. \n", (char *)__FILE__, __LINE__, node7->right);
    }

    if (node6->left != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase10 function. Left child of node6 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node6->left);
    }

    if (node6->right != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase10 function. Right child of node6 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node6->right);
    }

    if (node8->left != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase10 function. Left child of node8 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node8->left);
    }

    if (node8->right != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase10 function. Right child of node8 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node8->right);
    }

    if (node1->parent != node3)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase10 function. Parent of node1 isn't node3. There is %14p. \n", (char *)__FILE__, __LINE__, node1->parent);
    }

    if (node3->parent != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase10 function. Parent of node3 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node3->parent);
    }

    if (node4->parent != node5)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase10 function. Parent of node4 isn't node5. There is %14p. \n", (char *)__FILE__, __LINE__, node4->parent);
    }

    if (node5->parent != node3)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase10 function. Parent of node5 isn't node3. There is %14p. \n", (char *)__FILE__, __LINE__, node5->parent);
    }

    if (node6->parent != node7)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase10 function. Parent of node6 isn't node7. There is %14p. \n", (char *)__FILE__, __LINE__, node6->parent);
    }

    if (node7->parent != node5)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase10 function. Parent of node7 isn't node5. There is %14p. \n", (char *)__FILE__, __LINE__, node7->parent);
    }

    if (node8->parent != node7)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase10 function. Parent of node8 isn't node7. There is %14p. \n", (char *)__FILE__, __LINE__, node8->parent);
    }

    if (node1->colour != Black)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase10 function. Node1 isn't black. \n", (char *)__FILE__, __LINE__);
    }

    if (node3->colour != Black)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase10 function. Node3 isn't black. \n", (char *)__FILE__, __LINE__);
    }

    if (node4->colour != Black)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase10 function. Node4 isn't black. \n", (char *)__FILE__, __LINE__);
    }

    if (node5->colour != Red)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase10 function. Node5 isn't red. \n", (char *)__FILE__, __LINE__);
    }

    if (node6->colour != Red)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase10 function. Node6 isn't red. \n", (char *)__FILE__, __LINE__);
    }

    if (node7->colour != Black)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase10 function. Node7 isn't black. \n", (char *)__FILE__, __LINE__);
    }

    if (node8->colour != Red)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase10 function. Node8 isn't red. \n", (char *)__FILE__, __LINE__);
    }

    // Now time to remove node0.

    removeFromRedBlackTree(tree, node3);

    if (tree->count != 6)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase10 function. Counter in tree isn't 6. \n", (char *)__FILE__, __LINE__);
    }

    if (node4 != tree->first)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase10 function. Node4 isn't the root of tree. There is %14p. Node4: %14p \n", (char *)__FILE__, __LINE__, tree->first, node4);
    }

    if (node4->left != node1)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase10 function. Left child of node4 isn't node1. There is %14p. \n", (char *)__FILE__, __LINE__, node4->left);
    }

    if (node4->right != node7)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase10 function. Right child of node4 isn't node7. There is %14p. \n", (char *)__FILE__, __LINE__, node4->right);
    }

    if (node5->left != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase10 function. Left child of node5 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node5->left);
    }

    if (node5->right != node6)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase10 function. Right child of node5 isn't node6. There is %14p. \n", (char *)__FILE__, __LINE__, node5->right);
    }

    if (node6->left != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase10 function. Left child of node6 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node6->left);
    }

    if (node6->right != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase10 function. Right child of node6 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node6->right);
    }

    if (node7->left != node5)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase10 function. Left child of node7 isn't node5. There is %14p. \n", (char *)__FILE__, __LINE__, node7->left);
    }

    if (node7->right != node8)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase10 function. Right child of node7 isn't node8. There is %14p. \n", (char *)__FILE__, __LINE__, node7->right);
    }

    if (node8->left != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase10 function. Left child of node8 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node8->left);
    }

    if (node8->right != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase10 function. Right child of node8 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node8->right);
    }

    if (node1->parent != node4)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase10 function. Parent of node1 isn't node4. There is %14p. \n", (char *)__FILE__, __LINE__, node1->parent);
    }

    if (node4->parent != NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase10 function. Parent of node4 isn't NULL. There is %14p. \n", (char *)__FILE__, __LINE__, node4->parent);
    }

    if (node5->parent != node7)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase10 function. Parent of node5 isn't node7. There is %14p. \n", (char *)__FILE__, __LINE__, node5->parent);
    }

    if (node6->parent != node5)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase10 function. Parent of node6 isn't node5. There is %14p. \n", (char *)__FILE__, __LINE__, node6->parent);
    }

    if (node7->parent != node4)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase10 function. Parent of node7 isn't node4. There is %14p. \n", (char *)__FILE__, __LINE__, node7->parent);
    }

    if (node8->parent != node7)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase10 function. Parent of node8 isn't node7. There is %14p. \n", (char *)__FILE__, __LINE__, node8->parent);
    }

    if (node1->colour != Black)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase10 function. Node1 isn't black. \n", (char *)__FILE__, __LINE__);
    }

    if (node4->colour != Black)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase10 function. Node4 isn't black. \n", (char *)__FILE__, __LINE__);
    }

    if (node5->colour != Black)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase10 function. Node5 isn't black. \n", (char *)__FILE__, __LINE__);
    }

    if (node6->colour != Red)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase10 function. Node6 isn't red. \n", (char *)__FILE__, __LINE__);
    }

    if (node7->colour != Red)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase10 function. Node7 isn't red. \n", (char *)__FILE__, __LINE__);
    }

    if (node8->colour != Black)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: testRedBlackTreeRemovingCase10 function. Node8 isn't black. \n", (char *)__FILE__, __LINE__);
    }

    removeRedBlackTree(tree, false);
    free(point0);
    free(point1);
    free(point2);
    free(point3);
    free(point4);
    free(point5);
    free(point6);
    free(point7);
    free(point8);
}