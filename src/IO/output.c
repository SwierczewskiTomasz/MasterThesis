#include "IO.h"

int saveDTFormat1(UserOptions *options, Partition *partition)
{
    FILE *fp = fopen(options->DToutputFilename, "w+");

#if REDBLACKTREEDLL == 1
    redBlackTreeDLLNode *pointerTriangle = minimumInRedBlackSubTreeDLL(partition->triangles->first);
#elif REDBLACKTREEDLL == 2
    LUTRBTDLLNode *pointerTriangle = getFirstOfZCurveIndex(partition->triangles, 0);
#else
    redBlackTreeNode *pointerTriangle = minimumInRedBlackSubTree(partition->triangles->first);
#endif

    int count = 0;
    while (pointerTriangle != NULL)
    {
        if (pointerTriangle->data == NULL)
        {
            fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: This node in RBTree should have data. \n", (char *)__FILE__, __LINE__);
        }
        else
        {
            count++;
            Simplex *simplex = (Simplex *)pointerTriangle->data;
            // sortPointsInSimplex1(simplex);
            for (int i = 0; i < NO_DIM + 1; i++)
            {
                for (int j = 0; j < NO_DIM; j++)
                {
                    fprintf(fp, "%.10e ", simplex->vertices[i]->point.coords[j]);
                }
            }
            fprintf(fp, "\n");
        }

#if REDBLACKTREEDLL == 1
        pointerTriangle = getNextNodeFromRedBlackTreeDLL(partition->triangles, pointerTriangle);
#elif REDBLACKTREEDLL == 2
        pointerTriangle = getNextNodeFromLUTRBTDLL(pointerTriangle);
#else
        pointerTriangle = getNextNodeFromRedBlackTree(pointerTriangle);
#endif
    }

    fclose(fp);

    return count;
}

int saveDT(UserOptions *options, Partition *partition)
{
    if (options->DToutputFilename == NULL)
        return 0;

    switch (options->DToutputFormat)
    {
    case 1:
        return saveDTFormat1(options, partition);
    default:
        return saveDTFormat1(options, partition);
    }
}

void saveDTFEToTextFile(UserOptions *options, Partition *partition)
{
    FILE *fp;
    fp = fopen(options->outputFilename, "w+");

    // for (int i = 0; i < options->gridSize; i++)
    // {
    //     for (int j = 0; j < options->gridSize; j++)
    //     {
    //         for (int k = 0; k < options->gridSize; k++)
    //         {
    //             fprintf(fp, "%e\n", partition->gridMatrix[i][j][k].density);
    //         }
    //     }
    // }

    int gridMatrixSize = 0;
    if (INTERPOLATED_FIELDS > 0)
        gridMatrixSize = partition->gridMatrix[0]->size;

    for (BLOCK_TYPE j = 0; j < gridMatrixSize; j++)
    {
        for (int i = 0; i < INTERPOLATED_FIELDS; i++)
        {
            double data = getDataFromBlockSizeArrayDouble(partition->gridMatrix[i], j);
            // printf("%f %f %f %e \n", point->coords[0], point->coords[1], point->coords[2], point->density);
            fprintf(fp, "%e", data);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
}

void saveDTFEToBinaryFile(UserOptions *options, Partition *partition)
{
    FILE *fp;
    fp = fopen(options->outputFilename, "wb+");

    // for (int i = 0; i < options->gridSize; i++)
    // {
    //     for (int j = 0; j < options->gridSize; j++)
    //     {
    //         for (int k = 0; k < options->gridSize; k++)
    //         {
    //             float temp = (float)(partition->gridMatrix[i][j][k].density);
    //             fwrite(&temp, sizeof(float), 1, fp);
    //         }
    //     }
    // }

    int gridMatrixSize = 0;
    if (INTERPOLATED_FIELDS > 0)
        gridMatrixSize = partition->gridMatrix[0]->size;

    for (BLOCK_TYPE j = 0; j < gridMatrixSize; j++)
    {
        for (int i = 0; i < INTERPOLATED_FIELDS; i++)
        {
            float temp = (float)getDataFromBlockSizeArrayDouble(partition->gridMatrix[i], j);
            fwrite(&temp, sizeof(float), 1, fp);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
}

// void saveStatisticsToTextFile(UserOptions *options, Partition *partition)
// {
//     FILE *fp;
//     fp = fopen("test_1.txt", "w+");

//     for (int i = 0; i < options->gridSize; i++)
//     {
//         for (int j = 0; j < options->gridSize; j++)
//         {
//             for (int k = 0; k < options->gridSize; k++)
//             {
//                 fprintf(fp, "%i\n", partition->gridMatrix[i][j][k].onList);
//             }
//         }
//     }

//     fclose(fp);

//     fp = fopen("test_2.txt", "w+");

//     for (int i = 0; i < options->gridSize; i++)
//     {
//         for (int j = 0; j < options->gridSize; j++)
//         {
//             for (int k = 0; k < options->gridSize; k++)
//             {
//                 fprintf(fp, "%i\n", partition->gridMatrix[i][j][k].onListNoneZero);
//             }
//         }
//     }

//     fclose(fp);
// }