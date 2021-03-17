#include "DTFE.h"

long long DTFE(Partition *partition)
{
    double det = CayleyMengerDeterminant(partition->triangles->first->data);
    printf("Pole powierzchni: %12.4f\n", det);

    return 0;
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