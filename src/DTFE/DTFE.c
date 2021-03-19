#include "DTFE.h"

#if defined(WIND32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <time.h>
#include <Windows.h>
#else
#include <sys/time.h>
#include <unistd.h>
#endif

#include <gsl/gsl_linalg.h>

long long DTFE(Partition *partition)
{
    double det = CayleyMengerDeterminant(partition->triangles->first->data);
    printf("Pole powierzchni: %12.4f\n", det);

    struct timeval te;
    gettimeofday(&te, NULL);
    long long time1 = te.tv_sec * 1000000LL + te.tv_usec;

    calculateVolumeInEachSimplex(partition);
    calculateDensityInEachVertex(partition);

    struct timeval te2;
    gettimeofday(&te2, NULL);
    long long time2 = te2.tv_sec * 1000000LL + te2.tv_usec;

    return time2 - time1;
}

void calculateDensityInEachVertex(Partition *partition)
{
    redBlackTreeNode *pointer = minimumInRedBlackSubTree(partition->vertices->first);

    while (pointer != NULL)
    {
        PointId *point = (PointId *)pointer->data;

        point->density = point->mass * point->count / point->density;

        pointer = getNextNodeFromRedBlackTree(partition->vertices, pointer);
    }
}

void calculateVolumeInEachSimplex(Partition *partition)
{
    redBlackTreeDLLNode *pointer = minimumInRedBlackSubTreeDLL(partition->triangles->first);

    while (pointer != NULL)
    {
        Simplex *simplex = (Simplex *)pointer->data;

        addVolumeToEachVertexInSimplex(simplex);

        pointer = getNextNodeFromRedBlackTreeDLL(partition->triangles, pointer);
    }
}

void addVolumeToEachVertexInSimplex(Simplex *simplex)
{
    double volume = CayleyMengerDeterminant2(simplex);

    for (int i = 0; i < NO_DIM + 1; i++)
    {
        simplex->vertices[i]->count++;
        simplex->vertices[i]->density += volume;
    }
}

double CayleyMengerDeterminant(Simplex *simplex)
{
    int n = NO_DIM + 2;
    double **matrix = (double **)malloc(n * sizeof(double *));

    for (int i = 0; i < n; i++)
        matrix[i] = (double *)malloc(n * sizeof(double));

    for (int i = 0; i < n - 1; i++)
    {
        matrix[i][n - 1] = 1;
        matrix[n - 1][i] = 1;
        matrix[i][i] = 0;

        for (int j = 0; j < n - 1; j++)
        {
            double distance = squareOfDistanceFromPointToPoint(simplex->vertices[i]->point, simplex->vertices[j]->point);
            matrix[i][j] = distance;
            matrix[j][i] = distance;
        }
    }
    matrix[n - 1][n - 1] = 0;

    double det = determinant(matrix, n);
    // double det = PALUdecomposition(matrix, n);

    double l = NO_DIM % 2 == 0 ? -1 : 1;
    double m1 = 1;
    double m2 = 2;

    for (int i = 2; i < NO_DIM + 1; i++)
    {
        m1 *= i;
        m2 *= 2;
    }

    double m = m1 * m1 * m2;

    double result = l / m * det;

    for (int i = 0; i < n; i++)
        free(matrix[i]);

    free(matrix);

    return pow(result, 0.5);
}

double CayleyMengerDeterminant2(Simplex *simplex)
{
    int n = NO_DIM + 2;
    double *matrix = (double *)malloc(n * n * sizeof(double));

    for (int i = 0; i < n - 1; i++)
    {
        matrix[(i * n) + n - 1] = 1;
        matrix[(n - 1) * n + i] = 1;
        matrix[i * n + i] = 0;

        for (int j = 0; j < n - 1; j++)
        {
            double distance = squareOfDistanceFromPointToPoint(simplex->vertices[i]->point, simplex->vertices[j]->point);
            matrix[i * n + j] = distance;
            matrix[j * n + i] = distance;
        }
    }
    matrix[(n - 1) * n + n - 1] = 0;

    //double det = determinant(matrix, n);
    // double det = PALUdecomposition(matrix, n);
    gsl_permutation *p = gsl_permutation_alloc(n);
    gsl_matrix_view A = gsl_matrix_view_array(matrix, n, n);
    int s = 1;
    gsl_linalg_LU_decomp(&A.matrix, p, &s);
    double det = gsl_linalg_LU_det(&A.matrix, s);

    gsl_permutation_free(p);

    double l = NO_DIM % 2 == 0 ? -1 : 1;
    double m1 = 1;
    double m2 = 2;

    for (int i = 2; i < NO_DIM + 1; i++)
    {
        m1 *= i;
        m2 *= 2;
    }

    double m = m1 * m1 * m2;

    double result = l / m * det;

    // for (int i = 0; i < n; i++)
    //     free(matrix[i]);

    free(matrix);

    return pow(result, 0.5);
}