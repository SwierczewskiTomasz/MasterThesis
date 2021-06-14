#include "BlockSizeArray.h"
#include <stdlib.h>

BlockSizeArrayDouble *generateBlockSizeArrayDouble(BLOCK_TYPE size)
{
    int k = size % BLOCK_SIZE;
    int j = size / BLOCK_SIZE;

    if (k != 0)
        j++;
    else
        k = BLOCK_SIZE;

    BlockSizeArrayDouble *result = (BlockSizeArrayDouble *)malloc(sizeof(BlockSizeArrayDouble));

    result->data = (double **)malloc(j * sizeof(double *));
    for (int i = 0; i < j - 1; i++)
    {
        result->data[i] = (double *)calloc(BLOCK_SIZE, sizeof(double));
    }
    result->data[j - 1] = (double *)calloc(k, sizeof(double));

    result->numberOfBlocks = j;
    result->sizeOfLastBlock = k;
    result->size = size;

    return result;
}

double getDataFromBlockSizeArrayDouble(BlockSizeArrayDouble *array, BLOCK_TYPE i)
{
    int k = i % BLOCK_SIZE;
    int j = i / BLOCK_SIZE;

    if (k >= array->sizeOfLastBlock || j > array->numberOfBlocks)
        return 0;

    return array->data[j][k];
}

bool putDataToBlockSizeArrayDouble(BlockSizeArrayDouble *array, BLOCK_TYPE i, double data)
{
    int k = i % BLOCK_SIZE;
    int j = i / BLOCK_SIZE;

    if (k >= array->sizeOfLastBlock || j > array->numberOfBlocks)
        return false;

    array->data[j][k] = data;

    return true;
}

void removeBlockSizeArrayDouble(BlockSizeArrayDouble *array)
{
    int j = array->numberOfBlocks;
    for (int i = 0; i < j - 1; i++)
    {
        free(array->data[i]);
    }
    free(array->data[j - 1]);
    free(array->data);
    free(array);
}