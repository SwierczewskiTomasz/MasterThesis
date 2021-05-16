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
#include "../../DataStructures/Other/hashTable.h"
#include "../../Utilities/compare.h"

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
        saveToLogs((char *)__FILE__, __LINE__, "Simplex to analyze: ", printLongSimplex, simplex);
#endif

        double squareDistance = squareOfDistanceFromPointToPoint(simplex->circumcenter, point->point);
        double squareRadius = simplex->circumradius * simplex->circumradius;

        if (squareDistance <= squareRadius)
        {
            pushToLinkedList(trianglesToModify, simplex);

#if DEBUG_TRIANGULATION == 1
            saveToLogs((char *)__FILE__, __LINE__, "This triangle must be later modified. Added to Linked List.", printLongSimplex, simplex);
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
                    saveToLogs((char *)__FILE__, __LINE__, "This neighbor must be later analized. Added to Linked List:", printLongSimplex, toAdd);
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

LinkedList *findTrianglesToModifyPointMonteCarlo(Simplex *simplex, Point *point, UserOptions *options)
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
        saveToLogs((char *)__FILE__, __LINE__, "Simplex to analyze: ", printLongSimplex, simplex);
#endif

        double squareDistance = squareOfDistanceFromPointToPoint(simplex->circumcenter, *point);
        double temp = simplex->circumradius + options->diameterOfGrid;
        double squareRadius = temp * temp;

        bool inside = true;
        if (squareDistance <= squareRadius)
        {
            for (int i = 0; i < NO_DIM; i++)
            {
                bool allBelow = true;
                bool allAbove = true;

                for (int j = 0; j < NO_DIM + 1; j++)
                {
                    if (simplex->vertices[j]->point.coords[i] > point->coords[i] - options->diameterOfGrid)
                    {
                        allBelow = false;
                        break;
                    }
                }

                for (int j = 0; j < NO_DIM + 1; j++)
                {
                    if (simplex->vertices[j]->point.coords[i] < point->coords[i] + options->diameterOfGrid)
                    {
                        allAbove = false;
                        break;
                    }
                }

                if (allBelow || allAbove)
                {
                    inside = false;
                    break;
                }
            }
        }

        if (squareDistance <= squareRadius)
        {
            if (inside)
                pushToLinkedList(trianglesToModify, simplex);

#if DEBUG_TRIANGULATION == 1
            saveToLogs((char *)__FILE__, __LINE__, "This triangle must be later modified. Added to Linked List.", printLongSimplex, simplex);
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
                    saveToLogs((char *)__FILE__, __LINE__, "This neighbor must be later analized. Added to Linked List:", printLongSimplex, toAdd);
#endif
                    pushToLinkedList(listToAnalyze, toAdd);
                    insertIntoRedBlackTree(tree, toAdd);
                }
                else
                {
                    if (toAdd != fromTree)
                    {
                        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: Something very weird - firstly founded this pointer in tree, but later is other that expected. toAdd: %14p, fromTree: %14p\n", (char *)__FILE__, __LINE__, toAdd, fromTree);
                    }
                }
            }
        }
    }

    removeLinkedList(listToAnalyze, false);
    removeRedBlackTree(tree, false);

    return trianglesToModify;
}

