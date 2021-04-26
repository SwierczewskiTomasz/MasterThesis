#include <stdlib.h>
#include "hashTable.h"

HashTable *newHashTable(int size, int (*hash)(int))
{
    HashTable *hashTable = (HashTable *)malloc(sizeof(HashTable));
    hashTable->count = 0;
    hashTable->size = size;
    hashTable->hash = hash;
    hashTable->table = (redBlackTree **)malloc(size * sizeof(redBlackTree *));
}

bool checkDataInHashTable(HashTable *hashTable, int key, void *data)
{
    int tempKey = hashTable->hash(hashTable, key);

    if (hashTable->table[tempKey] == NULL)
    {
        return false;
    }

    redBlackTreeNode *node = getFromRedBlackTree(hashTable->table, data);
    if (node == NULL)
    {
        return false;
    }

    return true;
}

void putDataToHashTable(HashTable *hashTable, int key, void *data)
{
    int tempKey = hashTable->hash(hashTable, key);

    if (hashTable->table[tempKey] == NULL)
    {
        hashTable->table[tempKey] = newRedBlackTree(comparePointers, NULL);
    }

    insertIntoRedBlackTree(hashTable->table[tempKey], data);
}

void removeDataFromHashTable(HashTable *hashTable, int key, void *data)
{
    int tempKey = hashTable->hash(hashTable, key);

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

int simpleHash(HashTable *hashTable, int key)
{
    return key % hashTable->size;
}