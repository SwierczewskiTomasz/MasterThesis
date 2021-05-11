#include <stdlib.h>
#include "hashTable.h"
#include "../simplex.h"

HashTable *newHashTable(int size, int (*hash)(int, int))
{
    HashTable *hashTable = (HashTable *)malloc(sizeof(HashTable));
    hashTable->count = 0;
    hashTable->size = size;
    hashTable->hash = hash;
    hashTable->table = (redBlackTree **)calloc(size, sizeof(redBlackTree *));

    for(int i = 0; i < size; i++)
    {
        if(hashTable->table[i] != NULL)
            printf("%i Error? \n", i);
    }
    return hashTable;
}

bool checkDataInHashTable(HashTable *hashTable, int key, void *data)
{
    int tempKey = hashTable->hash(hashTable->size, key);

    if (hashTable->table[tempKey] == NULL)
    {
        return false;
    }

    redBlackTreeNode *node = getFromRedBlackTree(hashTable->table[tempKey], data);

    if (node == NULL)
    {
        return false;
    }

    return true;
}

void insertIntoHashTable(HashTable *hashTable, int key, void *data)
{
    hashTable->count++;
    int tempKey = hashTable->hash(hashTable->size, key);

    if (hashTable->table[tempKey] == NULL)
    {
        hashTable->table[tempKey] = newRedBlackTree(compareHashTableIds, NULL);
    }

    insertIntoRedBlackTree(hashTable->table[tempKey], data);
}

void removeDataFromHashTable(HashTable *hashTable, int key, void *data)
{
    int tempKey = hashTable->hash(hashTable->size, key);

    if (hashTable->table[tempKey] == NULL)
    {
        return;
    }

    removeFromRedBlackTree(hashTable->table[tempKey], data);
}

void removeHashTable(HashTable *hashTable)
{
    for (int i = 0; i < hashTable->size; i++)
    {
        if (hashTable->table[i] != NULL)
        {
            removeRedBlackTree(hashTable->table[i], false);
        }
    }
    free(hashTable->table);
    free(hashTable);
}

int simpleHash(int size, int key)
{
    return key % size; //(key % size + key & 1019) % size;
}

double compareHashTableIds(void *a, void *b)
{
    Simplex *sA = (Simplex *)a;
    Simplex *sB = (Simplex *)b;

    return sA - sB;
}