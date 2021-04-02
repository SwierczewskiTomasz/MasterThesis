#include "simplex.h"
#include <gsl/gsl_linalg.h>

#if ID == 1
ID_TYPE SimplexIdCount = 0;
#endif

Simplex *neighborOfSimplex(Simplex *simplex, int i)
{
    return simplex->neighbors[i];
}

void createNewSimplex(Simplex *result, PointId *points[NO_DIM + 1], UserOptions *options)
{
    int n = NO_DIM + 1;

#if ID == 1
    result->id = SimplexIdCount++;
#endif

    memcpy(result->vertices, points, n * sizeof(PointId *));

    // calculateCircumcircle(result);
    calculateCircumcircleGSL(result);
    result->hilbertDimension = options->PHgridSize;

    calculateBoxId(result, options);

    // Funkcjonalność do PeanoHilbert
    double x = 0.0;
    double y = 0.0;
    for (int i = 0; i < n; i++)
    {
        x += points[i]->point.coords[0];
        y += points[i]->point.coords[1];
    }

    x /= n;
    y /= n;

    result->hilbertId = hilbertCurveDoubleXY2D(options->PHgridSize, x, y, 0, 100, 0, 100);

    for(int i = 0; i < NO_DIM + 1; i++)
    {
        result->neighbors[i] = NULL;
    }

    // Funkcjonalność do centroid:

    //     result->centroid.x = 0;
    //     result->centroid.y = 0;
    // #if NO_DIM == 3
    //     result->centroid.z = 0;
    // #endif

    //     for (int i = 0; i < NO_DIM + 1; i++)
    //     {
    //         result->centroid.x += result->vertices[i]->point.x;
    //         result->centroid.y += result->vertices[i]->point.y;
    // #if NO_DIM == 3
    //         result->centroid.z += result->vertices[i]->point.z;
    // #endif
    //     }

    //     result->centroid.x /= NO_DIM + 1;
    //     result->centroid.y /= NO_DIM + 1;
    // #if NO_DIM == 3
    //     result->centroid.z /= NO_DIM + 1;
    // #endif
}

void createNewSimplexToSearch(Simplex *simplex, Point *point, UserOptions *options)
{
    for (int i = 0; i < NO_DIM; i++)
        simplex->vertices[i] = NULL;

    memcpy(&simplex->circumcenter, point, sizeof(Point));
    simplex->circumradius = 0;
    simplex->hilbertDimension = options->PHgridSize;

    calculateBoxId(simplex, options);
}

void freeSimplex(void *s)
{
    Simplex *simplex = (Simplex *)s;
    free(simplex);
}

