#include "io.h"
#include <limits.h>
// #include "../DT/serialDT.h"

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
        if (point->point.coords[2] < 600 && point->point.coords[2] > 200)
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

int asciiLoad2(char *filename, Partition *partition)
{
    FILE *fp = fopen(filename, "r+");

    int count = 0;
    int count2 = 0;
    int result = 1;

    double minMaxCoords[NO_DIM][2];

    for (int i = 0; i < NO_DIM; i++)
    {
        minMaxCoords[i][0] = INT_MAX;
        minMaxCoords[i][1] = INT_MIN;
    }

    char c[1000];
    char *temp;
    temp = fgets(c, 1000, fp);
    if (temp != NULL)
        printf("%s", c);
    temp = fgets(c, 1000, fp);
    if (temp != NULL)
        printf("%s", c);
    temp = fgets(c, 1000, fp);
    if (temp != NULL)
        printf("%s", c);

    while (result != EOF)
    {
        double *mess = (double *)malloc(6 * sizeof(double));
        int *messInt = (int *)malloc(2 * sizeof(int));
        PointId *point = newEmptyPointId();
        //result = fscanf(fp, "%lf %lf %lf %lf %lf %lf", &point->point.coords[0], &point->point.coords[1], &point->point.coords[2], &velocity[1], &velocity[2], &velocity[4]);
        result = fscanf(fp, "%i\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%i\t%lf\t%lf\t%lf\t%lf", &messInt[0], &point->point.coords[0], &point->point.coords[1], &point->point.coords[2],
                        &point->velocity[0], &point->velocity[1], &point->velocity[2], &point->mass, &messInt[1], &mess[2], &mess[3], &mess[4], &mess[5]);

        // printf("%lf %lf %lf,\t%lf %lf %lf,\t%f\n", point->point.coords[0], point->point.coords[1], point->point.coords[2], point->velocity[0], point->velocity[1], point->velocity[2], point->mass);

        if (messInt[0] > 0)
        {
            redBlackTreeNode *result = insertIntoRedBlackTree(partition->vertices, point);

            if (result == NULL)
            {
                printf("%i\t%lf %lf %lf,\t%lf %lf %lf,\t%f\n", messInt[0], point->point.coords[0], point->point.coords[1], point->point.coords[2], point->velocity[0], point->velocity[1], point->velocity[2], point->mass);
                printf("Count: %i \n", count);
            }
            else
            {
                count2++;
            }
        }

        // sleep(1);
        count++;

        free(mess);
        free(messInt);

        for (int i = 0; i < NO_DIM; i++)
        {
            if (point->point.coords[i] < minMaxCoords[i][0])
                minMaxCoords[i][0] = point->point.coords[i];
            if (point->point.coords[i] > minMaxCoords[i][1])
                minMaxCoords[i][1] = point->point.coords[i];
        }
    }
    fclose(fp);

    printf("Readed %i lines, choosen %i points\n", count, count2);

    printf("MinMaxs: ");
    for (int i = 0; i < NO_DIM; i++)
    {
        printf("[%i]: %f, %f  ", i, minMaxCoords[i][0], minMaxCoords[i][1]);
    }
    printf("\n");

    return count;
}