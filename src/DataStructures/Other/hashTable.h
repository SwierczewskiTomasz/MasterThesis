#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#define MAX_LOAD_FACTOR 0.7

#include "../Trees/redBlackTree.h"

typedef struct HashTable
{
    int count;
    int size;
    redBlackTree **table;
    int (*hash)(int, int);
} HashTable;

HashTable *newHashTable(int size, int (*hash)(int, int));
bool checkDataInHashTable(HashTable *hashTable, int key, void *data);
void insertIntoHashTable(HashTable *hashTable, int key, void *data);
void removeDataFromHashTable(HashTable *hashTable, int key, void *data);
void removeHashTable(HashTable *hashTable);
int simpleHash(int size, int key);
double compareHashTableIds(void *a, void *b);

#endif