void calculateCircumcircle(Simplex *simplex)
{
#if NO_DIM == 1
    int n = NO_DIM + 1;

    double r[NO_DIM + 1];
    for (int i = 0; i < n; i++)
    {
        r[i] = simplex->vertices[i]->point.coords[0] * simplex->vertices[i]->point.coords[0] + simplex->vertices[i]->point.coords[1] * simplex->vertices[i]->point.coords[1];
    }

    double **bxMatrix = (double **)malloc(n * sizeof(double *));
    double **byMatrix = (double **)malloc(n * sizeof(double *));
    double **aMatrix = (double **)malloc(n * sizeof(double *));
    double **cMatrix = (double **)malloc(n * sizeof(double *));

    for (int i = 0; i < n; i++)
    {
        bxMatrix[i] = (double *)malloc(n * sizeof(double));
        byMatrix[i] = (double *)malloc(n * sizeof(double));
        aMatrix[i] = (double *)malloc(n * sizeof(double));
        cMatrix[i] = (double *)malloc(n * sizeof(double));
    }

    for (int i = 0; i < n; i++)
    {
        bxMatrix[i][0] = r[i];
        bxMatrix[i][1] = simplex->vertices[i]->point.coords[1];
        bxMatrix[i][2] = 1;

        byMatrix[i][0] = r[i];
        byMatrix[i][1] = simplex->vertices[i]->point.coords[0];
        byMatrix[i][2] = 1;

        aMatrix[i][0] = simplex->vertices[i]->point.coords[0];
        aMatrix[i][1] = simplex->vertices[i]->point.coords[1];
        aMatrix[i][2] = 1;

        cMatrix[i][0] = r[i];
        cMatrix[i][1] = simplex->vertices[i]->point.coords[0];
        cMatrix[i][2] = simplex->vertices[i]->point.coords[1];
    }

    double bx = -determinant(bxMatrix, n);
    double by = determinant(byMatrix, n);
    double a = determinant(aMatrix, n);
    double c = -determinant(cMatrix, n);

    double x0 = -bx / (2 * a);
    double y0 = -by / (2 * a);

    //Zastanowić się, czy potrzebujemy radius, czy wystarczy nam radius^2. Wtedy jedna operacja sqrt mniej.
    double radius = sqrt(bx * bx + by * by - 4 * a * c) / (2 * fabs(a));

    // printMatrix(aMatrix, n);
    // printMatrix(bxMatrix, n);
    // printMatrix(byMatrix, n);
    // printMatrix(cMatrix, n);
    // printf("a: %15.4f, bx: %15.4f, by: %15.4f, c: %15.4f, radius: %15.4f \n", a, bx, by, c, radius);

    simplex->circumcenter.coords[0] = x0;
    simplex->circumcenter.coords[1] = y0;
    simplex->circumradius = radius;

    for (int i = 0; i < n; i++)
    {
        free(bxMatrix[i]);
        free(byMatrix[i]);
        free(aMatrix[i]);
        free(cMatrix[i]);
    }

    free(bxMatrix);
    free(byMatrix);
    free(aMatrix);
    free(cMatrix);
#else
    // #elif NO_DIM == 3
    // int n = NO_DIM + 1;

    // double r[NO_DIM + 1];
    // for (int i = 0; i < n; i++)
    // {
    //     r[i] = simplex->vertices[i]->point.coords[0] * simplex->vertices[i]->point.coords[0] + simplex->vertices[i]->point.coords[1] * simplex->vertices[i]->point.coords[1] + simplex->vertices[i]->point.coords[2] * simplex->vertices[i]->point.coords[2];
    // }

    // double **bxMatrix = (double **)malloc(n * sizeof(double *));
    // double **byMatrix = (double **)malloc(n * sizeof(double *));
    // double **bzMatrix = (double **)malloc(n * sizeof(double *));
    // double **aMatrix = (double **)malloc(n * sizeof(double *));
    // double **cMatrix = (double **)malloc(n * sizeof(double *));

    // for (int i = 0; i < n; i++)
    // {
    //     bxMatrix[i] = (double *)malloc(n * sizeof(double));
    //     byMatrix[i] = (double *)malloc(n * sizeof(double));
    //     bzMatrix[i] = (double *)malloc(n * sizeof(double));
    //     aMatrix[i] = (double *)malloc(n * sizeof(double));
    //     cMatrix[i] = (double *)malloc(n * sizeof(double));
    // }

    // for (int i = 0; i < n; i++)
    // {
    //     bxMatrix[i][0] = r[i];
    //     bxMatrix[i][1] = simplex->vertices[i]->point.coords[1];
    //     bxMatrix[i][2] = simplex->vertices[i]->point.coords[2];
    //     bxMatrix[i][3] = 1;

    //     byMatrix[i][0] = r[i];
    //     byMatrix[i][1] = simplex->vertices[i]->point.coords[0];
    //     byMatrix[i][2] = simplex->vertices[i]->point.coords[2];
    //     byMatrix[i][3] = 1;

    //     bzMatrix[i][0] = r[i];
    //     bzMatrix[i][1] = simplex->vertices[i]->point.coords[0];
    //     bzMatrix[i][2] = simplex->vertices[i]->point.coords[1];
    //     bzMatrix[i][3] = 1;

    //     aMatrix[i][0] = simplex->vertices[i]->point.coords[0];
    //     aMatrix[i][1] = simplex->vertices[i]->point.coords[1];
    //     aMatrix[i][2] = simplex->vertices[i]->point.coords[2];
    //     aMatrix[i][3] = 1;

    //     cMatrix[i][0] = r[i];
    //     cMatrix[i][1] = simplex->vertices[i]->point.coords[0];
    //     cMatrix[i][2] = simplex->vertices[i]->point.coords[1];
    //     cMatrix[i][3] = simplex->vertices[i]->point.coords[2];
    // }

    // double bx = determinant(bxMatrix, n);
    // double by = -determinant(byMatrix, n);
    // double bz = determinant(bzMatrix, n);
    // double a = determinant(aMatrix, n);
    // double c = determinant(cMatrix, n);

    // double x0 = bx / (2 * a);
    // double y0 = by / (2 * a);
    // double z0 = bz / (2 * a);

    // double radius = sqrt(bx * bx + by * by + bz * bz - 4 * a * c) / (2 * fabs(a));

    // simplex->circumcenter.coords[0] = x0;
    // simplex->circumcenter.coords[1] = y0;
    // simplex->circumcenter.coords[2] = z0;
    // simplex->circumradius = radius;

    // if (isnan(radius))
    // {
    //     printf("aMatrix: \n");
    //     for (int i = 0; i < n; i++)
    //     {
    //         for (int j = 0; j < n; j++)
    //         {
    //             printf("%10.4f ", aMatrix[i][j]);
    //         }
    //         printf("\n");
    //     }

    //     printf("bxMatrix: \n");
    //     for (int i = 0; i < n; i++)
    //     {
    //         for (int j = 0; j < n; j++)
    //         {
    //             printf("%10.4f ", bxMatrix[i][j]);
    //         }
    //         printf("\n");
    //     }

    //     printf("byMatrix: \n");
    //     for (int i = 0; i < n; i++)
    //     {
    //         for (int j = 0; j < n; j++)
    //         {
    //             printf("%10.4f ", byMatrix[i][j]);
    //         }
    //         printf("\n");
    //     }

    //     printf("bzMatrix: \n");
    //     for (int i = 0; i < n; i++)
    //     {
    //         for (int j = 0; j < n; j++)
    //         {
    //             printf("%10.4f ", bzMatrix[i][j]);
    //         }
    //         printf("\n");
    //     }

    //     printf("cMatrix: \n");
    //     for (int i = 0; i < n; i++)
    //     {
    //         for (int j = 0; j < n; j++)
    //         {
    //             printf("%10.4f ", cMatrix[i][j]);
    //         }
    //         printf("\n");
    //     }

    //     printf("n");

    //     printf("\x1B[31mError\x1B[0m in %s line %i: Circumradius isn't the number! \n", (char *)__FILE__, __LINE__);
    //     printf("Points: %s, %s, %s, %s\n", printLongPointId(simplex->vertices[0]), printLongPointId(simplex->vertices[1]), printLongPointId(simplex->vertices[2]), printLongPointId(simplex->vertices[3]));
    //     printf("A couple of numbers: bx: %10.4f, by: %10.4f, bz: %10.4f, a: %10.4f, c: %10.4f\n", bx, by, bz, a, c);
    //     printf("bx * bx + by * by + bz * bz - 4 * a * c: %10.4f\n", bx * bx + by * by + bz * bz - 4 * a * c);
    //     printf("sqrt(...): %10.4f, 2 * fabs(a): %10.4f \n", sqrt(bx * bx + by * by + bz * bz - 4 * a * c), 2 * fabs(a));
    //     printf("Circumcenter: %10.4f, %10.4f, %10.4f \n\n", simplex->circumcenter.x, simplex->circumcenter.y, simplex->circumcenter.z);
    // }

    // for (int i = 0; i < n; i++)
    // {
    //     free(bxMatrix[i]);
    //     free(byMatrix[i]);
    //     free(bzMatrix[i]);
    //     free(aMatrix[i]);
    //     free(cMatrix[i]);
    // }

    // free(bxMatrix);
    // free(byMatrix);
    // free(bzMatrix);
    // free(aMatrix);
    // free(cMatrix);
    // #else

    int n = NO_DIM + 1;

    double r[NO_DIM + 1];
    for (int i = 0; i < n; i++)
    {
        r[i] = 0;
        for (int j = 0; j < NO_DIM; j++)
        {
            r[i] += simplex->vertices[i]->point.coords[j] * simplex->vertices[i]->point.coords[j];
        }
    }

    double ***bMatrix = (double ***)malloc(NO_DIM * sizeof(double *));
    double **aMatrix = (double **)malloc(n * sizeof(double *));
    double **cMatrix = (double **)malloc(n * sizeof(double *));

    for (int i = 0; i < NO_DIM; i++)
    {
        bMatrix[i] = (double **)malloc(n * sizeof(double *));
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < NO_DIM; j++)
        {
            bMatrix[j][i] = (double *)malloc(n * sizeof(double));
        }
        aMatrix[i] = (double *)malloc(n * sizeof(double));
        cMatrix[i] = (double *)malloc(n * sizeof(double));
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < NO_DIM; j++)
        {
            bMatrix[j][i][0] = r[i];
            for (int k = 0; k < j; k++)
            {
                bMatrix[j][i][k + 1] = simplex->vertices[i]->point.coords[k];
            }
            for (int k = j + 1; k < NO_DIM; k++)
            {
                bMatrix[j][i][k] = simplex->vertices[i]->point.coords[k];
            }
            bMatrix[j][i][n - 1] = 1;
        }

        for (int j = 0; j < NO_DIM; j++)
        {
            aMatrix[i][j] = simplex->vertices[i]->point.coords[j];
        }
        aMatrix[i][n - 1] = 1;

        cMatrix[i][0] = r[i];
        for (int j = 0; j < NO_DIM; j++)
        {
            cMatrix[i][j + 1] = simplex->vertices[i]->point.coords[j];
        }
    }

    double *b = (double *)malloc(NO_DIM * sizeof(double));
    for (int i = 0; i < NO_DIM; i++)
    {
        b[i] = (i % 2 == 0 ? 1 : -1) * determinant(bMatrix[i], n);
    }
    double a = determinant(aMatrix, n);
    double c = (NO_DIM % 2 == 0 ? -1 : 1) * determinant(cMatrix, n);

    // printf("a: %10.4f, c: %10.4f \n", a, c);
    // for(int i = 0; i < NO_DIM; i++)
    // {
    //     printf("b%i: %10.4f \n", i, b[i]);
    // }
    // printMatrix(aMatrix, n);
    // printMatrix(cMatrix, n);
    // for(int i = 0; i < NO_DIM; i++)
    // {
    //     printf("%i\n", i);
    //     printMatrix(bMatrix[i], n);
    // }

    double *coords = (double *)malloc(NO_DIM * sizeof(double));
    for (int i = 0; i < NO_DIM; i++)
    {
        coords[i] = b[i] / (2 * a);
    }

    double square = 0;
    for (int i = 0; i < NO_DIM; i++)
    {
        square += b[i] * b[i];
    }

    //Zastanowić się, czy potrzebujemy radius, czy wystarczy nam radius^2. Wtedy jedna operacja sqrt mniej.
    double radius = sqrt(square - 4 * a * c) / (2 * fabs(a));
    // printf("Radius: %10.4f\n", radius);
    // printMatrix(aMatrix, n);
    // printMatrix(bMatrix[0], n);
    // printMatrix(bMatrix[1], n);
    // printMatrix(cMatrix, n);
    // printf("a: %15.4f, bx: %15.4f, by: %15.4f, c: %15.4f, radius: %15.4f \n", a, b[0], b[1], c, radius);
    for (int i = 0; i < NO_DIM; i++)
    {
        simplex->circumcenter.coords[i] = coords[i];
    }
    simplex->circumradius = radius;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < NO_DIM; j++)
        {
            free(bMatrix[j][i]);
        }
        free(aMatrix[i]);
        free(cMatrix[i]);
    }

    for (int i = 0; i < NO_DIM; i++)
    {
        free(bMatrix[i]);
    }

    free(bMatrix);
    free(aMatrix);
    free(cMatrix);
