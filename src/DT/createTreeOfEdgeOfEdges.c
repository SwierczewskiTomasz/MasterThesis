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
            char *string = printLongEdgeOfEdge(e);
            printf("Created edge of edge: %s\n\n", string);
            free(string);
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
                char *string = printLongEdgeOfEdge(e);
                printf("Before inserting edge of edge to tree: %s\n\n", string);
                free(string);
#endif
                insertIntoRedBlackTree(treeEdgeOfEdges, e);
#if DEBUG_TRIANGULATION == 1
                printf("File %s, line %i: createTreeOfEdgeOfEdges function.\n", (char *)__FILE__, __LINE__);
                char *string2 = printLongEdgeOfEdge(e);
                printf("After inserting edge of edge to tree: %s\n\n", string2);
                free(string2);
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
                    // char *string = printLongEdgeOfEdge(currentEdge->edge);
                    // printf("Founded edge of edge in tree:  %s\n\n", string);
                    // free(string);
                    char *string3 = printLongEdgeOfEdge(fromTree);
                    printf("Edge of Edge fromTree:  %s\n\n", string3);
                    free(string3);
#endif
                }
                else
                {
                    fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: Something very weird - founded more than 2 edges for one edge of edges. Should be only 2 edges. \n", (char *)__FILE__, __LINE__);
                    char *string = printLongEdgeOfEdge(fromTree);
                    printf("Edge of Edge fromTree:  %s\n\n", string);
                    free(string);
                    sleep(4);
                }
            }
        }

        currentEdge = currentEdge->next;
    }

    return treeEdgeOfEdges;
}