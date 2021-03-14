#include "validateResult.h"

void validateResult(Partition *partition)
{
    int count = 0; 
    int count2 = 0;
    redBlackTreeNode *pointer = minimumInRedBlackSubTree(partition->vertices->first);

    while (pointer != NULL)
    {
        PointId *point = (PointId *)pointer->data;
        redBlackTreeDLLNode *pointerTriangle = minimumInRedBlackSubTreeDLL(partition->triangles->first);

        while (pointerTriangle != NULL)
        {
            Simplex *simplex = (Simplex *)pointerTriangle->data;
            double distance = squareOfDistanceFromPointToPoint(point->point, simplex->circumcenter);
            // printf("%10.4f, %10.4f\n", distance, simplex->circumradius * simplex->circumradius);
            if(distance <= simplex->circumradius * simplex->circumradius)
            {
                count2++;
                bool isVertex = false;
                for(int i = 0; i < NO_DIM + 1; i++)
                {
                    if(simplex->vertices[i] == point)
                    {    
                        isVertex = true;
                        break;
                    }
                }

                if(!isVertex)
                {
                    count++;
                    fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: Point is inside other triangle, but isn't in vertices of this triangle. \n", (char *)__FILE__, __LINE__);
                    saveToLogs((char *)__FILE__, __LINE__, "Point: ", printLongPointId, point);
                    saveToLogs((char *)__FILE__, __LINE__, "Simplex: ", printLongSimplex, simplex);
                }
            }

            pointerTriangle = getNextNodeFromRedBlackTreeDLL(partition->triangles, pointerTriangle);
        }

        pointer = getNextNodeFromRedBlackTree(partition->vertices, pointer);
    }

    printf("End of validation. %i number of errors detected.\n", count);
    printf("%i\n", count2);
}