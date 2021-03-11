#include <stdio.h>
#include <stdlib.h>

#if defined(WIND32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <time.h>
#include <Windows.h>
#else
#include <sys/time.h>
#include <unistd.h>
#endif

#include <math.h>
#include "serialDT.h"

redBlackTree *createTreeOfEdgeOfEdges(PolygonList *edges)
{
    redBlackTree *treeEdgeOfEdges = newRedBlackTree(compareTwoEdgesOfEdges, freeEdgeOfEdge);
    PolygonLinkedListNode *currentEdge = edges->first;

    while (currentEdge != NULL)
    {
        for (int i = 0; i < NO_DIM; i++)
        {
            EdgeOfEdge *e = newEdgeOfEdge(currentEdge->edge, i);
#if DEBUG_TRIANGULATION == 1
            printf("File %s, line %i: createTreeOfEdgeOfEdges function.\n", (char *)__FILE__, __LINE__);
            printf("Created edge of edge: %14p, first: %14p, second: %14p, p1: x: %10.4f, y: %10.4f\n\n", e, e->first, e->second, e->points[0]->point.x, e->points[0]->point.y);
#endif
            redBlackTreeNode *nodeFromTree = getFromRedBlackTree(treeEdgeOfEdges, e);
            EdgeOfEdge *fromTree = NULL;

            if (nodeFromTree != NULL)
            {
                fromTree = (EdgeOfEdge *)nodeFromTree->data;
            }

#if DEBUG_TRIANGULATION == 1
            printf("File %s, line %i: createTreeOfEdgeOfEdges function.\n", (char *)__FILE__, __LINE__);
            printf("NodeFromTree: %14p ", nodeFromTree);
            if (nodeFromTree != NULL)
                printf("fromTree: %14p", fromTree);
            printf("\n\n");
#endif

            if (fromTree == NULL)
            {
#if DEBUG_TRIANGULATION == 1
                printf("File %s, line %i: createTreeOfEdgeOfEdges function.\n", (char *)__FILE__, __LINE__);
                printf("Before inserting edge of edge to tree: %14p, first: %14p, second: %14p, p1: x: %10.4f, y: %10.4f\n\n", e, e->first, e->second, e->points[0]->point.x, e->points[0]->point.y);
#endif
                insertIntoRedBlackTree(treeEdgeOfEdges, e);
#if DEBUG_TRIANGULATION == 1
                printf("File %s, line %i: createTreeOfEdgeOfEdges function.\n", (char *)__FILE__, __LINE__);
                printf("After inserting edge of edge to tree: %14p, first: %14p, second: %14p, p1: x: %10.4f, y: %10.4f\n\n", e, e->first, e->second, e->points[0]->point.x, e->points[0]->point.y);
#endif
            }
            else
            {
                freeEdgeOfEdge(e);
                if (fromTree->second == NULL)
                {
                    fromTree->second = currentEdge->edge;
                    currentEdge->edge->neighbors[i] = fromTree->first;
#if DEBUG_TRIANGULATION == 1
                    printf("File %s, line %i: createTreeOfEdgeOfEdges function.\n", (char *)__FILE__, __LINE__);
                    printf("Founded edge of edge in tree: %14p, first: %14p, second: %14p, p1: x: %10.4f, y: %10.4f\n", currentEdge->edge, currentEdge->edge->first, currentEdge->edge->second, currentEdge->edge->points[0]->point.x, currentEdge->edge->points[0]->point.y);
                    printf("i: %d, Neighbors: n1: %14p, n2: %14p \n", i, currentEdge->edge->neighbors[0], currentEdge->edge->neighbors[1]);
                    printf("Edge of Edge fromTree: %14p, first: %14p, second: %14p\n\n", fromTree, fromTree->first, fromTree->second);
#endif
                }
                else
                {
                    fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: Something very weird - founded more than 2 edges for one edge of edges. Should be only 2 edges. \n", (char *)__FILE__, __LINE__);
                    fprintf(stderr, "fromTree: %14p, first: %14p, second: %14p, Points: p1: x: %10.4f, y: %10.4f\n\n", fromTree, fromTree->first, fromTree->second, fromTree->points[0]->point.x, fromTree->points[0]->point.y);
                    sleep(4);
                }
            }
        }

        currentEdge = currentEdge->next;
    }

    return treeEdgeOfEdges;
}