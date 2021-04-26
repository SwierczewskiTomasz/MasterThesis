#include "DTFE.h"
#include <gsl/gsl_linalg.h>

void calculateBarycentricCoordinatesV2(BarycentricCoordinates *result, Simplex *simplex, PointWithDensity *point)
{
    int n = NO_DIM + 1;
    double *matrix = (double *)malloc(n * n * sizeof(double));
    double *bVector = (double *)malloc(n * sizeof(double));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < NO_DIM; j++)
        {
            matrix[j * n + i] = simplex->vertices[i]->point.coords[j];
        }
        matrix[(n - 1) * n + i] = 1;
    }

    for (int i = 0; i < NO_DIM; i++)
        bVector[i] = point->coords[i];

    bVector[NO_DIM] = 1;

    gsl_permutation *p = gsl_permutation_alloc(n);
    gsl_matrix_view A = gsl_matrix_view_array(matrix, n, n);
    gsl_vector_view b = gsl_vector_view_array(bVector, n);
    gsl_vector *x = gsl_vector_alloc(n);
    int s = 1;
    gsl_linalg_LU_decomp(&A.matrix, p, &s);
    gsl_linalg_LU_solve(&A.matrix, p, &b.vector, x);
    gsl_permutation_free(p);

    for (int i = 0; i < n; i++)
        result->coords[i] = x->data[i];

    gsl_vector_free(x);
    free(matrix);
    free(bVector);
}

/**
 * Return pointer to simplex, which one contain searching point, if not found return NULL.
 */
Simplex *densityInPointMonteCarlo(Partition *partition, PointWithDensity *point, LinkedList *list, Simplex *lastSimplex)
{
    LinkedListNode *current = list->first;
    Simplex *simplex;

    BarycentricCoordinates *coords = (BarycentricCoordinates *)malloc(sizeof(BarycentricCoordinates));

    if (lastSimplex != NULL)
    {
        calculateBarycentricCoordinatesV2(coords, lastSimplex, point);

        if (checkIfInsideSimplex(coords))
        {
            point->density = interpolation(lastSimplex, coords);
            free(coords);
            return lastSimplex;
        }
    }

    while (current != NULL)
    {
        simplex = (Simplex *)current->data;

        calculateBarycentricCoordinatesV2(coords, simplex, point);

        if (checkIfInsideSimplex(coords))
        {
            point->density = interpolation(simplex, coords);
            free(coords);
            return simplex;
        }

        current = current->next;
    }

    return NULL;
}

bool calculatePointDensityMonteCarlo(Partition *partition, PointWithDensity *point, UserOptions *options)
{
    Point *pointTemp = (Point *)malloc(sizeof(Point));

    for (int i = 0; i < NO_DIM; i++)
    {
        pointTemp->coords[i] = point->coords[i];
    }

    Simplex *simplex = findFirstSimplexToModifyPoint(pointTemp, partition, options);

    if (simplex == NULL)
    {
        printf("Didn't found first simplex to anlyze \n");
        free(pointTemp);
        return false;
    }

    LinkedList *list = findTrianglesToModifyPointMonteCarlo(simplex, pointTemp, options);

    printf("%i\n", list->count);

    PointWithDensity *randomPoint = (PointWithDensity *)malloc(sizeof(PointWithDensity));

    Simplex *lastSimplex = NULL;

    double result = 0;

    for (int i = 0; i < options->nMonteCarlo; i++)
    {
        for (int j = 0; j < NO_DIM; j++)
        {
            double scale = (options->minMaxCoords[j][1] - options->minMaxCoords[j][0]) / options->gridSize;
            randomPoint->coords[j] = ((double)rand() / RAND_MAX - 0.5) * scale + point->coords[j];
        }

        randomPoint->density = 0;

        lastSimplex = densityInPointMonteCarlo(partition, randomPoint, list, lastSimplex);
        if (lastSimplex == NULL)
        {
            for (int j = 0; j < NO_DIM; j++)
            {
                printf("%10.4f ", randomPoint->coords[j]);
            }
            printf("\n");
            for (int j = 0; j < NO_DIM; j++)
            {
                printf("%10.4f ", point->coords[j]);
            }
            printf("\n");

            printf("Number of triangles on list of founded triangles: %i \n", list->count);

            printf("Error - didn't found simplex, that sample is inside simplex. \n");
            sleep(1);
        }
        else if (randomPoint->density <= 0)
        {
            printf("Error?\n");
        }
        else
        {
            result += randomPoint->density;
        }
    }

    point->density = result / options->nMonteCarlo;

    removeLinkedList(list, false);

    free(pointTemp);
    return true;
}