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
#include "../../DataStructures/edgeOfEdge.h"
#include "../../Logs/Log.h"

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
            saveToLogs((char *)__FILE__, __LINE__, "Created edge of edge: ", printLongEdgeOfEdge, e);
#endif

            redBlackTreeNode *nodeFromTree = getFromRedBlackTree(treeEdgeOfEdges, e);
            EdgeOfEdge *fromTree = NULL;

            if (nodeFromTree != NULL)
            {
                fromTree = (EdgeOfEdge *)nodeFromTree->data;
            }

#if DEBUG_TRIANGULATION == 1
            saveToLogs((char *)__FILE__, __LINE__, "NodeFromTree: ", printLongEdgeOfEdge, fromTree);
#endif

            if (fromTree == NULL)
            {
#if DEBUG_TRIANGULATION == 1
                saveToLogs((char *)__FILE__, __LINE__, "Before inserting edge of edge to tree: ", printLongEdgeOfEdge, e);
#endif

                insertIntoRedBlackTree(treeEdgeOfEdges, e);

#if DEBUG_TRIANGULATION == 1
                saveToLogs((char *)__FILE__, __LINE__, "After inserting edge of edge to tree: ", printLongEdgeOfEdge, e);
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
                    saveToLogs((char *)__FILE__, __LINE__, "Modified Edge of Edge fromTree: ", printLongEdgeOfEdge, fromTree);
#endif
                }
                else
                {
                    fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: Something very weird - founded more than 2 edges for one edge of edges. Should be only 2 edges. \n", (char *)__FILE__, __LINE__);
                    saveToLogs((char *)__FILE__, __LINE__, "Edge of Edge fromTree which one caused the error: ", printLongEdgeOfEdge, fromTree);
                }
            }
        }

        currentEdge = currentEdge->next;
    }

    return treeEdgeOfEdges;
}