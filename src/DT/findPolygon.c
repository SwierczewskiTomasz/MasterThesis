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

PolygonList *findPolygon(PointId *point, Partition *partition, LinkedList *trianglesToModify)
{
        PolygonList *edges = newPolygonList(freeEdge);
        PolygonList *removedEdges = newPolygonList(freeEdge);
        LinkedListNode *current = trianglesToModify->first;

        while (current != NULL)
        {
                Simplex *data = current->data;

#if DEBUG_TRIANGULATION == 1
                saveToLogs((char *)__FILE__, __LINE__, "Creating polygon. Analyze of simplex: ", printLongSimplex, data);
#endif

                for (int i = 0; i < NO_DIM + 1; i++)
                {
                        Edge *edge = newEdge(data, i);

#if DEBUG_TRIANGULATION == 1
                        saveToLogs((char *)__FILE__, __LINE__, "Current Edge: ", printShortEdge, edge);
#endif

                        PolygonLinkedListNode *founded = findInPolygonList(edges, edge);

#if DEBUG_TRIANGULATION == 1
                        if (founded != NULL)
                        {
                                saveToLogs((char *)__FILE__, __LINE__, "Edge from founded: ", printShortEdge, founded->edge);
                        }
#endif

                        if (founded == NULL)
                        {
                                founded = findInPolygonList(removedEdges, edge);
                                if (founded == NULL)
                                {
                                        insertIntoPolygonList(edges, edge);
                                }
                        }
                        else
                        {

#if DEBUG_TRIANGULATION == 1
                                saveToLogs((char *)__FILE__, __LINE__, "Edge founded and removed from polygon list: ", printShortEdge, founded->edge);
#endif

                                freeEdge(edge);
                                insertIntoPolygonList(removedEdges, founded->edge);
                                removeFromPolygonList(edges, founded);
                        }
                }

#if DEBUG_TRIANGULATION == 1
                printf("partition->triangles Tree:\n");
                printRedBlackTreeDLLString(partition->triangles, printLongSimplex);
#endif
//removeFromDoubleLinkedList(partition->triangles, current->data);
#if REDBLACKTREEDLL == 1
                redBlackTreeDLLNode *fromTree = getFromRedBlackTreeDLL(partition->triangles, data);
#else
                redBlackTreeNode *fromTree = getFromRedBlackTree(partition->triangles, data);
#endif

                if (fromTree == NULL)
                        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: Something very weird - Don't found simplex in triangles tree (partition->triangles), which one we want to remove. Simplex: %14p, fromTree: %14p \n", (char *)__FILE__, __LINE__, data, fromTree);

#if DEBUG_TRIANGULATION == 1
                saveToLogsWithFormatWithData((char*)__FILE__, __LINE__, printLongSimplex, fromTree->data, "Node: %14p, Simplex: %14p, Parent: %14p, Left: %14p, Right: %14p, Colour: %s \nRemoving from triangle tree this simplex: ", \
                fromTree, fromTree->data, fromTree->parent, fromTree->left, fromTree->right, fromTree->colour == Red ? "Red  " : "Black");
                
                printf("partition->triangles: \n");
                printRedBlackTreeDLLString(partition->triangles, printLongSimplex);
#endif
#if REDBLACKTREEDLL == 1
                removeFromRedBlackTreeDLL(partition->triangles, fromTree);
#else
                removeFromRedBlackTree(partition->triangles, fromTree);
#endif

#if DEBUG_TRIANGULATION == 1
                printf("partition->triangles: \n");
                printRedBlackTreeDLLString(partition->triangles, printLongSimplex);
#endif

                //Potencjalnie niebezpieczne
                // freeSimplex(data);
                current = current->next;
        }

        removePolygonList(removedEdges, true);
        return edges;
}