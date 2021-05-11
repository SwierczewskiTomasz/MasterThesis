#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "ZCurveLUT.h"
#include "../../constants.h"

ZCurveLUT *generateZCurveLUT(int size)
{
    ZCurveLUT *result = (ZCurveLUT *)malloc(sizeof(ZCurveLUT));
    result->data = (BLOCK_TYPE **)malloc(NO_DIM * sizeof(BLOCK_TYPE *));

    double logSize = log2(size);
    int bitSize = (int)(log2(size));
    if (fmod(logSize, 1.0) != 0.0)
    {
        bitSize++;
    }

    for (int i = 0; i < NO_DIM; i++)
    {
        result->data[i] = (BLOCK_TYPE *)calloc(size, sizeof(BLOCK_TYPE));
        int currentInc = 1 << i;

        for (int j = 0; j < size; j++)
        {
            int temp = j;
            for (int k = bitSize - 1; k >= 0; k--)
            {
                result->data[i][j] = result->data[i][j] << NO_DIM;
                if (temp >> k == 1)
                {
                    result->data[i][j] += currentInc;
                    temp -= temp >> k << k;
                }
            }
        }
    }

    return result;
}

void printZCurveLUT(ZCurveLUT *LUT, int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            for (int k = 0; k < size; k++)
            {
                printf("%i %i %i: %i \n", i, j, k, getZCurveKey(LUT, 3, i, j, k));
            }
        }
    }
}

BLOCK_TYPE getZCurveKey(ZCurveLUT *LUT, int argc, ...)
{
    BLOCK_TYPE result = 0;

    va_list list;
    va_start(list, argc);
    for(int i = 0; i < argc; i++)
    {
        int j = va_arg(list, int);
        result += LUT->data[i][j];
    }
    va_end(list);

    return result;
}

void removeZCurve(ZCurveLUT *LUT)
{
    for(int i = 0; i < NO_DIM; i++)
    {
        free(LUT->data[i]);
    }
    free(LUT->data);
    free(LUT);
}