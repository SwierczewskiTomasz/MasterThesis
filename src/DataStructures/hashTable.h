#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#define MAX_LOAD_FACTOR 0.7

#include "../DT/serialDT.h"

typedef struct HashTable
{
    int count;
    int size;
    redBlackTree **table;
    int (*hash)(HashTable *hashTable, int);
} HashTable;

HashTable *newHashTable(int size, int (*hash)(HashTable *hashTable, int));
bool checkDataInHashTable(HashTable *hashTable, int key, void *data);
void putDataToHashTable(HashTable *hashTable, int key, void *data);
void removeDataFromHashTable(HashTable *hashTable, int key, void *data);

int simpleHash(HashTable *hashTable, int key);

#endif