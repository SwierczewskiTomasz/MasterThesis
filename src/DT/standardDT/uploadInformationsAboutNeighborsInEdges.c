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

void uploadInformationsAboutNeighborsInEdges(PolygonList *edges, redBlackTree *treeEdgeOfEdges)
{
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
            if (nodeFromTree != NULL)
                saveToLogs((char *)__FILE__, __LINE__, "fromTree: ", printLongEdgeOfEdge, fromTree);
            else
                saveToLogsWithFormat((char *)__FILE__, __LINE__, "NodeFromTree: %14p", nodeFromTree);
#endif

            if (fromTree == NULL)
            {
                fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: Something very weird - we didn't found this EdgeOfEdge in tree. \n", (char *)__FILE__, __LINE__);
            }
            else
            {
                if (fromTree->second == currentEdge->edge)
                {
                    if (fromTree->first != NULL)
                    {
                        currentEdge->edge->neighbors[i] = fromTree->first;
                    }
                    else
                    {
                        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: Something very weird - Second Edge should be connected to this Edge of Edge. \n", (char *)__FILE__, __LINE__);
                    }
                }
                else
                {
                    if (fromTree->first == currentEdge->edge)
                    {
                        if (fromTree->second != NULL)
                        {
                            currentEdge->edge->neighbors[i] = fromTree->second;
                        }
                        else
                        {
                            fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: Something very weird - Second Edge should be connected to this Edge of Edge. \n", (char *)__FILE__, __LINE__);
                        }
                    }
                    else
                    {
                        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: Something very weird - We should be connected to this Edge of Edge. \n", (char *)__FILE__, __LINE__);
                    }
                }

#if DEBUG_TRIANGULATION == 1
                saveToLogs((char*)__FILE__, __LINE__, "Current edge: ", printShortEdge, currentEdge->edge);
#endif
            }
            freeEdgeOfEdge(e);
        }

        currentEdge = currentEdge->next;
    }
}