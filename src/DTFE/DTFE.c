#include "DTFE.h"

#if defined(WIND32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <time.h>
#include <Windows.h>
#else
#include <sys/time.h>
#include <unistd.h>
#endif

#include <gsl/gsl_linalg.h>
#include "../Utilities/myMath.h"

void circumcenterInsideSimplex(Partition *partition)
{
    int count1 = 0;
    int count2 = 0;

#if REDBLACKTREEDLL == 1
    redBlackTreeDLLNode *pointer = minimumInRedBlackSubTreeDLL(partition->triangles->first);
#elif REDBLACKTREEDLL == 2
    LUTRBTDLLNode *pointer = getFirstOfZCurveIndex(partition->triangles, 0);
#else

#endif
    BarycentricCoordinates *result = (BarycentricCoordinates *)malloc(sizeof(BarycentricCoordinates));

    int n = NO_DIM + 1;

    while (pointer != NULL)
    {
        double *matrix = (double *)malloc(n * n * sizeof(double));
        double *bVector = (double *)malloc(n * sizeof(double));

        Simplex *simplex = (Simplex *)pointer->data;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < NO_DIM; j++)
            {
                matrix[j * n + i] = simplex->vertices[i]->point.coords[j];
            }
            matrix[(n - 1) * n + i] = 1;
        }

        for (int i = 0; i < NO_DIM; i++)
            bVector[i] = simplex->circumcenter.coords[i];

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

        if (checkIfInsideSimplex(result))
            count2++;

        count1++;

        free(matrix);
        free(bVector);

#if REDBLACKTREEDLL == 1
        pointer = getNextNodeFromRedBlackTreeDLL(partition->triangles, pointer);
#elif REDBLACKTREEDLL == 2
        pointer = getNextNodeFromLUTRBTDLL(pointer);
#else
        pointer = getNextNodeFromRedBlackTree(partition->triangles, pointer);
#endif
    }

    free(result);

    printf("\nAnalyzed %i simplexes, %i have circumcenter inside simplex. \n", count1, count2);
}

