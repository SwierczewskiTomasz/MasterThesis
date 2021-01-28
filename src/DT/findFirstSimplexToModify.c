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
    forSearch->circumcenter.x = point->point.x;
    forSearch->circumcenter.y = point->point.y;
    forSearch->hilbertId = hilbertCurveDoubleXY2D(hilbertDimension, point->point.x, point->point.y, 0, 100, 0, 100);
    calculateBoxId(forSearch);
    forSearch->circumradius = 0;
    redBlackTreeNode *pointer = getFromRedBlackTreeFirstSmaller(partition->triangles, forSearch);
    redBlackTreeNode *pointer2 = pointer;

    Simplex *simplex = NULL;
    double squareDistance;
    double squareRadius;

    //     while (pointer != NULL)
    //     {
    //         simplex = (Simplex *)pointer->data;
    //         squareDistance = squareOfDistanceFromPointToPoint(simplex->circumcenter, point->point);
    //         squareRadius = simplex->circumradius * simplex->circumradius;

    // #if DEBUG_TRIANGULATION == 1
    //         printf("File %s, line %i: findFirstSimplexToModify function.\n", (char *)__FILE__, __LINE__);
    //         printf("Analyze of simplex - %14p\n\n", simplex);
    // #endif

    //         if (squareDistance <= squareRadius)
    //         {
    // #if DEBUG_TRIANGULATION == 1
    //             printf("File %s, line %i: findFirstSimplexToModify function.\n", (char *)__FILE__, __LINE__);
    //             printf("Founded simplex to modify - %14p, distance: %10.4f, radius: %10.4f\n\n", simplex, sqrt(squareDistance), sqrt(squareRadius));
    // #endif
    //             break;
    //         }

    //         //pointer = getNextNode(pointer);
    //         pointer = getNextNodeFromRedBlackTree(partition->triangles, pointer);
    //     }

    //     if (pointer == NULL)
    //     {
    //         pointer = getFromRedBlackTreeFirstSmaller(partition->triangles, forSearch);

    //         while (pointer != NULL)
    //         {
    //             simplex = (Simplex *)pointer->data;
    //             squareDistance = squareOfDistanceFromPointToPoint(simplex->circumcenter, point->point);
    //             squareRadius = simplex->circumradius * simplex->circumradius;

    // #if DEBUG_TRIANGULATION == 1
    //             printf("File %s, line %i: findFirstSimplexToModify function.\n", (char *)__FILE__, __LINE__);
    //             printf("Analyze of simplex - %14p\n\n", simplex);
    // #endif

    //             if (squareDistance <= squareRadius)
    //             {
    // #if DEBUG_TRIANGULATION == 1
    //                 printf("File %s, line %i: findFirstSimplexToModify function.\n", (char *)__FILE__, __LINE__);
    //                 printf("Founded simplex to modify - %14p, distance: %10.4f, radius: %10.4f\n\n", simplex, sqrt(squareDistance), sqrt(squareRadius));
    // #endif
    //                 break;
    //             }

    //             //pointer = getNextNode(pointer);
    //             pointer = getPrevNodeFromRedBlackTree(partition->triangles, pointer);
    //         }

    //         if (pointer == NULL)
    //         {
    //             fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: findFirstSimplexToModify function didn't found simplex to modify. \n", (char *)__FILE__, __LINE__);
    //         }
    //     }

    while (pointer != NULL || pointer2 != NULL)
    {
        if (pointer != NULL)
        {
            simplex = (Simplex *)pointer->data;
            squareDistance = squareOfDistanceFromPointToPoint(simplex->circumcenter, point->point);
            squareRadius = simplex->circumradius * simplex->circumradius;

#if DEBUG_TRIANGULATION == 1
            printf("File %s, line %i: findFirstSimplexToModify function.\n", (char *)__FILE__, __LINE__);
            printf("Analyze of simplex - %14p\n\n", simplex);
#endif

            if (squareDistance <= squareRadius)
            {
#if DEBUG_TRIANGULATION == 1
                printf("File %s, line %i: findFirstSimplexToModify function.\n", (char *)__FILE__, __LINE__);
                printf("Founded simplex to modify - %14p, distance: %10.4f, radius: %10.4f\n\n", simplex, sqrt(squareDistance), sqrt(squareRadius));
#endif
                break;
            }

            //pointer = getNextNode(pointer);

            pointer = getNextNodeFromRedBlackTree(partition->triangles, pointer);
        }

        if (pointer2 != NULL)
        {
            simplex = (Simplex *)pointer2->data;
            squareDistance = squareOfDistanceFromPointToPoint(simplex->circumcenter, point->point);
            squareRadius = simplex->circumradius * simplex->circumradius;

#if DEBUG_TRIANGULATION == 1
            printf("File %s, line %i: findFirstSimplexToModify function.\n", (char *)__FILE__, __LINE__);
            printf("Analyze of simplex - %14p\n\n", simplex);
#endif

            if (squareDistance <= squareRadius)
            {
#if DEBUG_TRIANGULATION == 1
                printf("File %s, line %i: findFirstSimplexToModify function.\n", (char *)__FILE__, __LINE__);
                printf("Founded simplex to modify - %14p, distance: %10.4f, radius: %10.4f\n\n", simplex, sqrt(squareDistance), sqrt(squareRadius));
#endif
                break;
            }

            //pointer = getNextNode(pointer);
            pointer2 = getPrevNodeFromRedBlackTree(partition->triangles, pointer2);
        }
    }

    if (pointer == NULL && pointer2 == NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: findFirstSimplexToModify function didn't found simplex to modify. \n", (char *)__FILE__, __LINE__);
    }

    free(forSearch);

    return simplex;
}

