#include "simplex.h"

#if ID == 1
ID_TYPE SimplexIdCount = 0;
#endif

// PointId cw(Simplex *simplex, PointId vertex)
// {
//     for(int i = 0; i < NO_DIM + 1; i++)
//     {
//         if(memcmp(&simplex->vertices[i], &vertex, sizeof(PointId) == 0))
//             return simplex->vertices[(i + 1) % (NO_DIM + 1)];
//     }
// }

// PointId ccw(Simplex *simplex, PointId vertex)
// {
//     for(int i = 0; i < NO_DIM + 1; i++)
//     {
//         if(memcmp(&simplex->vertices[i], &vertex, sizeof(PointId) == 0))
//             return simplex->vertices[(i - 1) < 0 ? (i - 1) + (NO_DIM + 1) : (i - 1)];
//     }
// }

// PointId cw_i(Simplex *simplex, int i)
// {
//     return simplex->vertices[(i + 1) % (NO_DIM + 1)];
// }

// PointId ccw_i(Simplex *simplex, int i)
// {
//     return simplex->vertices[(i - 1) < 0 ? (i - 1) + (NO_DIM + 1) : (i - 1)];
// }

// Edge neighbor(Simplex *simplex, PointId vertex)
// {
//     for(int i = 0; i < NO_DIM + 1; i++)
//     {
//         if(memcmp(&simplex->vertices[i], &vertex, sizeof(PointId) == 0))
//             return simplex->edges[i];
//     }
// }

// Edge neighbor_i(Simplex *simplex, int i)
// {
//     return simplex->edges[i];
// }

Simplex *neighborOfSimplex(Simplex *simplex, int i)
{
    return simplex->neighbors[i];
}

void createNewSimplex(Simplex *result, PointId *points[NO_DIM + 1], int hilbertDimension)
{
    int n = NO_DIM + 1;
    //Trzeba nadać unikanlne id

#if ID == 1
    result->id = SimplexIdCount++;
#endif

    memcpy(result->vertices, points, n * sizeof(PointId *));

    // for(int i = 0; i < n; i++)
    // {
    //     printf("Vertex %i: x: %10.4f, y: %10.4f, z: %10.4f \n", i, points[i]->point.x, points[i]->point.y, points[i]->point.z);
    // }

    calculateCircumcircle(result);
    result->hilbertDimension = hilbertDimension;

    double x = 0.0;
    double y = 0.0;
    for (int i = 0; i < n; i++)
    {
        x += points[i]->point.x;
        y += points[i]->point.y;
    }

    x /= n;
    y /= n;

    result->hilbertId = hilbertCurveDoubleXY2D(hilbertDimension, x, y, 0, 100, 0, 100);
}

void freeSimplex(void *s)
{
    Simplex *simplex = (Simplex *)s;
    free(simplex);
}

