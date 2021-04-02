#ifndef BLOCKSIZEARRAY_H
#define BLOCKSIZEARRAY_H

#define BLOCK_SIZE 1024

#include <stdbool.h>

/**
 * Struct for storing pointers in array with constant sized block. Default block size is 1024 and is precompiled. 
 * array[i][j] return pointer to data, where i is index of first array (depend on size of array) and we get block, j is index inside block and should be beetween 0 and 1023.
 * If in last block number of data is smaller than size of block then will be allocated only necessery memory, no whole block. 
 */
typedef struct BlockSizeArray
{
    long long size;
    int numberOfBlocks;
    int sizeOfLastBlock;
    void *** data;
} BlockSizeArray;

BlockSizeArray *newBlockSizeArray(long long size);
void* getDataFromBlockSizeArray(BlockSizeArray *array, long long i);
bool putDataToBlockSizeArray(BlockSizeArray *array, long long i, void* data);

#endif