#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "myMath.h"

double determinant(double **data, int n)
{
    // return methodLU(data, n);
    return laplaceExpansion(data, n);
    // return PALUdecomposition(data, n);
}

double LUdecomposition(double **data, int n)
{
    if (n == 1)
    {
        return data[0][0];
    }

    if (n == 2)
    {
        return data[0][0] * data[1][1] - data[0][1] * data[1][0];
    }

    double **L = (double **)malloc(n * sizeof(double *));
    double **U = (double **)malloc(n * sizeof(double *));

    for (int i = 0; i < n; i++)
    {
        L[i] = (double *)malloc(n * sizeof(double));
        U[i] = (double *)malloc(n * sizeof(double));
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            double sum = 0;
            for (int k = 0; k < i; k++)
                sum += (L[i][k] * U[k][j]);

            U[i][j] = data[i][j] - sum;
        }

        for (int j = i; j < n; j++)
        {
            if (i == j)
                L[i][i] = 1;
            else
            {
                double sum = 0;
                for (int k = 0; k < i; k++)
                    sum += (L[j][k] * U[k][i]);

                L[j][i] = (data[j][i] - sum) / U[i][i];
            }
        }
    }

    double det = 1;
    for (int i = 0; i < n; i++)
    {
        det *= U[i][i];
    }

    return det;
}

// PA = LU decomposition
double PALUdecomposition(double **matrix, int n)
{
    // printf("\nPALUdecomposition:\n");
    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < n; j++)
    //     {
    //         printf("%f ", matrix[i][j]);
    //     }
    //     printf("\n");
    // }
    // printf("\n");

    double **data = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++)
    {
        data[i] = (double *)malloc(n * sizeof(double));
        memcpy(data[i], matrix[i], n * sizeof(double));
    }

    double min = pow(2, -1000);
    int degenerade = 0;

    if (n == 1)
    {
        return data[0][0];
    }

    if (n == 2)
    {
        return data[0][0] * data[1][1] - data[0][1] * data[1][0];
    }

    int *P = (int *)malloc((n + 1) * sizeof(int));

    double **L = (double **)malloc(n * sizeof(double *));
    double **U = (double **)malloc(n * sizeof(double *));

    for (int i = 0; i < n; i++)
    {
        L[i] = (double *)malloc(n * sizeof(double));
        U[i] = (double *)malloc(n * sizeof(double));
        P[i] = i;
    }

    P[n] = n;

    for (int i = 0; i < n; i++)
    {
        double maxA = 0.0;
        int imax = i;

        for (int k = i; k < n; k++)
            if (fabs(data[k][i]) > maxA)
            {
                maxA = fabs(data[k][i]);
                imax = k;
            }

        if (maxA < min)
        {
            // printf("Matrix is close to degenerate! \n");
            // printf("%14.4f \n", maxA);
            degenerade = 1;
            break;
        }

        if (imax != i)
        {
            int temp = P[i];
            P[i] = P[imax];
            P[imax] = temp;

            double *tempPtr = data[i];
            data[i] = data[imax];
            data[imax] = tempPtr;

            P[n]++;
        }

        for (int j = i; j < n; j++)
        {
            double sum = 0;
            for (int k = 0; k < i; k++)
                sum += (L[i][k] * U[k][j]);

            U[i][j] = data[i][j] - sum;
        }

        for (int j = i; j < n; j++)
        {
            if (i == j)
                L[i][i] = 1;
            else
            {
                double sum = 0;
                for (int k = 0; k < i; k++)
                    sum += (L[j][k] * U[k][i]);

                L[j][i] = (data[j][i] - sum) / U[i][i];
            }
        }
    }

    double det = 1;
    if (degenerade != 0)
    {
        // printf("\nWe must call laplace Expansion. Matrix:\n");
        // for (int i = 0; i < n; i++)
        // {
        //     for (int j = 0; j < n; j++)
        //     {
        //         printf("%f ", matrix[i][j]);
        //     }
        //     printf("\n");
        // }
        // printf("Uj\n");
        // printMatrix(data, n);
        return laplaceExpansion(matrix, n);
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            det *= U[i][i];
        }
    }
    det = (P[n] - n) % 2 == 0 ? det : -det;
    // printf("PALU det: %f\n", det);

    if (det == 0)
    {
        // printf("det equal to 0, so I compute lamplaceExpansion");
        return laplaceExpansion(matrix, n);
    }
    return det;
}

double laplaceExpansion(double **data, int n)
{
    if (n == 1)
        return data[0][0];

    if (n == 2)
        return data[0][0] * data[1][1] - data[1][0] * data[0][1];

    double **minor = (double **)malloc((n - 1) * sizeof(double *));

    for (int i = 0; i < n - 1; i++)
    {
        minor[i] = (double *)malloc((n - 1) * sizeof(double));
    }

    double det = 0.0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 1; j < n; j++)
        {
            for (int k = 0; k < i; k++)
            {
                minor[j - 1][k] = data[j][k];
            }
            for (int k = i + 1; k < n; k++)
            {
                minor[j - 1][k - 1] = data[j][k];
            }
        }
        // printf("\nA_i0: %f\nMinor:\n", data[0][i]);
        // for (int i = 0; i < n - 1; i++)
        // {
        //     for (int j = 0; j < n - 1; j++)
        //     {
        //         printf("%f ", minor[i][j]);
        //     }
        //     printf("\n");
        // }
        double wsp = i % 2 == 0 ? 1 : -1;
        det += wsp * data[0][i] * laplaceExpansion(minor, n - 1);
    }

    for(int i = 0; i < n - 1; i++)
    {
        free(minor[i]);
    }

    free(minor);

    // printf("det: %f \n", det);
    // printf("\nMatrix:\n");
    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < n; j++)
    //     {
    //         printf("%f ", data[i][j]);
    //     }
    //     printf("\n");
    // }
    return det;
}

void printMatrix(double **data, int n)
{
    printf("Matrix: \n");
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(j != 0)
                printf(", ");
            printf("%10.4f", data[i][j]);
        }
        printf("\n");
    }
}