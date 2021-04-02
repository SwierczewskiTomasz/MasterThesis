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

Simplex *findFirstSimplexToModify(PointId *point, Partition *partition, UserOptions *options)
{
    Simplex *forSearch = (Simplex *)malloc(sizeof(Simplex));
    createNewSimplexToSearch(forSearch, &point->point, options);

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

    while (radius < options->PHgridSize)
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
                if (boxIdCoords[k] >= options->PHgridSize)
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
                        if (boxIdCoords[k] >= options->PHgridSize)
                        {
                            boxIdCoords[k] = forSearch->boxId[k] - radius < 0 ? 0 : forSearch->boxId[k] - radius;
                            k--;
                            correctCoords = false;
                        }
                    }
                }
            }

            // for(int i = 0; i < NO_DIM; i++)
            // {
            //     printf("%i ", boxIdCoords[i]);
            // }
            // printf("\n");
        }

#if DEBUG_TRIANGULATION == 1
        saveToLogsWithFormat((char *)__FILE__, __LINE__, "Starting Coords: %i, %i\n", boxIdCoords[0], boxIdCoords[1]);
#endif
        j = NO_DIM - 1;

        while (k >= 0)
        {
            // for(int i = 0; i < NO_DIM; i++)
            // {
            //     printf("%i ", boxIdCoords[i]);
            // }
            // printf("\n");
            //Stwórz simplex, do znalezienia pierwszego w tym boxie
            Simplex *temp = (Simplex *)malloc(sizeof(Simplex));

            for (int i = 0; i < NO_DIM; i++)
            {
                temp->circumcenter.coords[i] = 0;
            }
            temp->circumcenter.coords[0] = -DBL_MAX;

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
                saveToLogs((char *)__FILE__, __LINE__, "Founded simplex to analyze: ", printLongSimplex, simplex);
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
            saveToLogsWithFormat((char *)__FILE__, __LINE__, "Analyzing Coords: %i, %i, radius: %i, point coords: %i, %i\n", boxIdCoords[0], boxIdCoords[1], radius, temp->boxId[0], temp->boxId[1]);
#endif

            // if (boxIdTheSame)
            // {
            //     saveToLogs((char*)__FILE__, __LINE__, "Point: ", printLongPointId, point);
            //     printf("%14p\n", pointer);
            //     sleep(1);
            // }

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
                    saveToLogsWithFormatWithData((char *)__FILE__, __LINE__, printLongSimplex, simplex, "Distance: %10.4f, radius: %10.4f, count: %i, Founded simplex to modify: ", simplex, sqrt(squareDistance), sqrt(squareRadius), count);
#endif
                    free(forSearch);
                    free(temp);

                    return simplex;
                }
                else
                {
#if DEBUG_TRIANGULATION == 1
                    saveToLogsWithFormatWithData((char *)__FILE__, __LINE__, printLongSimplex, simplex, "Distance: %10.4f, radius: %10.4f, This simplex isn't to modify: ", simplex, sqrt(squareDistance), sqrt(squareRadius));
#endif
                }

                //To nie jest poprawny. Weź kolejny.
#if REDBLACKTREEDLL == 1
                pointer = getNextNodeFromRedBlackTreeDLL(partition->triangles, pointer);
#else
                pointer = getNextNodeFromRedBlackTree(partition->triangles, pointer);
#endif

                // printf("%14p\n", pointer);
                // sleep(1);

                if (pointer != NULL)
                {
                    simplex = (Simplex *)pointer->data;
                }
                else
                {
                    simplex = NULL;
                    break;
                }

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
                                if (boxIdCoords[j] > forSearch->boxId[j] + radius || boxIdCoords[j] >= options->PHgridSize)
                                {
                                    boxIdCoords[j] = forSearch->boxId[j] - radius < 0 ? 0 : forSearch->boxId[j] - radius;
                                    j--;
                                    correctCoords = false;
                                }
                            }
                            else
                            {
                                if (boxIdCoords[j] >= forSearch->boxId[j] + radius || boxIdCoords[j] >= options->PHgridSize)
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
                }
                if (!correctCoords)
                {
                    correctCoords = true;
                    if (boxIdCoords[k] != forSearch->boxId[k] + radius)
                    {
                        boxIdCoords[k] = forSearch->boxId[k] + radius;
                        if (boxIdCoords[k] >= options->PHgridSize)
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
                                if (boxIdCoords[k] >= options->PHgridSize)
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
        // fprintf(stderr, "%s\n", printLongPointId(point));
        saveToLogs((char *)__FILE__, __LINE__, "Point: ", printLongPointId, point);
        sleep(5);
    }

    free(forSearch);

    return simplex;
}

