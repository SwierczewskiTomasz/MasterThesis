#include <float.h>
#include "LUTDT.h"
#include "../../Logs/Log.h"

BLOCK_TYPE calculateZCurveId(ZCurveLUT *LUT, Point *point, UserOptions *options)
{
    BLOCK_TYPE result = 0;

    int boxId[NO_DIM];

    for (int i = 0; i < NO_DIM; i++)
    {
        boxId[i] = (int)((point->coords[i] - options->minMaxCoords[i][0]) / (options->minMaxCoords[i][1] - options->minMaxCoords[i][0]) * options->PHgridSize);
    }

    for (int i = 0; i < NO_DIM; i++)
    {
        if (boxId[i] >= options->PHgridSize)
        {
            boxId[i] = options->PHgridSize - 1;
        }
        if (boxId[i] < 0)
        {
            boxId[i] = 0;
        }
    }

    for (int i = 0; i < NO_DIM; i++)
    {
        result += LUT->data[i][boxId[i]];
    }

    return result;
}

Simplex *findFirstSimplexToModifyLUT(PointId *point, Partition *partition, UserOptions *options)
{
    BLOCK_TYPE index = 0;
    int smallShift = partition->triangles->currentBitShiftOneDimension;
    int boxId[NO_DIM];

    for (int i = 0; i < NO_DIM; i++)
    {
        boxId[i] = (int)((point->point.coords[i] - options->minMaxCoords[i][0]) / (options->minMaxCoords[i][1] - options->minMaxCoords[i][0]) * options->PHgridSize);
    }

    for (int i = 0; i < NO_DIM; i++)
    {
        if (boxId[i] >= options->PHgridSize)
        {
            boxId[i] = options->PHgridSize - 1;
        }
        if (boxId[i] < 0)
        {
            boxId[i] = 0;
        }
        boxId[i] = boxId[i] >> smallShift << smallShift;
    }

    for (int i = 0; i < NO_DIM; i++)
    {
        index += partition->triangles->LUT->data[i][boxId[i]];
    }

    LUTRBTDLLNode *pointer = NULL;
    Simplex *simplex = NULL;

    int count = 0;
    int radius = 0;
    bool correctCoords;
    int j = NO_DIM - 1;

    double squareRadius;
    double squareDistance;

    while (radius < options->PHgridSize)
    {
        //Przygotuj współrzędne, od których zaczynamy przeszukiwania przy danym radius
        index = 0;
        int boxIdCoords[NO_DIM];
        for (int i = 0; i < NO_DIM; i++)
        {
            boxIdCoords[i] = boxId[i] - radius < 0 ? 0 : boxId[i] - radius;
        }

        j = NO_DIM - 1;

        //Znajdzie pierwsze dobre współrzędne
        correctCoords = false;

        int k = NO_DIM - 1;

        if (boxIdCoords[k] == boxId[k] - radius)
        {
            correctCoords = true;
        }

        while (k >= 0 && !correctCoords)
        {
            correctCoords = true;
            if (boxIdCoords[k] != boxId[k] + radius)
            {
                boxIdCoords[k] = boxId[k] + radius;
                if (boxIdCoords[k] >= options->PHgridSize)
                {
                    boxIdCoords[k] = boxId[k] - radius < 0 ? 0 : boxId[k] - radius;
                    k--;
                    correctCoords = false;
                }
            }
            else
            {
                boxIdCoords[k] = boxId[k] - radius < 0 ? 0 : boxId[k] - radius;
                k--;
                correctCoords = false;
            }
            if (!correctCoords)
            {
                while (k >= 0 && !correctCoords)
                {
                    correctCoords = true;
                    boxIdCoords[k] = boxId[k] - radius < 0 ? 0 : boxId[k] - radius;
                    if (boxIdCoords[k] != boxId[k] - radius)
                    {
                        boxIdCoords[k] = boxId[k] + radius;
                        if (boxIdCoords[k] >= options->PHgridSize)
                        {
                            boxIdCoords[k] = boxId[k] - radius < 0 ? 0 : boxId[k] - radius;
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
            index = 0;
            for (int i = 0; i < NO_DIM; i++)
            {
                index += partition->triangles->LUT->data[i][boxIdCoords[i]];
            }

            if (index >= pow(options->PHgridSize, NO_DIM))
            {
                for (int i = 0; i < NO_DIM; i++)
                {
                    printf("%i %i\n", boxIdCoords[i], partition->triangles->LUT->data[i][boxIdCoords[i]]);
                }
                printf("Hmmmm? /n");
            }

            index = index >> partition->triangles->currentBitShift << partition->triangles->currentBitShift;
            pointer = getFirstOfZCurveIndex(partition->triangles, index);

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

                if (simplex->ZCurveId >> partition->triangles->currentBitShift << partition->triangles->currentBitShift != index)
                {
                    boxIdTheSame = false;
                }
            }

#if DEBUG_TRIANGULATION == 1
            saveToLogsWithFormat((char *)__FILE__, __LINE__, "Analyzing Coords: %i, %i, radius: %i, point coords: %i, %i\n", boxIdCoords[0], boxIdCoords[1], radius, temp->boxId[0], temp->boxId[1]);
#endif

            while (boxIdTheSame)
            {
                //Sprawdź, czy to jest poprawny. Jeśli tak, to przydałoby się opuścić wszystkie pętle. Najłatwiej return tego simplexa.
                //Najpierw zrób free wszystkich rzeczy, których nie bęziemy potrzebować.

                squareDistance = squareOfDistanceFromPointToPoint(simplex->circumcenter, point->point);
                squareRadius = simplex->circumradius * simplex->circumradius;
                count++;

                if (squareDistance <= squareRadius + DT_EPSILON)
                {
#if DEBUG_TRIANGULATION == 1
                    saveToLogsWithFormatWithData((char *)__FILE__, __LINE__, printLongSimplex, simplex, "Distance: %10.4f, radius: %10.4f, count: %i, Founded simplex to modify: ", simplex, sqrt(squareDistance), sqrt(squareRadius), count);
#endif
                    return simplex;
                }
                else
                {
#if DEBUG_TRIANGULATION == 1
                    saveToLogsWithFormatWithData((char *)__FILE__, __LINE__, printLongSimplex, simplex, "Distance: %10.4f, radius: %10.4f, This simplex isn't to modify: ", simplex, sqrt(squareDistance), sqrt(squareRadius));
#endif
                }

                pointer = getNextNodeFromLUTRBTDLL(pointer);

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

                if (simplex->ZCurveId >> partition->triangles->currentBitShift << partition->triangles->currentBitShift != index)
                {
                    boxIdTheSame = false;
                    break;
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
                            boxIdCoords[j] += 1 << partition->triangles->currentBitShiftOneDimension;
                            if (j > k)
                            {
                                if (boxIdCoords[j] > boxId[j] + radius || boxIdCoords[j] >= options->PHgridSize)
                                {
                                    boxIdCoords[j] = boxId[j] - radius < 0 ? 0 : boxId[j] - radius;
                                    j--;
                                    correctCoords = false;
                                }
                            }
                            else
                            {
                                if (boxIdCoords[j] >= boxId[j] + radius || boxIdCoords[j] >= options->PHgridSize)
                                {
                                    boxIdCoords[j] = boxId[j] - radius + 1 < 0 ? 0 : boxId[j] - radius + 1;
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
                    if (boxIdCoords[k] != boxId[k] + radius)
                    {
                        boxIdCoords[k] = boxId[k] + radius;
                        if (boxIdCoords[k] >= options->PHgridSize)
                        {
                            boxIdCoords[k] = boxId[k] - radius < 0 ? 0 : boxId[k] - radius;
                            k--;
                            correctCoords = false;
                        }
                    }
                    else
                    {
                        boxIdCoords[k] = boxId[k] - radius < 0 ? 0 : boxId[k] - radius;
                        k--;
                        correctCoords = false;
                    }
                    if (!correctCoords)
                    {
                        while (k >= 0 && !correctCoords)
                        {
                            correctCoords = true;
                            boxIdCoords[k] = boxId[k] - radius < 0 ? 0 : boxId[k] - radius;
                            if (boxIdCoords[k] != boxId[k] - radius)
                            {
                                boxIdCoords[k] = boxId[k] + radius;
                                if (boxIdCoords[k] >= options->PHgridSize)
                                {
                                    boxIdCoords[k] = boxId[k] - radius < 0 ? 0 : boxId[k] - radius;
                                    k--;
                                    correctCoords = false;
                                }
                            }
                        }
                    }
                }
            }
        }

        //Jeśli j < 0, to znaczy, że w tej odległości radius od punktu nie znaleźliśmy boxa. Trzeba szukać dalej, przy większym radius

        // #warning Trzeba dodawać nie ++ a w zależności od pojemności tablicy
        if (k < 0)
        {
            // radius++;
            radius += 1 << partition->triangles->currentBitShiftOneDimension;
        }

        //Na wszelki wypadek zeruję pointer, ponieważ nie znaleźliśmy go póki co, więc chcę zachować taką informację.
        pointer = NULL;
    }

    return simplex;
}