#include "blockSizeArray.h"
#include <stdlib.h>

BlockSizeArray *generateBlockSizeArray(BLOCK_TYPE size)
{
    int k = size % BLOCK_SIZE;
    int j = size / BLOCK_SIZE;

    if (k != 0)
        j++;
    else
        k = BLOCK_SIZE;

    BlockSizeArray *result = (BlockSizeArray *)malloc(sizeof(BlockSizeArray));

    result->data = (void ***)malloc(j * sizeof(void **));
    for (int i = 0; i < j - 1; i++)
    {
        result->data[i] = (void **)malloc(BLOCK_SIZE * sizeof(void *));
        for (int l = 0; l < BLOCK_SIZE; l++)
        {
            result->data[i][l] = NULL;
        }
    }
    result->data[j - 1] = (void **)malloc(k * sizeof(void *));
    for (int l = 0; l < k; l++)
    {
        result->data[j - 1][l] = NULL;
    }

    result->numberOfBlocks = j;
    result->sizeOfLastBlock = k;
    result->size = size;

    return result;
}

void *getDataFromBlockSizeArray(BlockSizeArray *array, BLOCK_TYPE i)
{
    int k = i % BLOCK_SIZE;
    int j = i / BLOCK_SIZE;

    if (k >= array->sizeOfLastBlock || j > array->numberOfBlocks)
        return NULL;

    return array->data[j][k];
}

bool putDataToBlockSizeArray(BlockSizeArray *array, BLOCK_TYPE i, void *data)
{
    int k = i % BLOCK_SIZE;
    int j = i / BLOCK_SIZE;

    if (k >= array->sizeOfLastBlock || j > array->numberOfBlocks)
        return false;

    array->data[j][k] = data;

    return true;
}

void removeBlockSizeArray(BlockSizeArray *array, void (*freeData)(void *), bool freeDataBool)
{
    int j = array->numberOfBlocks;
    for (int i = 0; i < j - 1; i++)
    {
        for (int k = 0; k < BLOCK_SIZE; k++)
        {
            if (array->data[i][k] != NULL)
                if (freeDataBool)
                    freeData(array->data[i][k]);
        }
        free(array->data[i]);
    }
    for (int i = 0; i < array->sizeOfLastBlock; i++)
    {
        if (array->data[j - 1][i] != NULL)
            if (freeDataBool)
                freeData(array->data[j - 1][i]);
    }
    free(array->data[j - 1]);
    free(array->data);
    free(array);
}