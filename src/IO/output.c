#include "IO.h"

int saveDTFormat1(UserOptions *options, Partition *partition)
{
    FILE *fp = fopen(options->DToutputFilename, "w+");

    redBlackTreeDLLNode *pointerTriangle = minimumInRedBlackSubTreeDLL(partition->triangles->first);
    int count = 0;
    while(pointerTriangle != NULL)
    {
        if(pointerTriangle->data == NULL)
        {
            fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: This node in RBTree should have data. \n", (char *)__FILE__, __LINE__);
        }
        else
        {
            count++;
            Simplex *simplex = (Simplex*)pointerTriangle->data;
            // sortPointsInSimplex1(simplex);
            for(int i = 0; i < NO_DIM + 1; i++)
            {
                for(int j = 0; j < NO_DIM; j++)
                {
                    fprintf(fp, "%.10e ", simplex->vertices[i]->point.coords[j]);
                }
            }
            fprintf(fp, "\n");
        }
        pointerTriangle = getNextNodeFromRedBlackTreeDLL(partition->triangles, pointerTriangle);
    }

    fclose(fp);

    return count;
}

int saveDT(UserOptions *options, Partition *partition)
{
    if(options->DToutputFilename == NULL)
        return 0;
    
    switch(options->DToutputFormat)
    {
        case 1:
            return saveDTFormat1(options, partition);
        default:
            return saveDTFormat1(options, partition);
    }
}