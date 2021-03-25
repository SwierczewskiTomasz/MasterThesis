#include "io.h"

int asciiLoad(char *filename, Partition *partition)
{
    FILE *fp = fopen(filename, "r+");

    int count = 0;
    int count2 = 0;
    int result = 1;

    printf("1\n");

    while (result != EOF)
    {
        double *velocity = (double *)malloc(4 * sizeof(double));
        PointId *point = newEmptyPointId();
        result = fscanf(fp, "%lf %lf %lf %lf %lf %lf", &point->point.coords[0], &point->point.coords[1], &point->point.coords[2], &velocity[1], &velocity[2], &velocity[4]);
        point->mass = 1;
        if (velocity[0] < 11 * 100000)
        {
            if (point->point.coords[0] != 0 && point->point.coords[1] != 0 && point->point.coords[2] != 0)
                insertIntoRedBlackTree(partition->vertices, point);
            count2++;
        }
        count++;
        // printf("%i, %10.4f, %10.4f, %10.4f\n", count, velocity[0], velocity[1], velocity[2]);
        free(velocity);
    }
    fclose(fp);

    printf("Loaded %i points, choosen %i points\n", count, count2);

    return count;
}