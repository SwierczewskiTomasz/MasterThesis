#include <stdlib.h>
#include <stdio.h>
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

int asciiLoad3(char *filename, Partition *partition, UserOptions *options)
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

        // for(int i = 0; i < NO_DIM; i++)
        // {
        //     point->point.coords[i] /= 1024000;
        // }

        if (messInt[0] > 0)
        {
            bool insideGrid = true;

            for (int j = 0; j < NO_DIM; j++)
            {
                if (point->point.coords[j] > options->minMaxCoords[j][1] || point->point.coords[j] < options->minMaxCoords[j][0])
                {
                    insideGrid = false;
                    break;
                }
            }

            redBlackTreeNode *result = NULL;

            if (insideGrid)
            {
                result = insertIntoRedBlackTree(partition->vertices, point);

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

        if (count == 1000)
            break;
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

int asciiLoad2(char *filename, Partition *partition, UserOptions *options)
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

        for (int i = 0; i < NO_DIM; i++)
        {
            point->point.coords[i] /= 1024000;
        }

        if (messInt[0] > 0)
        {
            bool insideGrid = true;

            for (int j = 0; j < NO_DIM; j++)
            {
                if (point->point.coords[j] > options->minMaxCoords[j][1] || point->point.coords[j] < options->minMaxCoords[j][0])
                {
                    insideGrid = false;
                    break;
                }
            }

            redBlackTreeNode *result = NULL;

            if (insideGrid)
            {
                result = insertIntoRedBlackTree(partition->vertices, point);

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

        if(count == 100)
            break;
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

int loadDTFormat1(UserOptions *options, Partition *partition)
{
    int count = 0;
    int result = 1;

    FILE *fp = fopen(options->DTinputFilename, "r+");
    PointId **points = (PointId **)malloc((NO_DIM + 1) * sizeof(PointId *));

    while (result != EOF)
    {
        for (int i = 0; i < NO_DIM + 1; i++)
        {
            points[i] = newEmptyPointId();
        }

        for (int i = 0; i < NO_DIM + 1; i++)
        {
            for (int j = 0; j < NO_DIM; j++)
            {
                result = fscanf(fp, "%le ", &points[i]->point.coords[j]);
                if (result == EOF)
                    break;
            }
            if (result == EOF)
                break;
        }

        if (result == EOF)
            break;

        for (int i = 0; i < NO_DIM + 1; i++)
        {
            redBlackTreeNode *node = getFromRedBlackTree(partition->vertices, points[i]);
            if (node == NULL)
            {
                insertIntoRedBlackTree(partition->vertices, points[i]);
            }
            else
            {
                free(points[i]);
                points[i] = (PointId *)node->data;
            }
        }
        Simplex *newSimplex = (Simplex *)malloc(sizeof(Simplex));

#if REDBLACKTREEDLL == 2
        createNewSimplex(newSimplex, points, options, partition->triangles->LUT);
#else
        createNewSimplex(newSimplex, points, options);
#endif

        // for (int i = 0; i < NO_DIM + 1; i++)
        //     for (int j = 0; j < NO_DIM; j++)
        //         printf("%le ", newSimplex->vertices[i]->point.coords[j]);
        // printf("\n");
        sortPointsInSimplex(newSimplex);
        // for (int i = 0; i < NO_DIM + 1; i++)
        //     for (int j = 0; j < NO_DIM; j++)
        //         printf("%le ", newSimplex->vertices[i]->point.coords[j]);
        // printf("\n");
#if REDBLACKTREEDLL == 1
        insertIntoRedBlackTreeDLL(partition->triangles, newSimplex);
#elif REDBLACKTREEDLL == 2
        insertIntoLUTRBTDLL(partition->triangles, newSimplex);
#else
        insertIntoRedBlackTree(partition->triangles, newSimplex);
#endif

        count++;
    }

    free(points);

    return count;
}

int loadDT(UserOptions *options, Partition *partition)
{
    if (options->DTinputFilename == NULL)
        return 0;

    switch (options->DTinputFormat)
    {
    case 1:
        return loadDTFormat1(options, partition);
    default:
        return loadDTFormat1(options, partition);
    }
}