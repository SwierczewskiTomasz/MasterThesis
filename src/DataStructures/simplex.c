#include "simplex.h"
#include <stdlib.h>
#include <gsl/gsl_linalg.h>
#include "../Utilities/myMath.h"
#include "../Utilities/compare.h"
#include "LookUpTables/ZCurveLUT.h"

#if ID == 1
ID_TYPE SimplexIdCount = 0;
#endif

Simplex *neighborOfSimplex(Simplex *simplex, int i)
{
    return simplex->neighbors[i];
}

#if REDBLACKTREEDLL == 2
void createNewSimplex(Simplex *result, PointId *points[NO_DIM + 1], UserOptions *options, ZCurveLUT *LUT)
#else
void createNewSimplex(Simplex *result, PointId *points[NO_DIM + 1], UserOptions *options)
#endif
{
    int n = NO_DIM + 1;

#if ID == 1
    result->id = SimplexIdCount++;
#endif

    memcpy(result->vertices, points, n * sizeof(PointId *));

    calculateCircumcircleGSL(result);
    result->hilbertDimension = options->PHgridSize;

    calculateBoxId(result, options);

    result->ZCurveId = 0;
    for(int i = 0; i < NO_DIM; i++)
    {
        result->ZCurveId += LUT->data[i][result->boxId[i]];
    }

    for (int i = 0; i < NO_DIM + 1; i++)
    {
        result->neighbors[i] = NULL;
    }
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
    free(b);
    free(coords);
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

void sortPointsInSimplex1(Simplex *simplex)
{
    for (int i = 0; i < NO_DIM; i++)
    {
        for (int j = 0; j < NO_DIM - i; j++)
        {
            if (comparePoints(simplex->vertices[j]->point, simplex->vertices[j + 1]->point) > 0)
            {
                printf("1\n");
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

void calculateBoxId2(Simplex *result)
{
    double *coordsMinMax[NO_DIM];
    for (int i = 0; i < NO_DIM; i++)
    {
        coordsMinMax[i] = (double *)malloc(2 * sizeof(double));
        coordsMinMax[i][0] = 0;
        coordsMinMax[i][1] = 100;
    }

    for (int i = 0; i < NO_DIM; i++)
    {
        result->boxId[i] = (int)((result->centroid.coords[i] - coordsMinMax[i][0]) / (coordsMinMax[i][1] - coordsMinMax[i][0]) * result->hilbertDimension);
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