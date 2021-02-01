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

LinkedList *findTrianglesToModify(Simplex *simplex, PointId *point)
{
    LinkedList *trianglesToModify = newLinkedList(freeSimplex);

    // Teraz stwórz sobie listę odwiedzanych po kolei
    // Trzeba oznaczać te sympleksy, które już odwiedziliśmy.

    // Niech lista trianglesToModify przechowuje listę trójkątów do modyfikacji
    // Niech lista listToAnalyze przechowuje listę trójkątów, które muszę jeszcze odwiedzić
    // A drzewo tree te, które już dodałem kiedykolwiek do listy do analizy (aby nie odwiedzać ich kolejny raz).

    LinkedList *listToAnalyze = newLinkedList(freeSimplex);
    redBlackTree *tree = newRedBlackTree(comparePointers, freeSimplex);

    pushToLinkedList(listToAnalyze, simplex);
    insertIntoRedBlackTree(tree, simplex);

    while (listToAnalyze->count != 0)
    {
        simplex = popFromLinkedList(listToAnalyze);

#if DEBUG_TRIANGULATION == 1
        printf("File %s, line %i: findTrianglesToModify function.\n", (char *)__FILE__, __LINE__);
        printf("findTrianglesToModify function - simplex to analyze: %14p, center: x: %10.4f, y: %10.4f, radius: %10.4f\n", simplex, simplex->circumcenter.x, simplex->circumcenter.y, simplex->circumradius);
        printf("Points: p1: x: %10.4f, y: %10.4f, p2: x: %10.4f, y: %10.4f, p3: x: %10.4f, y: %10.4f\n", simplex->vertices[0]->point.x, simplex->vertices[0]->point.y,
               simplex->vertices[1]->point.x, simplex->vertices[1]->point.y, simplex->vertices[2]->point.x, simplex->vertices[2]->point.y);
        printf("Neighbors: 0: %14p, 1: %14p, 2: %14p\n\n", simplex->neighbors[0], simplex->neighbors[1], simplex->neighbors[2]);

        // printf("Tree (tree with simplexes anytime added to analyze): \n");
        // printRedBlackTreeTriangles(tree);
#endif

        double squareDistance = squareOfDistanceFromPointToPoint(simplex->circumcenter, point->point);
        double squareRadius = simplex->circumradius * simplex->circumradius;

        if (squareDistance <= squareRadius)
        {
            pushToLinkedList(trianglesToModify, simplex);

#if DEBUG_TRIANGULATION == 1
            printf("File %s, line %i: findTrianglesToModify function.\n", (char *)__FILE__, __LINE__);
            printf("This triangle must be later modified. Added to Linked List. Simplex: %14p \n\n", simplex);
#endif

            for (int i = 0; i < NO_DIM + 1; i++)
            {
                Simplex *toAdd = simplex->neighbors[i];

                if (toAdd == NULL)
                    continue;

                redBlackTreeNode *nodeFromTree = getFromRedBlackTree(tree, toAdd);
                Simplex *fromTree = NULL;

                if (nodeFromTree != NULL)
                {
                    fromTree = (Simplex *)nodeFromTree->data;
                }

                if (fromTree == NULL)
                {
#if DEBUG_TRIANGULATION == 1
                    printf("File %s, line %i: findTrianglesToModify function.\n", (char *)__FILE__, __LINE__);
                    printf("This neighbor must be later analized. Added to Linked List: %14p \n\n", toAdd);
#endif
                    pushToLinkedList(listToAnalyze, toAdd);
                    insertIntoRedBlackTree(tree, toAdd);
                }
                else
                {
                    if (toAdd != fromTree)
                    {
                        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: Something very weird - firstly founded this pointer in tree, but later is other that expected. toAdd: %14p, fromTree: %14p\n", (char *)__FILE__, __LINE__, toAdd, fromTree);
                        // #if DEBUG_TRIANGULATION == 1
                        //                             printf("This neighbor must be later analized. Also he has the same circum as current, but other points. Added to Linked List: %14p \n\n", toAdd);
                        // #endif
                        //                             pushToLinkedList(listToAnalyze, toAdd);
                    }
                    // Exists in tree, so we processed ealier this simplex.
                }
            }
        }
    }

    removeLinkedList(listToAnalyze, false);
    removeRedBlackTree(tree, false);

    return trianglesToModify;
}