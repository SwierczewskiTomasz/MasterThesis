#ifndef BLOCKSIZEARRAY_H
#define BLOCKSIZEARRAY_H

#include <stdbool.h>
#include "../../constants.h"

/**
 * Struct for storing pointers in array with constant sized block. Default block size is 1024 and is precompiled. 
 * array[i][j] return pointer to data, where i is index of first array (depend on size of array) and we get block, j is index inside block and should be beetween 0 and 1023.
 * If in last block number of data is smaller than size of block then will be allocated only necessery memory, no whole block. 
 */
typedef struct BlockSizeArray
{
    BLOCK_TYPE size;
    int numberOfBlocks;
    int sizeOfLastBlock;
    void *** data;
} BlockSizeArray;

BlockSizeArray *generateBlockSizeArray(BLOCK_TYPE size);
void* getDataFromBlockSizeArray(BlockSizeArray *array, BLOCK_TYPE i);
bool putDataToBlockSizeArray(BlockSizeArray *array, BLOCK_TYPE i, void* data);
void removeBlockSizeArray(BlockSizeArray *array, void (*freeData)(void *), bool freeDataBool);

/**
 * Struct for storing doubles in array with constant sized block. Default block size is 1024 and is precompiled. 
 * array[i][j] return double, where i is index of first array (depend on size of array) and we get block, j is index inside block and should be beetween 0 and 1023.
 * If in last block number of data is smaller than size of block then will be allocated only necessery memory, no whole block. 
 */
typedef struct BlockSizeArrayDouble
{
    BLOCK_TYPE size;
    int numberOfBlocks;
    int sizeOfLastBlock;
    double **data;
} BlockSizeArrayDouble;

BlockSizeArrayDouble *generateBlockSizeArrayDouble(BLOCK_TYPE size);
double getDataFromBlockSizeArrayDouble(BlockSizeArrayDouble *array, BLOCK_TYPE i);
bool putDataToBlockSizeArrayDouble(BlockSizeArrayDouble *array, BLOCK_TYPE i, double data);
void removeBlockSizeArrayDouble(BlockSizeArrayDouble *array);

#endif