long long DTFE(Partition *partition, UserOptions *options)
{
    circumcenterInsideSimplex(partition);

    struct timeval te;
    gettimeofday(&te, NULL);
    long long time1 = te.tv_sec * 1000000LL + te.tv_usec;

    calculateVolumeInEachSimplex(partition);
    calculateDensityInEachVertex(partition);

    PointWithDensity point;

    for (int i = 0; i < INTERPOLATED_FIELDS; i++)
    {
        for (BLOCK_TYPE j = 0; j < partition->gridMatrix[i]->size; j++)
        {
            BLOCK_TYPE c = j;
            for (int k = NO_DIM - 1; k >= 0; k--)
            {
                int mod = c % options->gridSize;
                if(options->MonteCarlo)
                    point.coords[k] = (double)(mod + 0.5) * (options->minMaxCoords[k][1] - options->minMaxCoords[k][0]) / (options->gridSize);
                else
                    point.coords[k] = (double)mod * (options->minMaxCoords[k][1] - options->minMaxCoords[k][0]) / (options->gridSize - 1);

                c /= options->gridSize;
            }

            bool success;
            
            if(options->MonteCarlo)
                success = calculatePointDensityMonteCarlo(partition, &point, options);
            else
                success = calculatePointDensity(partition, &point, options);

            if (!success)
            {
                printf("Error when calculating density ");
                for(int k = 0; k < NO_DIM; k++)
                {
                    printf("%f ", point.coords[k]);
                }
                printf("\n");
            }

            if (!putDataToBlockSizeArrayDouble(partition->gridMatrix[i], j, point.density))
            {
                printf("Failed to put data into BlockSizeArray\n");
            }

            if(j%1000 == 0)
            {
                printf("\rField: %i, Computed points in DTFE: %i/%i", i, j, partition->gridMatrix[i]->size);
                fflush(stdout);
            }
        }
    }

    // Below old version optimised from 3 dimensions

    // for (int i = 0; i < options->gridSize; i++)
    // {
    //     for (int j = 0; j < options->gridSize; j++)
    //     {
    //         for (int k = 0; k < options->gridSize; k++)
    //         {
    //             if (options->MonteCarlo)
    //             {
    //                 partition->gridMatrix[i][j][k].coords[0] = (double)(i + 0.5) * (options->minMaxCoords[0][1] - options->minMaxCoords[0][0]) / (options->gridSize);
    //                 partition->gridMatrix[i][j][k].coords[1] = (double)(j + 0.5) * (options->minMaxCoords[1][1] - options->minMaxCoords[1][0]) / (options->gridSize);
    //                 partition->gridMatrix[i][j][k].coords[2] = (double)(k + 0.5) * (options->minMaxCoords[2][1] - options->minMaxCoords[2][0]) / (options->gridSize);

    //                 bool success = calculatePointDensityMonteCarlo(partition, &partition->gridMatrix[i][j][k], options);

    //                 if (!success)
    //                 {
    //                     printf("Error! %i, %i, %i, %f, %f, %f \n", i, j, k, partition->gridMatrix[i][j][k].coords[0], partition->gridMatrix[i][j][k].coords[1], partition->gridMatrix[i][j][k].coords[2]);
    //                 }
    //             }
    //             else
    //             {
    //                 partition->gridMatrix[i][j][k].coords[0] = (double)i * (options->minMaxCoords[0][1] - options->minMaxCoords[0][0]) / (options->gridSize - 1);
    //                 partition->gridMatrix[i][j][k].coords[1] = (double)j * (options->minMaxCoords[1][1] - options->minMaxCoords[1][0]) / (options->gridSize - 1);
    //                 partition->gridMatrix[i][j][k].coords[2] = (double)k * (options->minMaxCoords[2][1] - options->minMaxCoords[2][0]) / (options->gridSize - 1);

    //                 // partition->gridMatrix[i][j][k].coords[0] = (double)(i + 0.5) * (options->minMaxCoords[0][1] - options->minMaxCoords[0][0]) / (options->gridSize);
    //                 // partition->gridMatrix[i][j][k].coords[1] = (double)(j + 0.5) * (options->minMaxCoords[1][1] - options->minMaxCoords[1][0]) / (options->gridSize);
    //                 // partition->gridMatrix[i][j][k].coords[2] = (double)(k + 0.5) * (options->minMaxCoords[2][1] - options->minMaxCoords[2][0]) / (options->gridSize);

    //                 bool success = calculatePointDensity(partition, &partition->gridMatrix[i][j][k], options);
    //                 // bool success = calculatePointDensityTest(partition, &partition->gridMatrix[i][j][k], options);

    //                 if (!success)
    //                 {
    //                     printf("Error! %i, %i, %i, %f, %f, %f \n", i, j, k, partition->gridMatrix[i][j][k].coords[0], partition->gridMatrix[i][j][k].coords[1], partition->gridMatrix[i][j][k].coords[2]);
    //                 }
    //             }
    //         }
    //     }
    //     printf("\rComputed points in DTFE: %i/%i", i, options->gridSize);
    //     fflush(stdout);
    // }

    printf("\n");

    struct timeval te2;
    gettimeofday(&te2, NULL);
    long long time2 = te2.tv_sec * 1000000LL + te2.tv_usec;

    return time2 - time1;
}

