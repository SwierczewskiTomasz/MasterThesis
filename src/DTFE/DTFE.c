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

    for (int i = 0; i < 250; i++)
    {
        for (int j = 0; j < 250; j++)
        {
            for (int k = 100; k < 101; k++)
            {
                // partition->densityMatrix[i][j][k].coords[0] = (double)i * 1000 * 4 + 1;
                // partition->densityMatrix[i][j][k].coords[1] = (double)j * 1000 * 4 + 1;
                // partition->densityMatrix[i][j][k].coords[2] = (double)k * 1000 * 4 + 1;

                partition->densityMatrix[i][j][k].coords[0] = (double)i * 4 + 1;
                partition->densityMatrix[i][j][k].coords[1] = (double)j * 4 + 1;
                partition->densityMatrix[i][j][k].coords[2] = (double)k * 4 + 1;

                // printf("%10.4f, %10.4f\n", partition->densityMatrix[i][j].coords[0], partition->densityMatrix[i][j].coords[1]);

                bool success = calculatePointDensity(partition, &partition->densityMatrix[i][j][k]);

                if (!success)
                {
                    printf("Error! %i, %i\n", i, j);
                }
                // else
                // {
                //     // printf("Success! %i, %i\n", i, j);
                //     printf("%10.4f\n", partition->densityMatrix[i][j].density);
                // }
            }
        }
        printf("%i\n", i);
    }

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
        // printf("Denisty: %10.4f, %10.4f, %10.4f\n", point->point.coords[0], point->point.coords[1], point->density);

        pointer = getNextNodeFromRedBlackTree(partition->vertices, pointer);
    }

    pointer = minimumInRedBlackSubTree(partition->globalVertices->first);

    while (pointer != NULL)
    {
        PointId *point = (PointId *)pointer->data;

        point->density = point->mass * point->count / point->density;
        // printf("Denisty: %10.4f, %10.4f, %10.4f\n", point->point.coords[0], point->point.coords[1], point->density);

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

double interpolation(Simplex *simplex, BarycentricCoordinates *barycentric)
{
    double result = 0;
    for (int i = 0; i < NO_DIM + 1; i++)
    {
        result += simplex->vertices[i]->density * barycentric->coords[i];
    }

    return result;
}

bool checkIfInsideSimplex(BarycentricCoordinates *barycentric)
{
    for (int i = 0; i < NO_DIM + 1; i++)
    {
        if (barycentric->coords[i] < 0 || barycentric->coords[i] > 1)
            return false;
    }
    return true;
}

BarycentricCoordinates *calculateBarycentricCoordinates(Simplex *simplex, PointWithDensity *point)
{
    BarycentricCoordinates *result = (BarycentricCoordinates *)malloc(sizeof(BarycentricCoordinates));

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

    return result;
}

bool calculatePointDensity(Partition *partition, PointWithDensity *point)
{
    Point *pointTemp = (Point *)malloc(sizeof(Point));

    for (int i = 0; i < NO_DIM; i++)
    {
        pointTemp->coords[i] = point->coords[i];
    }

    Simplex *simplex = findFirstSimplexToModifyPoint(pointTemp, partition, partition->hilbertDimension);

    if (simplex == NULL)
    {    
        free(pointTemp);
        return false;
    }
        

    // saveToLogs((char*)__FILE__, __LINE__, "Founded simplex: ", printLongSimplex, simplex);
    LinkedList *list = findTrianglesToModifyPoint(simplex, pointTemp);

    LinkedListNode *current = list->first;

    // printf("list->count: %i\n", list->count);
    int c = 0;
    while (current != NULL)
    {
        simplex = (Simplex *)current->data;

        BarycentricCoordinates *coords = calculateBarycentricCoordinates(simplex, point);

        // for (int i = 0; i < NO_DIM + 1; i++)
        //     printf("%10.4f ", coords->coords[i]);
        // printf("\n");

        if (checkIfInsideSimplex(coords))
        {
            point->density = interpolation(simplex, coords);
            // point->density = log(point->density);

            removeLinkedList(list, false);
            free(pointTemp);
            // for (int i = 0; i < NO_DIM + 1; i++)
            //     printf("%10.4f ", coords->coords[i]);
            // printf(" True!\n");
            // printf("%i, %10.4f\n", c, point->density);
            return true;
        }
        // else
        // {
        //     for (int i = 0; i < NO_DIM + 1; i++)
        //         printf("%10.4f ", coords->coords[i]);
        //     printf("\n");
        // }
        c++;
        free(coords);
        current = current->next;
    }

    removeLinkedList(list, false);
    free(pointTemp);
    return false;
}