Simplex *findFirstSimplexToModifyPoint(Point *point, Partition *partition, UserOptions *options)
{
    Simplex *forSearch = (Simplex *)malloc(sizeof(Simplex));
    createNewSimplexToSearch(forSearch, point, options);

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
    while (radius < options->PHgridSize)
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
                if (boxIdCoords[k] >= options->PHgridSize)
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
                        if (boxIdCoords[k] >= options->PHgridSize)
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
        saveToLogsWithFormat((char *)__FILE__, __LINE__, "Starting Coords: %i, %i\n", boxIdCoords[0], boxIdCoords[1]);
#endif
        j = NO_DIM - 1;

        while (k >= 0)
        {
            //Stwórz simplex, do znalezienia pierwszego w tym boxie
            Simplex *temp = (Simplex *)malloc(sizeof(Simplex));

            for (int i = 0; i < NO_DIM; i++)
            {
                temp->circumcenter.coords[i] = 0;
            }
            temp->circumcenter.coords[0] = -DBL_MAX;

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
                saveToLogs((char *)__FILE__, __LINE__, "Founded simplex to analyze: ", printLongSimplex, simplex);
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
            saveToLogsWithFormat((char *)__FILE__, __LINE__, "Analyzing Coords: %i, %i, radius: %i, point coords: %i, %i\n", boxIdCoords[0], boxIdCoords[1], radius, temp->boxId[0], temp->boxId[1]);
#endif

            while (boxIdTheSame)
            {
                //Sprawdź, czy to jest poprawny. Jeśli tak, to przydałoby się opuścić wszystkie pętle. Najłatwiej return tego simplexa.
                //Najpierw zrób free wszystkich rzeczy, których nie bęziemy potrzebować.

                squareDistance = squareOfDistanceFromPointToPoint(simplex->circumcenter, *point);
                squareRadius = simplex->circumradius * simplex->circumradius;
                count++;

                if (squareDistance <= squareRadius)
                {
#if DEBUG_TRIANGULATION == 1
                    saveToLogsWithFormatWithData((char *)__FILE__, __LINE__, printLongSimplex, simplex, "Distance: %10.4f, radius: %10.4f, count: %i, Founded simplex to modify: ", simplex, sqrt(squareDistance), sqrt(squareRadius), count);
#endif
                    free(forSearch);
                    free(temp);

                    return simplex;
                }
                else
                {
#if DEBUG_TRIANGULATION == 1
                    saveToLogsWithFormatWithData((char *)__FILE__, __LINE__, printLongSimplex, simplex, "Distance: %10.4f, radius: %10.4f, This simplex isn't to modify: ", simplex, sqrt(squareDistance), sqrt(squareRadius));
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
                                if (boxIdCoords[j] > forSearch->boxId[j] + radius || boxIdCoords[j] >= options->PHgridSize)
                                {
                                    boxIdCoords[j] = forSearch->boxId[j] - radius < 0 ? 0 : forSearch->boxId[j] - radius;
                                    j--;
                                    correctCoords = false;
                                }
                            }
                            else
                            {
                                if (boxIdCoords[j] >= forSearch->boxId[j] + radius || boxIdCoords[j] >= options->PHgridSize)
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
                }
                if (!correctCoords)
                {
                    correctCoords = true;
                    if (boxIdCoords[k] != forSearch->boxId[k] + radius)
                    {
                        boxIdCoords[k] = forSearch->boxId[k] + radius;
                        if (boxIdCoords[k] >= options->PHgridSize)
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
                                if (boxIdCoords[k] >= options->PHgridSize)
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
        // fprintf(stderr, "%s\n", printLongPointId(point));
        saveToLogs((char *)__FILE__, __LINE__, "Point: ", printLongPoint, point);
    }

    free(forSearch);

    return simplex;
}