#endif
}

void calculateCircumcircleGSL(Simplex *simplex)
{
    int n = NO_DIM + 1;

    double r[NO_DIM + 1];
    for (int i = 0; i < n; i++)
    {
        r[i] = 0;
        for (int j = 0; j < NO_DIM; j++)
        {
            r[i] += simplex->vertices[i]->point.coords[j] * simplex->vertices[i]->point.coords[j];
        }
    }

    double **bMatrix = (double **)malloc(NO_DIM * sizeof(double *));
    double *aMatrix = (double *)malloc(n * n * sizeof(double));
    double *cMatrix = (double *)malloc(n * n * sizeof(double));

    for (int i = 0; i < NO_DIM; i++)
    {
        bMatrix[i] = (double *)malloc(n * n * sizeof(double));
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < NO_DIM; j++)
        {
            bMatrix[j][i * n] = r[i];
            for (int k = 0; k < j; k++)
            {
                bMatrix[j][i * n + k + 1] = simplex->vertices[i]->point.coords[k];
            }
            for (int k = j + 1; k < NO_DIM; k++)
            {
                bMatrix[j][i * n + k] = simplex->vertices[i]->point.coords[k];
            }
            bMatrix[j][i * n + n - 1] = 1;
        }

        for (int j = 0; j < NO_DIM; j++)
        {
            aMatrix[i * n + j] = simplex->vertices[i]->point.coords[j];
        }
        aMatrix[i * n + n - 1] = 1;

        cMatrix[i * n] = r[i];
        for (int j = 0; j < NO_DIM; j++)
        {
            cMatrix[i * n + j + 1] = simplex->vertices[i]->point.coords[j];
        }
    }

    double *b = (double *)malloc(NO_DIM * sizeof(double));
    for (int i = 0; i < NO_DIM; i++)
    {
        gsl_permutation *p = gsl_permutation_alloc(n);
        gsl_matrix_view A = gsl_matrix_view_array(bMatrix[i], n, n);
        int s = 1;
        gsl_linalg_LU_decomp(&A.matrix, p, &s);
        double det = gsl_linalg_LU_det(&A.matrix, s);

        gsl_permutation_free(p);
        b[i] = (i % 2 == 0 ? 1 : -1) * det;
    }

    gsl_permutation *p = gsl_permutation_alloc(n);
    gsl_matrix_view A = gsl_matrix_view_array(aMatrix, n, n);
    int s = 1;
    gsl_linalg_LU_decomp(&A.matrix, p, &s);
    double a = gsl_linalg_LU_det(&A.matrix, s);

    gsl_matrix_view C = gsl_matrix_view_array(cMatrix, n, n);
    gsl_linalg_LU_decomp(&C.matrix, p, &s);

    gsl_permutation_free(p);

    double c = (NO_DIM % 2 == 0 ? -1 : 1) * gsl_linalg_LU_det(&C.matrix, s);

    double *coords = (double *)malloc(NO_DIM * sizeof(double));
    for (int i = 0; i < NO_DIM; i++)
    {
        coords[i] = b[i] / (2 * a);
    }

    double square = 0;
    for (int i = 0; i < NO_DIM; i++)
    {
        square += b[i] * b[i];
    }

    double radius = sqrt(square - 4 * a * c) / (2 * fabs(a));

    for (int i = 0; i < NO_DIM; i++)
    {
        simplex->circumcenter.coords[i] = coords[i];
    }
    simplex->circumradius = radius;

    for (int i = 0; i < NO_DIM; i++)
    {
        free(bMatrix[i]);
    }

    free(bMatrix);
    free(aMatrix);
    free(cMatrix);
}

