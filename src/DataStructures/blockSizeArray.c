#include "blockSizeArray.h"
#include <stdlib.h>

BlockSizeArray *newBlockSizeArray(long long size)
{
    int k = size % BLOCK_SIZE;
    int j = size / BLOCK_SIZE;

    if(k != 0)
        j++;
    else
        k = BLOCK_SIZE;
    
    BlockSizeArray *result = (BlockSizeArray *)malloc(sizeof(BlockSizeArray));
    
    result->data = (void ***)malloc(j * sizeof(void **));
    for (int i = 0; i < j - 1; i++)
        result->data[i] = (void **)malloc(BLOCK_SIZE * sizeof(void *));
    result->data[j-1] = (void**)malloc(k * sizeof(void*));

    result->numberOfBlocks = j;
    result->sizeOfLastBlock = k;
    result->size = size;
    
    return result;
}

void *getDataFromBlockSizeArray(BlockSizeArray *array, long long i)
{
    int k = i % BLOCK_SIZE;
    int j = i / BLOCK_SIZE;

    if(k >= array->sizeOfLastBlock || j > array->numberOfBlocks)
        return NULL;

    return array->data[j][k];
}

bool putDataToBlockSizeArray(BlockSizeArray *array, long long i, void* data)
{
    int k = i % BLOCK_SIZE;
    int j = i / BLOCK_SIZE;

    if(k >= array->sizeOfLastBlock || j > array->numberOfBlocks)
        return false;

    array->data[j][k] = data;

    return true;
}