void calculateCircumcircle(Simplex *simplex)
{
#if NO_DIM == 2
    int n = NO_DIM + 1;

    double r[NO_DIM + 1];
    for (int i = 0; i < n; i++)
    {
        r[i] = simplex->vertices[i]->point.x * simplex->vertices[i]->point.x + simplex->vertices[i]->point.y * simplex->vertices[i]->point.y;
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
        bxMatrix[i][1] = simplex->vertices[i]->point.y;
        bxMatrix[i][2] = 1;

        byMatrix[i][0] = r[i];
        byMatrix[i][1] = simplex->vertices[i]->point.x;
        byMatrix[i][2] = 1;

        aMatrix[i][0] = simplex->vertices[i]->point.x;
        aMatrix[i][1] = simplex->vertices[i]->point.y;
        aMatrix[i][2] = 1;

        cMatrix[i][0] = r[i];
        cMatrix[i][1] = simplex->vertices[i]->point.x;
        cMatrix[i][2] = simplex->vertices[i]->point.y;
    }

    double bx = -determinant(bxMatrix, n);
    double by = determinant(byMatrix, n);
    double a = determinant(aMatrix, n);
    double c = -determinant(cMatrix, n);

    double x0 = -bx / (2 * a);
    double y0 = -by / (2 * a);

    //Zastanowić się, czy potrzebujemy radius, czy wystarczy nam radius^2. Wtedy jedna operacja sqrt mniej.
    double radius = sqrt(bx * bx + by * by - 4 * a * c) / (2 * fabs(a));

    simplex->circumcenter.x = x0;
    simplex->circumcenter.y = y0;
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

#elif NO_DIM == 3
    int n = NO_DIM + 1;

    double r[NO_DIM + 1];
    for (int i = 0; i < n; i++)
    {
        r[i] = simplex->vertices[i]->point.x * simplex->vertices[i]->point.x + simplex->vertices[i]->point.y * simplex->vertices[i]->point.y + simplex->vertices[i]->point.z * simplex->vertices[i]->point.z;
    }

    double **bxMatrix = (double **)malloc(n * sizeof(double *));
    double **byMatrix = (double **)malloc(n * sizeof(double *));
    double **bzMatrix = (double **)malloc(n * sizeof(double *));
    double **aMatrix = (double **)malloc(n * sizeof(double *));
    double **cMatrix = (double **)malloc(n * sizeof(double *));

    for (int i = 0; i < n; i++)
    {
        bxMatrix[i] = (double *)malloc(n * sizeof(double));
        byMatrix[i] = (double *)malloc(n * sizeof(double));
        bzMatrix[i] = (double *)malloc(n * sizeof(double));
        aMatrix[i] = (double *)malloc(n * sizeof(double));
        cMatrix[i] = (double *)malloc(n * sizeof(double));
    }

    for (int i = 0; i < n; i++)
    {
        bxMatrix[i][0] = r[i];
        bxMatrix[i][1] = simplex->vertices[i]->point.y;
        bxMatrix[i][2] = simplex->vertices[i]->point.z;
        bxMatrix[i][3] = 1;

        byMatrix[i][0] = r[i];
        byMatrix[i][1] = simplex->vertices[i]->point.x;
        byMatrix[i][2] = simplex->vertices[i]->point.z;
        byMatrix[i][3] = 1;

        bzMatrix[i][0] = r[i];
        bzMatrix[i][1] = simplex->vertices[i]->point.x;
        bzMatrix[i][2] = simplex->vertices[i]->point.y;
        bzMatrix[i][3] = 1;

        aMatrix[i][0] = simplex->vertices[i]->point.x;
        aMatrix[i][1] = simplex->vertices[i]->point.y;
        aMatrix[i][2] = simplex->vertices[i]->point.z;
        aMatrix[i][3] = 1;

        cMatrix[i][0] = r[i];
        cMatrix[i][1] = simplex->vertices[i]->point.x;
        cMatrix[i][2] = simplex->vertices[i]->point.y;
        cMatrix[i][3] = simplex->vertices[i]->point.z;
    }

    double bx = determinant(bxMatrix, n);
    double by = -determinant(byMatrix, n);
    double bz = determinant(bzMatrix, n);
    double a = determinant(aMatrix, n);
    double c = -determinant(cMatrix, n);

    double x0 = bx / (2 * a);
    double y0 = by / (2 * a);
    double z0 = bz / (2 * a);

    double radius = sqrt(bx * bx + by * by + bz * bz - 4 * a * c) / (2 * fabs(a));

    simplex->circumcenter.x = x0;
    simplex->circumcenter.y = y0;
    simplex->circumcenter.z = z0;
    simplex->circumradius = radius;

    for (int i = 0; i < n; i++)
    {
        free(bxMatrix[i]);
        free(byMatrix[i]);
        free(bzMatrix[i]);
        free(aMatrix[i]);
        free(cMatrix[i]);
    }

    free(bxMatrix);
    free(byMatrix);
    free(bzMatrix);
    free(aMatrix);
    free(cMatrix);
#else
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
                bMatrix[j][i][k] = simplex->vertices[i]->point.coords[k];
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
        aMatrix[i][2] = 1;

        cMatrix[i][0] = r[i];
        for (int j = 0; j < NO_DIM; j++)
        {
            aMatrix[i][j + 1] = simplex->vertices[i]->point.coords[j];
        }
    }

    double *b = (double *)malloc(NO_DIM * sizeof(double));
    for (int i = 0; i < NO_DIM; i++)
    {
        b[i] = (i % 2 == 0 ? 1 : -1) * determinant(bMatrix[i], n);
    }
    double a = determinant(aMatrix, n);
    double c = -determinant(cMatrix, n);

    double *coords = (double *)malloc(NO_DIM * sizeof(double));
    for (int i = 0; i < NO_DIM; i++)
    {
        coords[i] = b[i] / (2 * a);
    }

    double square = 0;
    for (int i = 0; i < NO_DIM; i++)
    {
        square = coords[i] * coords[i];
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
#endif
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
#if NO_DIM == 2
    double result = p1.x - p2.x;
    if (result == 0)
        return p1.y - p2.y;
    else
        return result;
#elif NO_DIM == 3
    double result = p1.x - p2.x;
    if (result == 0)
    {
        result = p1.y - p2.y;
        if (result == 0)
            return p1.z - p2.z;
        else
            return result;
    }
    else
        return result;
#else

    for (int i = 0; i < NO_DIM; i++)
    {
        double result = p1.coords[i] - p2.coords[i];
        if (result != 0)
            return result;
    }

    return 0;
#endif
}

double comparePointsVoids(void *p1, void *p2)
{
    PointId *point1 = (PointId *)p1;
    PointId *point2 = (PointId *)p2;
    return comparePoints(point1->point, point2->point);
}

char *printLongSimplex(Simplex *simplex)
{
    int n = 1000;
    char *result = (char*)malloc(n * sizeof(char));

    return result;
}

#if ID == 1
char *printShortSimplex(Simplex *simplex)
{
    int n = 300;
    char *result = (char*)malloc(n * sizeof(char));

    char circumcenter[100];
#if NO_DIM == 2
    sprintf(circumcenter, "x: %10.4f, y: %10.4f", simplex->circumcenter.x, simplex->circumcenter.y);
#elif NO_DIM == 3
    sprintf(circumcenter, "x: %10.4f, y: %10.4f", simplex->circumcenter.x, simplex->circumcenter.y, simplex->circumcenter.z);
#else
    for (int i = 0; i < NO_DIM; i++)
    {
        char temp[20];
        sprintf(temp, ", c%i: %10.4f", i, simplex->circumcenter.coords[i]);
        strcat(circumcenter, temp);
    }
#endif

    sprintf(result, "Simplex: %i, circumcenter: %s, circumradius: %10.4f, hilbertId: %i, hilbertDimension: %i, neighbors: ",
            simplex->id, circumcenter, simplex->circumradius, simplex->hilbertId, simplex->hilbertDimension);

    for(int i = 0; i < NO_DIM; i++)
    {
        char temp[20];
        sprintf(temp, ", n%i: %i", i, simplex->neighbors[i] == NULL?-1:simplex->neighbors[i]->id);
        strcat(result, temp);
    }

    strcat(result, "\n");

    return result;
}
#endif