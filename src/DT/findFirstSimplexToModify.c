#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#if defined(WIND32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <time.h>
#include <Windows.h>
#else
#include <sys/time.h>
#include <unistd.h>
#endif

#include <math.h>
#include "serialDT.h"

Simplex *findFirstSimplexToModify(PointId *point, Partition *partition, int hilbertDimension)
{
    // redBlackTreeNode *pointer = minimumInRedBlackSubTree(partition->triangles->first);
    Simplex *forSearch = (Simplex *)malloc(sizeof(Simplex));
//     forSearch->circumcenter.x = point->point.x;
//     forSearch->circumcenter.y = point->point.y;
// #if NO_DIM == 3
//     forSearch->circumcenter.z = point->point.z;
// #endif
//     forSearch->hilbertDimension = hilbertDimension;
//     forSearch->hilbertId = hilbertCurveDoubleXY2D(hilbertDimension, point->point.x, point->point.y, 0, 100, 0, 100);
//     calculateBoxId(forSearch);
//     forSearch->circumradius = 0;
    createNewSimplexToSearch(forSearch, &point->point, hilbertDimension);

#if REDBLACKTREEDLL == 1
    redBlackTreeDLLNode *pointer;
#else
    redBlackTreeNode *pointer;
#endif
    Simplex *simplex = NULL;
    double squareDistance;
    double squareRadius;
    bool correctCoords = false;
    int j;

    // printf("Test doubli: %i, %i, %i, coords: %i, %i\n", (int)3.4, (int)3.5, (int)3.7, forSearch->boxId[0], forSearch->boxId[1]);

    int count = 0;
    int radius = 0;
    while (radius < hilbertDimension)
    {
        //Przygotuj współrzędne, od których zaczynamy przeszukiwania przy danym radius
        int boxIdCoords[NO_DIM];
        for (int i = 0; i < NO_DIM; i++)
        {
            boxIdCoords[i] = forSearch->boxId[i] - radius < 0 ? 0 : forSearch->boxId[i] - radius;
        }

        j = NO_DIM - 1;

        //Znajdzie pierwsze dobre współrzędne
        correctCoords = false;

        int k = NO_DIM - 1;

        if (boxIdCoords[k] == forSearch->boxId[k] - radius)
        {
            correctCoords = true;
        }

        while (k >= 0 && !correctCoords)
        {
            correctCoords = true;
            if (boxIdCoords[k] != forSearch->boxId[k] + radius)
            {
                boxIdCoords[k] = forSearch->boxId[k] + radius;
                if (boxIdCoords[k] >= hilbertDimension)
                {
                    boxIdCoords[k] = forSearch->boxId[k] - radius < 0 ? 0 : forSearch->boxId[k] - radius;
                    k--;
                    correctCoords = false;
                }
            }
            else
            {
                boxIdCoords[k] = forSearch->boxId[k] - radius < 0 ? 0 : forSearch->boxId[k] - radius;
                k--;
                correctCoords = false;
            }
            if (!correctCoords)
            {
                while (k >= 0 && !correctCoords)
                {
                    correctCoords = true;
                    boxIdCoords[k] = forSearch->boxId[k] - radius < 0 ? 0 : forSearch->boxId[k] - radius;
                    if (boxIdCoords[k] != forSearch->boxId[k] - radius)
                    {
                        boxIdCoords[k] = forSearch->boxId[k] + radius;
                        if (boxIdCoords[k] >= hilbertDimension)
                        {
                            boxIdCoords[k] = forSearch->boxId[k] - radius < 0 ? 0 : forSearch->boxId[k] - radius;
                            k--;
                            correctCoords = false;
                        }
                    }
                }
            }
        }

#if DEBUG_TRIANGULATION == 1
        printf("Starting Coords: %i, %i\n", boxIdCoords[0], boxIdCoords[1]);
#endif
        j = NO_DIM - 1;

        // printf("boxIdCoords: %i, %i, forSearch boxId: %i, %i, j: %2i, k: %2i, correctCoords: %i, radius: %i - 1\n", boxIdCoords[0], boxIdCoords[1], forSearch->boxId[0], forSearch->boxId[1], j, k, correctCoords, radius);

        while (k >= 0)
        {
            //Stwórz simplex, do znalezienia pierwszego w tym boxie
            Simplex *temp = (Simplex *)malloc(sizeof(Simplex));

// #if NO_DIM == 2
//             temp->circumcenter.x = -DBL_MAX;
//             temp->circumcenter.y = 0;
// #elif NO_DIM == 3
//             temp->circumcenter.x = -DBL_MAX;
//             temp->circumcenter.y = 0;
//             temp->circumcenter.z = 0;
// #else
            for (int i = 0; i < NO_DIM; i++)
            {
                temp->circumcenter.coords[i] = 0;
            }
            temp->circumcenter.coords[0] = -DBL_MAX;
// #endif

            for (int i = 0; i < NO_DIM; i++)
            {
                temp->boxId[i] = boxIdCoords[i];
            }

            //Rozpocznij przeszukiwania w tym boxie, dopóki nadal będziesz tym boxie
#if REDBLACKTREEDLL == 1
            pointer = getFromRedBlackTreeFirstBiggerDLL(partition->triangles, temp);
#else
            pointer = getFromRedBlackTreeFirstBigger(partition->triangles, temp);
#endif

            bool boxIdTheSame = true;
            if (pointer == NULL)
            {
                boxIdTheSame = false;
            }
            else
            {
                simplex = (Simplex *)pointer->data;
#if DEBUG_TRIANGULATION == 1
                printf("File %s, line %i: findFirstSimplexToModifyBoxId function.\n", (char *)__FILE__, __LINE__);
                printf("Founded simplex to analyze - %14p, simplexCoords: %i, %i, coords: %i, %i, count: %i, %s \n\n", simplex, simplex->boxId[0], simplex->boxId[1], forSearch->boxId[0], forSearch->boxId[1], count, printLongSimplex(simplex));
#endif

                for (int i = 0; i < NO_DIM; i++)
                {
                    if (simplex->boxId[i] != boxIdCoords[i])
                    {
                        boxIdTheSame = false;
                        break;
                    }
                }
            }

#if DEBUG_TRIANGULATION == 1
            printf("Analyzing Coords: %i, %i, radius: %i, point coords: %i, %i, forSearch circumcenter: %s \n", boxIdCoords[0], boxIdCoords[1], radius, temp->boxId[0], temp->boxId[1], printLongSimplex(simplex));
#endif

            while (boxIdTheSame)
            {
                //Sprawdź, czy to jest poprawny. Jeśli tak, to przydałoby się opuścić wszystkie pętle. Najłatwiej return tego simplexa.
                //Najpierw zrób free wszystkich rzeczy, których nie bęziemy potrzebować.

                printf("Circumcenter: %s\n", printLongPoint(simplex->circumcenter));
                printf("Point: %s\n", printLongPointId(point));

                squareDistance = squareOfDistanceFromPointToPoint(simplex->circumcenter, point->point);
                squareRadius = simplex->circumradius * simplex->circumradius;
                count++;

                if (squareDistance <= squareRadius)
                {
#if DEBUG_TRIANGULATION == 1
                    printf("File %s, line %i: findFirstSimplexToModifyBoxId function.\n", (char *)__FILE__, __LINE__);
                    printf("Founded simplex to modify - %14p, distance: %10.4f, radius: %10.4f, count: %i \n\n", simplex, sqrt(squareDistance), sqrt(squareRadius), count);
#endif
                    free(forSearch);
                    free(temp);
                    // printf("%i\n", radius);
                    // printf("boxIdCoords: %i, %i, forSearch boxId: %i, %i, j: %2i, k: %2i, correctCoords: %i, radius: %i - Znalezione\n", boxIdCoords[0], boxIdCoords[1], forSearch->boxId[0], forSearch->boxId[1], j, k, correctCoords, radius);
                    return simplex;
                }
                else
                {
#if DEBUG_TRIANGULATION == 1
                    printf("File %s, line %i: findFirstSimplexToModifyBoxId function.\n", (char *)__FILE__, __LINE__);
                    printf("This simplex isn't to modify - %14p, distance: %10.4f, radius: %10.4f\n", simplex, sqrt(squareDistance), sqrt(squareRadius));
                    printf("%s\n", printLongSimplex(simplex));
#endif
                }

                //To nie jest poprawny. Weź kolejny.
#if REDBLACKTREEDLL == 1
                pointer = getNextNodeFromRedBlackTreeDLL(partition->triangles, pointer);
#else
                pointer = getNextNodeFromRedBlackTree(partition->triangles, pointer);
#endif

                if (pointer != NULL)
                {
                    simplex = (Simplex *)pointer->data;
                }
                else
                {
                    simplex = NULL;
                    break;
                }

                // #if DEBUG_TRIANGULATION == 1
                //             printf("File %s, line %i: findFirstSimplexToModifyBoxId function.\n", (char *)__FILE__, __LINE__);
                //             printf("Next simplex ", simplex, sqrt(squareDistance), sqrt(squareRadius));
                //             printf("%s\n", simplex == NULL ? "" : printLongSimplex(simplex));
                // #endif

                //Sprawdź, czy nadal jest w tym boxie

                for (int i = 0; i < NO_DIM; i++)
                {
                    if (simplex->boxId[i] != boxIdCoords[i])
                    {
                        boxIdTheSame = false;
                        break;
                    }
                }
            }

            //Nie znaleziono simplexa i na pewno opuściliśmy już ten box. Trzeba znaleźć kolejny box do przeszukiwań.

            correctCoords = false;

            while (k >= 0 && !correctCoords)
            {
                j = NO_DIM - 1;
                while (j >= 0 && !correctCoords)
                {
                    j = NO_DIM - 1;
                    while (j >= 0 && !correctCoords)
                    {
                        correctCoords = true;
                        if (j != k)
                        {
                            boxIdCoords[j]++;
                            if (j > k)
                            {
                                if (boxIdCoords[j] > forSearch->boxId[j] + radius || boxIdCoords[j] >= hilbertDimension)
                                {
                                    boxIdCoords[j] = forSearch->boxId[j] - radius < 0 ? 0 : forSearch->boxId[j] - radius;
                                    j--;
                                    correctCoords = false;
                                }
                            }
                            else
                            {
                                if (boxIdCoords[j] >= forSearch->boxId[j] + radius || boxIdCoords[j] >= hilbertDimension)
                                {
                                    boxIdCoords[j] = forSearch->boxId[j] - radius + 1 < 0 ? 0 : forSearch->boxId[j] - radius + 1;
                                    j--;
                                    correctCoords = false;
                                }
                            }
                        }
                        else
                        {
                            correctCoords = false;
                            j--;
                        }
                    }
                    // printf("boxIdCoords: %i, %i, forSearch boxId: %i, %i, j: %2i, k: %2i, correctCoords: %i, radius: %i - 3\n", boxIdCoords[0], boxIdCoords[1], forSearch->boxId[0], forSearch->boxId[1], j, k, correctCoords, radius);
                }
                if (!correctCoords)
                {
                    correctCoords = true;
                    if (boxIdCoords[k] != forSearch->boxId[k] + radius)
                    {
                        boxIdCoords[k] = forSearch->boxId[k] + radius;
                        if (boxIdCoords[k] >= hilbertDimension)
                        {
                            boxIdCoords[k] = forSearch->boxId[k] - radius < 0 ? 0 : forSearch->boxId[k] - radius;
                            k--;
                            correctCoords = false;
                        }
                    }
                    else
                    {
                        boxIdCoords[k] = forSearch->boxId[k] - radius < 0 ? 0 : forSearch->boxId[k] - radius;
                        k--;
                        correctCoords = false;
                    }
                    if (!correctCoords)
                    {
                        while (k >= 0 && !correctCoords)
                        {
                            correctCoords = true;
                            boxIdCoords[k] = forSearch->boxId[k] - radius < 0 ? 0 : forSearch->boxId[k] - radius;
                            if (boxIdCoords[k] != forSearch->boxId[k] - radius)
                            {
                                boxIdCoords[k] = forSearch->boxId[k] + radius;
                                if (boxIdCoords[k] >= hilbertDimension)
                                {
                                    boxIdCoords[k] = forSearch->boxId[k] - radius < 0 ? 0 : forSearch->boxId[k] - radius;
                                    k--;
                                    correctCoords = false;
                                }
                            }
                        }
                    }
                }
            }

            // printf("boxIdCoords: %i, %i, forSearch boxId: %i, %i, j: %2i, k: %2i, correctCoords: %i, radius: %i - 2\n", boxIdCoords[0], boxIdCoords[1], forSearch->boxId[0], forSearch->boxId[1], j, k, correctCoords, radius);
            //}
            free(temp);
        }

        //Jeśli j < 0, to znaczy, że w tej odległości radius od punktu nie znaleźliśmy boxa. Trzeba szukać dalej, przy większym radius

        if (k < 0)
            radius++;

        //Na wszelki wypadek zeruję pointer, ponieważ nie znaleźliśmy go póki co, więc chcę zachować taką informację.
        pointer = NULL;
    }

    if (pointer == NULL)
    {
        fprintf(stderr, "\n\x1B[31mError\x1B[0m in %s line %i: findFirstSimplexToModifyBoxId function didn't found simplex to modify. Checked simplexes: %i \n", (char *)__FILE__, __LINE__, count);
        fprintf(stderr, "%s\n", printLongPointId(point));
    }

    free(forSearch);

    return simplex;
}