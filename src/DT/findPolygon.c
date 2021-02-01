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
                Simplex *simplex = data;
                printf("File %s, line %i: findPolygon function.\n", (char *)__FILE__, __LINE__);
                // printf("Creating polygon. Analyze of simplex: %14p, center: x: %10.4f, y: %10.4f, radius: %10.4f\n", simplex, simplex->circumcenter.x, simplex->circumcenter.y, simplex->circumradius);
                // printf("Points: p1: x: %10.4f, y: %10.4f, p2: x: %10.4f, y: %10.4f, p3: x: %10.4f, y: %10.4f\n", simplex->vertices[0]->point.x, simplex->vertices[0]->point.y,
                //        simplex->vertices[1]->point.x, simplex->vertices[1]->point.y, simplex->vertices[2]->point.x, simplex->vertices[2]->point.y);
                // printf("Neighbors: 0: %14p, 1: %14p, 2: %14p\n\n", simplex->neighbors[0], simplex->neighbors[1], simplex->neighbors[2]);
                printf("Creating polygon. Analyze of simplex: %s \n\n", printShortSimplex(simplex));
#endif

                for (int i = 0; i < NO_DIM + 1; i++)
                {
                        Edge *edge = newEdge(data, i);

// Do usunięcia
#if DEBUG_TRIANGULATION == 1
                        printf("File %s, line %i: findPolygon function. i: %i\n", (char *)__FILE__, __LINE__, i);
                        //     printf("Current Edge: %14p, Points: p1: x: %10.4f, y: %10.4f, p2: x: %10.4f, y: %10.4f, first: %14p, second: %14p, secondIndex: %d, neighbors: n1: %14p, n2: %14p \n\n",
                        //            edge, edge->points[0]->point.x, edge->points[0]->point.y,
                        //            edge->points[1]->point.x, edge->points[1]->point.y, edge->first, edge->second,
                        //            edge->secondIndex, edge->neighbors[0], edge->neighbors[1]);
                        printf("Current Edge: %s \n\n", printShortEdge(edge));
#endif

                        PolygonLinkedListNode *founded = findInPolygonList(edges, edge);
#if DEBUG_TRIANGULATION == 1
                        printf("File %s, line %i: findPolygon function.\n", (char *)__FILE__, __LINE__);
                        printf("Current edge: %14p, Founded edge in edges: %14p\n", edge, founded);
                        // printf("Current Edge: %14p, Points: p1: x: %10.4f, y: %10.4f, p2: x: %10.4f, y: %10.4f, first: %14p, second: %14p, secondIndex: %d, neighbors: n1: %14p, n2: %14p \n\n",
                        //        edge, edge->points[0]->point.x, edge->points[0]->point.y,
                        //        edge->points[1]->point.x, edge->points[1]->point.y, edge->first, edge->second,
                        //        edge->secondIndex, edge->neighbors[0], edge->neighbors[1]);
                        if (founded != NULL)
                        {
                                // printf("Edge from founded: %14p, p1: x: %10.4f, y: %10.4f, p2: x: %10.4f, y: %10.4f\n", founded->edge, founded->edge->points[0]->point.x, founded->edge->points[0]->point.y, founded->edge->points[1]->point.x, founded->edge->points[1]->point.y);
                                printf("Edge from founded: %s\n", printShortEdge(founded->edge));
                        }
                        printf("\n");
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
                                printf("File %s, line %i: findPolygon function.\n", (char *)__FILE__, __LINE__);
                                // printf("Edge founded and removed from polygon list: %14p, p1: x: %10.4f, y: %10.4f, p2: x: %10.4f, y: %10.4f\n\n", founded->edge, founded->edge->points[0]->point.x, founded->edge->points[0]->point.y, founded->edge->points[1]->point.x, founded->edge->points[1]->point.y);
                                printf("Edge founded and removed from polygon list: %s\n\n", printShortEdge(founded->edge));
#endif
                                freeEdge(edge);
                                insertIntoPolygonList(removedEdges, founded->edge);
                                removeFromPolygonList(edges, founded);
                        }
                }

#if DEBUG_TRIANGULATION == 1
                printf("partition->triangles Tree:\n");
                printRedBlackTreeString(partition->triangles, printShortSimplex);
#endif
                //removeFromDoubleLinkedList(partition->triangles, current->data);
                redBlackTreeDLLNode *fromTree = getFromRedBlackTreeDLL(partition->triangles, data);
                if (fromTree == NULL)
                        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: Something very weird - Don't found simplex in triangles tree (partition->triangles), which one we want to remove. Simplex: %14p, fromTree: %14p \n", (char *)__FILE__, __LINE__, data, fromTree);

#if DEBUG_TRIANGULATION == 1
                printf("Removing from triangle tree this simplex: \x1B[33m%14p, node: %14p\x1B[0m\n", fromTree->data, fromTree);
                simplex = (Simplex *)fromTree->data;
                printf("Node: %14p, Simplex: %14p, Parent: %14p, Left: %14p, Right: %14p, Colour: %s \n", fromTree, fromTree->data, fromTree->parent, fromTree->left, fromTree->right, fromTree->colour == Red ? "Red  " : "Black");
                // printf("Simplex: circumcenter: x: %10.4f, y: %10.4f, circumradius: %10.4f, Points: p1: x: %10.4f, y: %10.4f, p2: x: %10.4f, y: %10.4f, p3: x: %10.4f, y: %10.4f, Neighbors: n1: %14p, n2: %14p, n3: %14p\n\n",
                //        simplex->circumcenter.x, simplex->circumcenter.y, simplex->circumradius, simplex->vertices[0]->point.x, simplex->vertices[0]->point.y,
                //        simplex->vertices[1]->point.x, simplex->vertices[1]->point.y, simplex->vertices[2]->point.x, simplex->vertices[2]->point.y, simplex->neighbors[0], simplex->neighbors[1], simplex->neighbors[2]);
                printf("Simplex: %s\n", printShortSimplex(simplex));
                printf("partition->triangles: \n");
                printRedBlackTreeString(partition->triangles, printShortSimplex);
#endif

                removeFromRedBlackTreeDLL(partition->triangles, fromTree);

#if DEBUG_TRIANGULATION == 1
                printf("partition->triangles: \n");
                printRedBlackTreeString(partition->triangles, printShortSimplex);
#endif

                //Potencjalnie niebezpieczne
                // freeSimplex(data);
                current = current->next;
        }

        removePolygonList(removedEdges, true);
        return edges;
}