LinkedList *findTrianglesToModifyPointMonteCarlo2(Simplex *simplex, Point *point, UserOptions *options)
{
    LinkedList *trianglesToModify = newLinkedList(freeSimplex);

    // Teraz stwórz sobie listę odwiedzanych po kolei
    // Trzeba oznaczać te sympleksy, które już odwiedziliśmy.

    // Niech lista trianglesToModify przechowuje listę trójkątów do modyfikacji
    // Niech lista listToAnalyze przechowuje listę trójkątów, które muszę jeszcze odwiedzić
    // A drzewo tree te, które już dodałem kiedykolwiek do listy do analizy (aby nie odwiedzać ich kolejny raz).

    LinkedList *listToAnalyze = newLinkedList(freeSimplex);
    // redBlackTree *tree = newRedBlackTree(comparePointers, freeSimplex);
    HashTable *hashTable = newHashTable(1024, simpleHash);

    pushToLinkedList(listToAnalyze, simplex);
    // insertIntoRedBlackTree(tree, simplex);
    insertIntoHashTable(hashTable, simplex->id, simplex);

    while (listToAnalyze->count != 0)
    {
        simplex = popFromLinkedList(listToAnalyze);

#if DEBUG_TRIANGULATION == 1
        saveToLogs((char *)__FILE__, __LINE__, "Simplex to analyze: ", printLongSimplex, simplex);
#endif

        double squareDistance = squareOfDistanceFromPointToPoint(simplex->circumcenter, *point);
        double temp = simplex->circumradius + options->diameterOfGrid;
        double squareRadius = temp * temp;

        bool inside = true;
        if (squareDistance <= squareRadius)
        {
            for (int i = 0; i < NO_DIM; i++)
            {
                bool allBelow = true;
                bool allAbove = true;

                for (int j = 0; j < NO_DIM + 1; j++)
                {
                    if (simplex->vertices[j]->point.coords[i] > point->coords[i] - options->diameterOfGrid)
                    {
                        allBelow = false;
                        break;
                    }
                }

                for (int j = 0; j < NO_DIM + 1; j++)
                {
                    if (simplex->vertices[j]->point.coords[i] < point->coords[i] + options->diameterOfGrid)
                    {
                        allAbove = false;
                        break;
                    }
                }

                if (allBelow || allAbove)
                {
                    inside = false;
                    break;
                }
            }
        }

        if (squareDistance <= squareRadius)
        {
            if (inside)
                pushToLinkedList(trianglesToModify, simplex);

#if DEBUG_TRIANGULATION == 1
            saveToLogs((char *)__FILE__, __LINE__, "This triangle must be later modified. Added to Linked List.", printLongSimplex, simplex);
#endif

            for (int i = 0; i < NO_DIM + 1; i++)
            {
                Simplex *toAdd = simplex->neighbors[i];

                if (toAdd == NULL)
                    continue;

                // redBlackTreeNode *nodeFromTree = getFromRedBlackTree(tree, toAdd);
                bool inHashTable = checkDataInHashTable(hashTable, toAdd->id, toAdd);

                if (!inHashTable)
                {
#if DEBUG_TRIANGULATION == 1
                    saveToLogs((char *)__FILE__, __LINE__, "This neighbor must be later analized. Added to Linked List:", printLongSimplex, toAdd);
#endif
                    pushToLinkedList(listToAnalyze, toAdd);
                    // insertIntoRedBlackTree(tree, toAdd);
                    insertIntoHashTable(hashTable, toAdd->id, toAdd);
                }
            }
        }
    }

    // printf("Count: %i\n", hashTable->count);

    removeLinkedList(listToAnalyze, false);
    // removeRedBlackTree(tree, false);
    removeHashTable(hashTable);

    return trianglesToModify;
}

LinkedList *findTrianglesToModifyPoint(Simplex *simplex, Point *point)
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
        saveToLogs((char *)__FILE__, __LINE__, "Simplex to analyze: ", printLongSimplex, simplex);
#endif

        double squareDistance = squareOfDistanceFromPointToPoint(simplex->circumcenter, *point);
        double squareRadius = simplex->circumradius * simplex->circumradius;

        if (squareDistance <= squareRadius)
        {
            pushToLinkedList(trianglesToModify, simplex);

#if DEBUG_TRIANGULATION == 1
            saveToLogs((char *)__FILE__, __LINE__, "This triangle must be later modified. Added to Linked List.", printLongSimplex, simplex);
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
                    saveToLogs((char *)__FILE__, __LINE__, "This neighbor must be later analized. Added to Linked List:", printLongSimplex, toAdd);
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