void sortPointsInSimplex(Simplex *simplex)
{
    for (int i = 0; i < NO_DIM; i++)
    {
        for (int j = 0; j < NO_DIM - i; j++)
        {
            if (comparePoints(simplex->vertices[j]->point, simplex->vertices[j + 1]->point) > 0)
            {
                // Nie jestem pewien, czy to będzie dobrze działać, bo pracujemy tak de facto na PointId *, a rzeczywiście są PointId, a ja dałem PointId **array, aby można było ją modyfikować.
                PointId *copy = simplex->vertices[j];
                simplex->vertices[j] = simplex->vertices[j + 1];
                simplex->vertices[j + 1] = copy;

                Simplex *copySimplex = simplex->neighbors[j];
                simplex->neighbors[j] = simplex->neighbors[j + 1];
                simplex->neighbors[j + 1] = copySimplex;
            }
        }
    }
}

double comparePoints(Point p1, Point p2)
{
    // #if NO_DIM == 2
    //     double result = p1.x - p2.x;
    //     if (result == 0)
    //         return p1.y - p2.y;
    //     else
    //         return result;
    // #elif NO_DIM == 3
    //     double result = p1.x - p2.x;
    //     if (result == 0)
    //     {
    //         result = p1.y - p2.y;
    //         if (result == 0)
    //             return p1.z - p2.z;
    //         else
    //             return result;
    //     }
    //     else
    //         return result;
    // #else

    for (int i = 0; i < NO_DIM; i++)
    {
        double result = p1.coords[i] - p2.coords[i];
        if (result != 0)
            return result;
    }

    return 0;
    // #endif
}