Simplex *findFirstSimplexToModifyBoxId(PointId *point, Partition *partition, int hilbertDimension)
{
    // redBlackTreeNode *pointer = minimumInRedBlackSubTree(partition->triangles->first);
    Simplex *forSearch = (Simplex *)malloc(sizeof(Simplex));
    forSearch->circumcenter.x = point->point.x;
    forSearch->circumcenter.y = point->point.y;
    forSearch->hilbertDimension = hilbertDimension;
    forSearch->hilbertId = hilbertCurveDoubleXY2D(hilbertDimension, point->point.x, point->point.y, 0, 100, 0, 100);
    calculateBoxId(forSearch);
    forSearch->circumradius = 0;

    redBlackTreeNode *pointer;
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

        //Trzeba zweryfikować, czy te współrzędne są dobre (tzn. czy odległość boxa bieżącego od początkowego jest mniejsza niż radius i większa od radius - 1)

        j = NO_DIM - 1;

        // #if DEBUG_TRIANGULATION == 1
        //         printf("Coords: %i, %i\n", boxIdCoords[0], boxIdCoords[1]);
        // #endif

        while (j >= 0 && !correctCoords)
        {

            correctCoords = true;
            //Zweryfikuj, czy wcześniej nie mieliśmy takiej sytuacji - lepiej sprawdzać, czy jest w pierścieniu - patrz poniżej:
            //Sprawdź czy jest odległość między radius a radius-1.
            double length = 0;
            for (int i = 0; i < NO_DIM; i++)
            {
                length += (boxIdCoords[i] - forSearch->boxId[i]) * (boxIdCoords[i] - forSearch->boxId[i]);
            }
            length = sqrt(length);

            if (length <= radius - 1 || length > radius)
            {
                correctCoords = false;
            }

            while (!correctCoords && j >= 0)
            {
                boxIdCoords[j]++;
                if (boxIdCoords[j] > forSearch->boxId[j] + radius || boxIdCoords[j] == hilbertDimension)
                {
                    boxIdCoords[j] = forSearch->boxId[j] - radius < 0 ? 0 : forSearch->boxId[j] - radius;
                    j--;
                    //Nadal współrzędne do poprawki. Nie weryfikuj jeszcze czy jesteśmy w pierścieniu.
                }
                else
                {
                    correctCoords = true;
                    //Zweryfikuj, czy wcześniej nie mieliśmy takiej sytuacji - lepiej sprawdzać, czy jest w pierścieniu - patrz poniżej:
                    //Sprawdź czy jest odległość między radius a radius-1.
                    double length = 0;
                    for (int i = 0; i < NO_DIM; i++)
                    {
                        length += (boxIdCoords[i] - forSearch->boxId[i]) * (boxIdCoords[i] - forSearch->boxId[i]);
                    }
                    length = sqrt(length);

                    if (length <= radius - 1 || length > radius)
                    {
                        correctCoords = false;
                    }

                    j = NO_DIM - 1;
                }
                // #if DEBUG_TRIANGULATION == 1
                //                 printf("Coords: %i, %i\n", boxIdCoords[0], boxIdCoords[1]);
                // #endif
            }
        }

#if DEBUG_TRIANGULATION == 1
        printf("Starting Coords: %i, %i\n", boxIdCoords[0], boxIdCoords[1]);
#endif

        j = NO_DIM - 1;
        while (j >= 0)
        {
            //Stwórz simplex, do znalezienia pierwszego w tym boxie
            Simplex *temp = (Simplex *)malloc(sizeof(Simplex));

#if NO_DIM == 2
            temp->circumcenter.x = -DBL_MAX;
            temp->circumcenter.y = 0;
#elif NO_DIM == 3
            temp->circumcenter.x = -DBL_MAX;
            temp->circumcenter.y = 0;
            temp->circumcenter.z = 0;
#else
            for (int i = 0; i < NO_DIM; i++)
            {
                temp->circumcenter.coords[i] = 0;
            }
            temp->circumcenter.coords[0] = -DBL_MAX;
#endif

            for (int i = 0; i < NO_DIM; i++)
            {
                temp->boxId[i] = boxIdCoords[i];
            }

            //Rozpocznij przeszukiwania w tym boxie, dopóki nadal będziesz tym boxie

            pointer = getFromRedBlackTreeFirstBigger(partition->triangles, temp);

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
                printf("Founded simplex to analyze - %14p, simplexCoords: %i, %i, coords: %i, %i, count: %i, %s \n\n", simplex, simplex->boxId[0], simplex->boxId[1], forSearch->boxId[0], forSearch->boxId[1], count, printShortSimplex(simplex));
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
            printf("Analyzing Coords: %i, %i, radius: %i, point coords: %i, %i, forSearch circumcenter: %10.4f, %10.4f \n", boxIdCoords[0], boxIdCoords[1], radius, temp->boxId[0], temp->boxId[1], forSearch->circumcenter.x, forSearch->circumcenter.y);
#endif

            while (boxIdTheSame)
            {
                //Sprawdź, czy to jest poprawny. Jeśli tak, to przydałoby się opuścić wszystkie pętle. Najłatwiej return tego simplexa.
                //Najpierw zrób free wszystkich rzeczy, których nie bęziemy potrzebować.

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
                    return simplex;
                }
                else
                {
#if DEBUG_TRIANGULATION == 1
                    printf("File %s, line %i: findFirstSimplexToModifyBoxId function.\n", (char *)__FILE__, __LINE__);
                    printf("This simplex isn't to modify - %14p, distance: %10.4f, radius: %10.4f\n", simplex, sqrt(squareDistance), sqrt(squareRadius));
                    printf("%s\n", printShortSimplex(simplex));
#endif
                }

                //To nie jest poprawny. Weź kolejny.

                pointer = getNextNodeFromRedBlackTree(partition->triangles, pointer);
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
                //             printf("%s\n", simplex == NULL ? "" : printShortSimplex(simplex));
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

            j = NO_DIM - 1;
            while (!correctCoords && j >= 0)
            {

                boxIdCoords[j]++;
                if (boxIdCoords[j] > forSearch->boxId[j] + radius || boxIdCoords[j] == hilbertDimension)
                {
                    boxIdCoords[j] = forSearch->boxId[j] - radius < 0 ? 0 : forSearch->boxId[j] - radius;
                    j--;
                    //Nadal współrzędne do poprawki. Nie weryfikuj jeszcze czy jesteśmy w pierścieniu.
                }
                else
                {
                    correctCoords = true;
                    //Zweryfikuj, czy wcześniej nie mieliśmy takiej sytuacji - lepiej sprawdzać, czy jest w pierścieniu - patrz poniżej:
                    //Sprawdź czy jest odległość między radius a radius-1.
                    double length = 0;
                    for (int i = 0; i < NO_DIM; i++)
                    {
                        length += (boxIdCoords[i] - forSearch->boxId[i]) * (boxIdCoords[i] - forSearch->boxId[i]);
                    }
                    length = sqrt(length);

                    if (length <= radius - 1 || length > radius)
                    {
                        correctCoords = false;
                    }

                    j = NO_DIM - 1;
                }
            }
        }

        //Jeśli j < 0, to znaczy, że w tej odległości radius od punktu nie znaleźliśmy boxa. Trzeba szukać dalej, przy większym radius

        if (j < 0)
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