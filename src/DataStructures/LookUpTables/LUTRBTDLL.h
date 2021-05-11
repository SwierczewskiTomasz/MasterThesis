#ifndef LUTRBTDLL_H
#define LUTRBTDLL_H

#include "../simplex.h"
#include "blockSizeArray.h"
#include "../Trees/redBlackTree.h"
#include "ZCurveLUT.h"

typedef struct LUTRBTDLLNode
{
    enum Colour colour;
    Simplex *data;
    struct LUTRBTDLLNode *parent;
    struct LUTRBTDLLNode *left;
    struct LUTRBTDLLNode *right;
    struct LUTRBTDLLNode *next;
    struct LUTRBTDLLNode *prev;
} LUTRBTDLLNode;

/**
 * Structure to store Delaunay Teselation. It uses BlockSizeArray (Array devided on blocks, it isn't possible to allocate for example 64GB array).
 * It is Look-Up Table using Red Black Tree with Double Linked List properties (in each node we have also information about next and previous node).
 * 
 * It uses Red-Black Tree for fast inserting and deleting. 
 * It uses Double Linked List for fast searching next node in RBT. In traditional RBT to travel across whole tree from first to last,
 * you must to make something between O(n) and O(n log(n)) checks. Sometimes it is too large for me, especially for small trees (n=15, I need around 25-30 checks).
 * It uses LUT to fast location first eligible node. For example RBT can have height h < 2*log_2(n/2 + 1). For n = 2^30 elements it will have height smaller than 58. 
 * Sometimes i need to faster locate data which one or bigger than x and smaller than y. So i need to found first bigger than x and later checking that I am in range.
 * I decided to use LUT for storing first data, which one are eligible. I am ordering by Z-curve order. Beacuse it is space filling curve I can increasing size of LUT. 
 * 
 * Bolow my notes. If this private comment stays in your code for too long, just use Google Translator. 
 * 
 * Przepraszam, jeśli ten komentarz zostanie zbyt długo, ale to robi się na tyle skomplikowana struktura, że muszę zapisać własne myśli.
 * 
 * 1. Dodawanie póki co z wykorzystaniem struktury drzew czerwono czarnych. Tak samo usuwanie.
 * 2. Znajdowanie konkretnego trójkąta - też z wykorzystaniem drzew czerwono czarnych.
 * 3. Znajdowanie pierwszego trójkąta spełniającego dane wymagania - z wykorzystaniem LUT
 * 
 * 
 */
typedef struct LUTRBTDLL
{
    /** 
     * Function to compare one simplex with another.
     * Prefered order: Z-curve id => simplex circumcenter => simplex vertices
     */
    double (*compare)(void *, void *);

    void (*freeData)(void *);

    /** 
     * Target size in bits for one dimension.
     * For example for 3 dimensions and int (64bits) it will have (int)(64/3) = 21 bits. For each dimension will be reserved 21 bits. 
     */
    int targetSize;

    /**
     * Current size in bits for one dimension.
     */
    int currentSize;

    /**
     * Current bit shift in all dimensions. For NO_DIM = 3 it will have 0, 3, 6, ...
     */
    int currentBitShift;

    /** 
     * Current bit shift in one dimension.
     */
    int currentBitShiftOneDimension;
    
    BLOCK_TYPE targetCapacity;
    BLOCK_TYPE currentCapacity;

    LUTRBTDLLNode *first;
    ZCurveLUT *LUT;
    BlockSizeArray *array;
    int count;
} LUTRBTDLL;

/**
 * Function to allocate memory for LUTRBTDLL. 
 * 
 * @return Allocated and generated empty Look-Up Table using Red Black Tree with Double Linked List properties (in each node we have also information about next and previous node).
 */
LUTRBTDLL *generateLUTRBTDLL(int targetCapacityOneDim, double (*compare)(void *, void *));
void divideLUTRBTDLL(LUTRBTDLL *table);
void removeLUTRBTDLL(LUTRBTDLL *table, bool freeData);
void removeLUTRBTDLLNode(void *node, bool freeData);
void removeLUTRBTDLLOnlyNode(void *node);
void removeFromLUTRBTDLL(LUTRBTDLL *table, LUTRBTDLLNode *node, bool freeData);

LUTRBTDLLNode *insertIntoLUTRBTDLL(LUTRBTDLL *table, Simplex *simplex);
LUTRBTDLLNode *getFromLUTRBTDLL(LUTRBTDLL *table, Simplex *simplex);

LUTRBTDLLNode *getFirstOfZCurveIndex(LUTRBTDLL *table, BLOCK_TYPE id);
LUTRBTDLLNode *getNextNodeFromLUTRBTDLL(LUTRBTDLLNode *node);
LUTRBTDLLNode *getPrevNodeFromLUTRBTDLL(LUTRBTDLLNode *node);

#endif