void calculateDensityInEachVertex(Partition *partition)
{
    redBlackTreeNode *pointer = minimumInRedBlackSubTree(partition->vertices->first);

    double totalMass = 0;

    while (pointer != NULL)
    {
        PointId *point = (PointId *)pointer->data;
        totalMass += point->mass;

        pointer = getNextNodeFromRedBlackTree(partition->vertices, pointer);
    }

    pointer = minimumInRedBlackSubTree(partition->globalVertices->first);

    while (pointer != NULL)
    {
        PointId *point = (PointId *)pointer->data;
        totalMass += point->mass;

        pointer = getNextNodeFromRedBlackTree(partition->globalVertices, pointer);
    }

    // double avgMass = totalMass / (partition->globalVertices->count + partition->vertices->count);

    // printf("Total mass: %e \n", totalMass);

    double avgSimplexVolume = 1.0 / partition->triangles->count;

    printf("Number of triangles: %i, expected avg simplex volume: %e\n", partition->triangles->count, avgSimplexVolume);

    pointer = minimumInRedBlackSubTree(partition->vertices->first);

    while (pointer != NULL)
    {
        PointId *point = (PointId *)pointer->data;

        // point->density = point->mass * point->count / (point->density / avgSimplexVolume) / avgMass;
        point->density = point->mass * (NO_DIM + 1) / point->density / totalMass;
        // printf("Denisty: %10.4f, %10.4f, %10.4f\n", point->point.coords[0], point->point.coords[1], point->density);

        pointer = getNextNodeFromRedBlackTree(partition->vertices, pointer);
    }

    // pointer = minimumInRedBlackSubTree(partition->globalVertices->first);

    // while (pointer != NULL)
    // {
    //     PointId *point = (PointId *)pointer->data;

    //     point->density = point->mass * point->count / (point->density / avgSimplexVolume) / avgMass;
    //     printf("Denisty: %10.4f, %10.4f, %10.4f, %e\n", point->point.coords[0], point->point.coords[1], point->point.coords[2], point->density);

    //     pointer = getNextNodeFromRedBlackTree(partition->globalVertices, pointer);
    // }
}

void calculateVolumeInEachSimplex(Partition *partition)
{
#if REDBLACKTREEDLL == 1
    redBlackTreeDLLNode *pointer = minimumInRedBlackSubTreeDLL(partition->triangles->first);
#elif REDBLACKTREEDLL == 2
    LUTRBTDLLNode *pointer = getFirstOfZCurveIndex(partition->triangles, 0);
#else
    redBlackTreeNode *pointer = minimumInRedBlackSubTree(partition->triangles->first);
#endif

    while (pointer != NULL)
    {
        Simplex *simplex = (Simplex *)pointer->data;

        addVolumeToEachVertexInSimplex(simplex);

#if REDBLACKTREEDLL == 1
        pointer = getNextNodeFromRedBlackTreeDLL(partition->triangles, pointer);
#elif REDBLACKTREEDLL == 2
        pointer = getNextNodeFromLUTRBTDLL(pointer);
#else
        pointer = getNextNodeFromRedBlackTree(partition->triangles, pointer);
#endif
    }
}

void addVolumeToEachVertexInSimplex(Simplex *simplex)
{
    double volume = CayleyMengerDeterminant2(simplex);

    // printf("Simplex: %i, volume: %10.5f\n", simplex->id, volume);

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
        if (barycentric->coords[i] < -10e-10 || barycentric->coords[i] > 1 + 10e10)
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

bool calculatePointDensity(Partition *partition, PointWithDensity *point, UserOptions *options)
{
    Point *pointTemp = (Point *)malloc(sizeof(Point));

    for (int i = 0; i < NO_DIM; i++)
    {
        pointTemp->coords[i] = point->coords[i];
    }

#if REDBLACKTREEDLL == 1
    Simplex *simplex = findFirstSimplexToModifyPoint(pointTemp, partition, options);
#elif REDBLACKTREEDLL == 2

    Simplex *simplex = findFirstSimplexToModifyLUTPoint(pointTemp, partition, options);
#endif

    if (simplex == NULL)
    {
        printf("Didn't found first simplex to anlyze \n");
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
    printf("Analyzed %i simplexes, didn't found correct one. \n", c);
    free(pointTemp);
    return false;
}

#if REDBLACKTREEDLL == 2
bool calculatePointDensityTest(Partition *partition, PointWithDensity *point, UserOptions *options)
{
    Point *pointTemp = (Point *)malloc(sizeof(Point));

    for (int i = 0; i < NO_DIM; i++)
    {
        pointTemp->coords[i] = point->coords[i];
    }

    Simplex *simplex = findFirstSimplexToModifyLUTPointTest(pointTemp, partition, options);

    if (simplex == NULL)
    {
        printf("Didn't found first simplex to anlyze \n");
        free(pointTemp);
        return false;
    }

    BarycentricCoordinates *coords = calculateBarycentricCoordinates(simplex, point);

    point->density = interpolation(simplex, coords);

    free(pointTemp);
    return true;

    free(coords);
    free(pointTemp);
    return false;
}
#endif