double comparePointsVoids(void *p1, void *p2)
{
    PointId *point1 = (PointId *)p1;
    PointId *point2 = (PointId *)p2;
    return comparePoints(point1->point, point2->point);
}

void calculateBoxId2(Simplex *result)
{
    // printf("%10.4f, %10.4f\n", result->centroid.x, result->centroid.y);
    double *coordsMinMax[NO_DIM];
    for (int i = 0; i < NO_DIM; i++)
    {
        coordsMinMax[i] = (double *)malloc(2 * sizeof(double));
        coordsMinMax[i][0] = 0;
        coordsMinMax[i][1] = 100;
    }

    // #if NO_DIM == 2
    //     result->boxId[0] = (int)((result->centroid.x - coordsMinMax[0][0]) / (coordsMinMax[0][1] - coordsMinMax[0][0]) * result->hilbertDimension);
    //     result->boxId[1] = (int)((result->centroid.y - coordsMinMax[1][0]) / (coordsMinMax[1][1] - coordsMinMax[1][0]) * result->hilbertDimension);
    // #elif NO_DIM == 3
    //     result->boxId[0] = (int)((result->centroid.x - coordsMinMax[0][0]) / (coordsMinMax[0][1] - coordsMinMax[0][0]) * result->hilbertDimension);
    //     result->boxId[1] = (int)((result->centroid.y - coordsMinMax[1][0]) / (coordsMinMax[1][1] - coordsMinMax[1][0]) * result->hilbertDimension);
    //     result->boxId[2] = (int)((result->centroid.z - coordsMinMax[2][0]) / (coordsMinMax[2][1] - coordsMinMax[2][0]) * result->hilbertDimension);
    // #else
    for (int i = 0; i < NO_DIM; i++)
    {
        result->boxId[i] = (int)((result->centroid.coords[i] - coordsMinMax[i][0]) / (coordsMinMax[i][1] - coordsMinMax[i][0]) * result->hilbertDimension);
    }
    // #endif
    for (int i = 0; i < NO_DIM; i++)
    {
        if (result->boxId[i] >= result->hilbertDimension)
        {
            result->boxId[i] = result->hilbertDimension - 1;
        }
        if (result->boxId[i] < 0)
        {
            result->boxId[i] = 0;
        }
        // printf("%i, ", result->boxId[i]);
    }
    // printf("\n");
}

void calculateBoxId(Simplex *result, UserOptions *options)
{
    for (int i = 0; i < NO_DIM; i++)
    {
        result->boxId[i] = (int)((result->circumcenter.coords[i] - options->minMaxCoords[i][0]) / (options->minMaxCoords[i][1] - options->minMaxCoords[i][0]) * result->hilbertDimension);
    }
    
    for (int i = 0; i < NO_DIM; i++)
    {
        if (result->boxId[i] >= result->hilbertDimension)
        {
            result->boxId[i] = result->hilbertDimension - 1;
        }
        if (result->boxId[i] < 0)
        {
            result->boxId[i] = 0;
        }
    }
}