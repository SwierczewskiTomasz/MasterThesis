#include <stdlib.h>
#include "LUTRBTDLL.h"
#include "LUTRBTDLLPriv.h"
#include "../../oneHeaderToRuleThemAll.h"

LUTRBTDLL *generateLUTRBTDLL(int targetCapacityOneDim, double (*compare)(void *, void *))
{
    LUTRBTDLL *result = (LUTRBTDLL *)malloc(sizeof(LUTRBTDLL));

    result->targetCapacity = pow(targetCapacityOneDim, NO_DIM);
    result->targetSize = ceil(log2(targetCapacityOneDim));
    result->currentSize = 1;
    result->currentCapacity = pow(2, NO_DIM);

    result->compare = compare;
    result->freeData = freeSimplex;

    result->count = 0;
    result->currentBitShift = ceil(log2(targetCapacityOneDim)) * NO_DIM - NO_DIM;
    result->currentBitShiftOneDimension = ceil(log2(targetCapacityOneDim)) - 1;

    result->array = generateBlockSizeArray(result->targetCapacity);
    result->first = NULL;
    result->LUT = generateZCurveLUT(targetCapacityOneDim);

    return result;
}

void printLUT(LUTRBTDLL *result)
{
    BLOCK_TYPE i = 0;
    BLOCK_TYPE inc = 1 << result->currentBitShift;

    while (i < result->targetCapacity)
    {
        LUTRBTDLLNode *node = (LUTRBTDLLNode *)getDataFromBlockSizeArray(result->array, i);
        printf("%i: %i \n", i, node == NULL ? -1 : node->data->ZCurveId);
        i += inc;
    }

    printf("\nPrinting from tree: \n");
    LUTRBTDLLNode *pointer = minimumInSubTreeLUTRBTDLL(result->first);
    while (pointer != NULL)
    {
        printf("%i \n", pointer->data->ZCurveId);
        pointer = getNextNodeFromLUTRBTDLL(pointer);
    }

    printf("\n\n");
}

void divideLUTRBTDLL(LUTRBTDLL *result)
{
    // printLUT(result);

    BLOCK_TYPE i = 0;
    BLOCK_TYPE inc = 1 << result->currentBitShift;
    BLOCK_TYPE smallInc = 1 << (result->currentBitShift - NO_DIM);

    while (i < result->targetCapacity)
    {
        BLOCK_TYPE j = i + smallInc;
        while (j < i + inc)
        {
            LUTRBTDLLNode *previous = (LUTRBTDLLNode *)getDataFromBlockSizeArray(result->array, j - smallInc);
            if (previous != NULL)
            {
                Simplex *simplex = previous->data;

                while (simplex->ZCurveId < j)
                {
                    previous = previous->next;
                    if (previous != NULL)
                        simplex = previous->data;
                    else
                    {
                        simplex = NULL;
                        break;
                    }
                }

                if (simplex != NULL)
                {
                    if (simplex->ZCurveId >= j)
                    {
                        putDataToBlockSizeArray(result->array, j, previous);
                    }
                }
            }

            j += smallInc;
        }

        i += inc;
    }

    result->currentBitShift -= NO_DIM;
    result->currentBitShiftOneDimension--;
    result->currentCapacity <<= NO_DIM;
    result->currentSize++;

    // printLUT(result);

    // printf("/n");
}

void removeLUTRBTDLL(LUTRBTDLL *table, bool freeData)
{
    removeBlockSizeArray(table->array, removeLUTRBTDLLOnlyNode, false);
    removeLUTRBTDLLTree(table, freeData);
    free(table);
}

/**
 * Only for private use. It only free memory, doesn't remove node from tree.
 */
void removeLUTRBTDLLNode(void *node, bool freeData)
{
// #warning Skoro to jest do prywatnego użytku, to przenieść do headera priv.
    if (freeData)
        freeSimplex(((LUTRBTDLLNode *)node)->data);
    free(node);
}

void removeLUTRBTDLLOnlyNode(void *node)
{
    if (node != NULL)
        free(node);
}

void removeFromLUTRBTDLL(LUTRBTDLL *table, LUTRBTDLLNode *node, bool freeData)
{
    BLOCK_TYPE id = node->data->ZCurveId >> table->currentBitShift << table->currentBitShift;
    LUTRBTDLLNode *previousNode = getDataFromBlockSizeArray(table->array, id);
    while (previousNode == node)
    {
        putDataToBlockSizeArray(table->array, id, node->next);
        id -= 1 << table->currentBitShift;
        if (id < 0)
            break;
        previousNode = getDataFromBlockSizeArray(table->array, id);
    }

    removeFromLUTRBTDLLTree(table, node);
    // printLUT(table);
}

void compareCounts(LUTRBTDLL *table)
{
    printf("Table->count: %i\n", table->count);
    int count = 0;
    LUTRBTDLLNode *pointer = minimumInSubTreeLUTRBTDLL(table->first);
    while (pointer != NULL)
    {
        count++;
        pointer = getNextNodeFromLUTRBTDLL(pointer);
    }
    printf("From tree: %i\n\n", count);
}

LUTRBTDLLNode *insertIntoLUTRBTDLL(LUTRBTDLL *table, Simplex *simplex)
{
    LUTRBTDLLNode *result = insertIntoLUTRBTDLLAdditional(table, simplex);

    // if(simplex->ZCurveId == 28676)
    // {
    //     printf("to Tutaj!\n");
    // }

    BLOCK_TYPE id = simplex->ZCurveId >> table->currentBitShift << table->currentBitShift;

    // printLUT(table);

    LUTRBTDLLNode *previousNode = getDataFromBlockSizeArray(table->array, id);
    // if (previousNode != NULL)
    //     printf("%p\n", previousNode->data);

    double compare = 0;
    if (previousNode != NULL)
        compare = table->compare(simplex, previousNode->data);

    while (previousNode == NULL || compare < 0)
    {
        putDataToBlockSizeArray(table->array, id, result);
        id -= 1 << table->currentBitShift;
        if (id < 0)
            break;
        previousNode = getDataFromBlockSizeArray(table->array, id);
        if (previousNode != NULL)
            compare = table->compare(simplex, previousNode->data);
    }

    table->count++;
    if (table->count == table->currentCapacity * DIVIDEWHEN)
    {
        printf("\nDividing LUTRBTDLL table. Current capacity: %i, count: %i\n", table->currentCapacity, table->count);
        // compareCounts(table);
        divideLUTRBTDLL(table);
        // compareCounts(table);
    }

    // printLUT(table);

    return result;
}

LUTRBTDLLNode *getFirstOfZCurveIndex(LUTRBTDLL *table, BLOCK_TYPE id)
{
    return getDataFromBlockSizeArray(table->array, id);
}