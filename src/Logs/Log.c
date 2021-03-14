#include "Log.h"
#include <stdarg.h>

char *printLongPoint(void *data)
{
    Point *point = (Point *)data;
    int n = NO_DIM * 25;
    char *result = (char *)malloc(n * sizeof(char));

    for (int i = 0; i < NO_DIM; i++)
    {
        char temp[20];
        sprintf(temp, ", c%i: %10.4f", i, point->coords[i]);
        strcat(result, temp);
    }

    return result;
}

char *printLongPointId(void *data)
{
    PointId *point = (PointId *)data;
    int n = NO_DIM * 20 + 40;
    char *result = (char *)malloc(n * sizeof(char));

#if ID == 1
    sprintf(result, "%i", point->id);
#else
    sprintf(result, "%14p", point);
#endif

    for (int i = 0; i < NO_DIM; i++)
    {
        char temp[20];
        sprintf(temp, ", c%i: %10.4f", i, point->point.coords[i]);
        strcat(result, temp);
    }

    return result;
}

char *printLongEdge(void *data)
{
    Edge *edge = (Edge *)data;

    int n = 600;
    char *result = (char *)malloc(n * sizeof(char));

#if ID == 1
    sprintf(result, "Edge: %6i, points: ", edge->id);
#else
    sprintf(result, "Edge: %14p, points: ", edge);
#endif

    for (int i = 0; i < NO_DIM; i++)
    {
        char *temp = printLongPointId(edge->points[i]);
        int length = strlen(temp) + 10;
        char *temp2 = (char *)malloc(length * sizeof(char));
        if (i == 0)
            sprintf(temp2, "p%i: %s", i, temp);
        else
            sprintf(temp2, ", p%i: %s", i, temp);
        strcat(result, temp2);
        free(temp);
        free(temp2);
    }
    
    char temp[300];
    sprintf(temp, ", first: %i, second: %i, secondIndex: %i, neighbors: ", edge->first == NULL ? -1 : edge->first->id, edge->second == NULL? -1 : edge->second->id, edge->secondIndex);
    strcat(result, temp);
    
    for (int i = 0; i < NO_DIM; i++)
    {
        char temp2[20];
#if ID == 1
        if (i == 0)
            sprintf(temp2, "n%i: %6i", i, edge->neighbors[i] == NULL ? -1 : edge->neighbors[i]->id);
        else
            sprintf(temp2, ", n%i: %6i", i, edge->neighbors[i] == NULL ? -1 : edge->neighbors[i]->id);
#else
        if (i == 0)
            sprintf(temp2, "n%i: %14p", i, edge->neighbors[i]);
        else
            sprintf(temp2, ", n%i: %14p", i, edge->neighbors[i]);
#endif
        strcat(result, temp2);
    }

    strcat(result, "\n");

    return result;
}

char *printShortEdge(void *data)
{
    Edge *edge = (Edge *)data;

    int n = 600;
    char *result = (char *)malloc(n * sizeof(char));
    sprintf(result, "Edge: %3i, points: ", edge->id);

    for (int i = 0; i < NO_DIM; i++)
    {
        char temp[10];
        if (i == 0)
            sprintf(temp, "p%i: %3i", i, edge->points[i]->id);
        else
            sprintf(temp, ", p%i: %3i", i, edge->points[i]->id);
        strcat(result, temp);
    }

    char temp[300];
    sprintf(temp, ", first: %3i, second: %3i, secondIndex: %3i, neighbors: ", edge->first == NULL ? -1 : edge->first->id,
            edge->second == NULL ? -1 : edge->second->id, edge->secondIndex);
    strcat(result, temp);

    for (int i = 0; i < NO_DIM; i++)
    {
        char temp2[20];
        if (i == 0)
            sprintf(temp2, "n%i: %3i", i, edge->neighbors[i] == NULL ? -1 : edge->neighbors[i]->id);
        else
            sprintf(temp2, ", n%i: %3i", i, edge->neighbors[i] == NULL ? -1 : edge->neighbors[i]->id);
        strcat(result, temp2);
    }

    strcat(result, "\n");

    return result;
}

char *printLongEdgeOfEdge(void *data)
{
    EdgeOfEdge *edge = (EdgeOfEdge *)data;

    int n = (NO_DIM * 20 + 20) * NO_DIM + 200;
    char *result = (char *)malloc(n * sizeof(char));

    if(data == NULL)
    {
        sprintf(result, "EdgeOfEdge is NULL: %14p\n", edge);
        return result;
    }

#if ID == 1
    sprintf(result, "EdgeOfEdge: %6i, first: %6i, second: %6i ", edge == NULL ? -1 : edge->id, edge->first == NULL ? -1 : edge->first->id, edge->second == NULL ? -1 : edge->second->id);
#else
    sprintf(result, "EdgeOfEdge: %14p, first: %14p, second: %14p ", edge, edge->first, edge->second);
#endif

    for (int i = 0; i < NO_DIM - 1; i++)
    {
        int n = NO_DIM * 20 + 30;
        char *temp = (char *)malloc(n * sizeof(char));
        char *pointIdString = printLongPointId(edge->points[i]);
        if (i == 0)
            sprintf(temp, "p%i: %s", i, pointIdString);
        else
            sprintf(temp, ", p%i: %s", i, pointIdString);
        strcat(result, temp);
        free(pointIdString);
        free(temp);
    }
    strcat(result, "\n");

    return result;
}

char *printShortEdgeOfEdge(void *data)
{
    EdgeOfEdge *edge = (EdgeOfEdge *)data;

    int n = 300;
    char *result = (char *)malloc(n * sizeof(char));
    sprintf(result, "EdgeOfEdge: %i, first: %i, second: %i", edge->id, edge->first == NULL ? -1 : edge->first->id, edge->second == NULL ? -1 : edge->second->id);

    for (int i = 0; i < NO_DIM - 1; i++)
    {
        char temp[10];
        if (i == 0)
            sprintf(temp, "p%i: %i", i, edge->points[i]->id);
        else
            sprintf(temp, ", p%i: %i", i, edge->points[i]->id);
        strcat(result, temp);
    }
    strcat(result, "\n");
    return result;
}

char *printLongSimplex(void *data)
{
    Simplex *simplex = (Simplex *)data;

    int n = NO_DIM * (25 + 20 + 20 + 10 + 25 * (NO_DIM + 1)) + 200;

    char *result = (char *)malloc(n * sizeof(char));

    char *circumcenter = (char *)malloc(25 * NO_DIM * sizeof(char));

    for (int i = 0; i < NO_DIM; i++)
    {
        char *temp = (char *)malloc(25 * sizeof(char));
        if (i == 0)
        {
            sprintf(circumcenter, "c%i: %10.4f", i, simplex->circumcenter.coords[i]);
        }
        else
        {
            sprintf(temp, ", c%i: %10.4f", i, simplex->circumcenter.coords[i]);
            strcat(circumcenter, temp);
        }
        free(temp);
    }

    sprintf(result, "Simplex: %4i, circumcenter: ", simplex->id);
    strcat(result, circumcenter);

    char *result2 = (char *)malloc(n * sizeof(char));
    sprintf(result2, " circumradius: %10.4f, hilbertId: %4i, hilbertDimension: %4i, boxId: ",
            simplex->circumradius, simplex->hilbertId, simplex->hilbertDimension);
    strcat(result, result2);
    free(result2);

    for (int i = 0; i < NO_DIM; i++)
    {
        char *temp = (char *)malloc(20 * sizeof(char));
        if (i == 0)
            sprintf(temp, "%6i", simplex->boxId[i]);
        else
            sprintf(temp, ", %6i", simplex->boxId[i]);
        strcat(result, temp);
        free(temp);
    }

    strcat(result, "\n Neighbors: ");

    for (int i = 0; i < NO_DIM + 1; i++)
    {
        char *temp = (char *)malloc(20 * sizeof(char));
        if (i == 0)
        {
            if (simplex->neighbors[i] == NULL)
            {
                sprintf(temp, "%i:   NULL", i);
            }
            else
            {
                sprintf(temp, "%i: %6i", i, simplex->neighbors[i]->id);
            }
        }
        else
        {
            if (simplex->neighbors[i] == NULL)
            {
                sprintf(temp, ", %i:   NULL", i);
            }
            else
            {
                sprintf(temp, ", %i: %6i", i, simplex->neighbors[i]->id);
            }
        }

        strcat(result, temp);
        free(temp);
    }

    strcat(result, "\n Vertices: ");
    for (int i = 0; i < NO_DIM + 1; i++)
    {
        char *temp = printLongPointId(simplex->vertices[i]);
        char *temp1 = (char *)malloc((10 + strlen(temp)) * sizeof(char));
        if (i == 0)
            sprintf(temp1, "%i: %s", i, temp);
        else
            sprintf(temp1, ", %i: %s", i, temp);
        strcat(result, temp1);
        free(temp);
        free(temp1);
    }

    strcat(result, "\n");

    free(circumcenter);
    return result;
}

char *printShortSimplex(void *data)
{
    Simplex *simplex = (Simplex *)data;

    int n = 500;
    char *result = (char *)malloc(n * sizeof(char));

    char circumcenter[100];
    // #if NO_DIM == 2
    //     sprintf(circumcenter, "x: %10.4f, y: %10.4f", simplex->circumcenter.x, simplex->circumcenter.y);
    // #elif NO_DIM == 3
    //     sprintf(circumcenter, "x: %10.4f, y: %10.4f, z: %10.4f", simplex->circumcenter.x, simplex->circumcenter.y, simplex->circumcenter.z);
    // #else
    for (int i = 0; i < NO_DIM; i++)
    {
        char temp[20];
        sprintf(temp, ", c%i: %10.4f", i, simplex->circumcenter.coords[i]);
        strcat(circumcenter, temp);
    }
    // #endif

#if NO_DIM == 2
    sprintf(result, "Simplex: %i, circumcenter: %s, circumradius: %10.4f, hilbertId: %i, hilbertDimension: %i, boxId: %i, %i, neighbors: ",
            simplex->id, circumcenter, simplex->circumradius, simplex->hilbertId, simplex->hilbertDimension, simplex->boxId[0], simplex->boxId[1]);
#endif

#if NO_DIM == 3
    sprintf(result, "Simplex: %i, circumcenter: %s, circumradius: %10.4f, hilbertId: %i, hilbertDimension: %i, boxId: %i, %i, %i, neighbors: ",
            simplex->id, circumcenter, simplex->circumradius, simplex->hilbertId, simplex->hilbertDimension, simplex->boxId[0], simplex->boxId[1], simplex->boxId[2]);
#endif
    for (int i = 0; i < NO_DIM + 1; i++)
    {
        char temp[20];
        sprintf(temp, ", n%i: %5i", i, simplex->neighbors[i] == NULL ? -1 : simplex->neighbors[i]->id);
        strcat(result, temp);
    }

    strcat(result, " Points: ");
    for (int i = 0; i < NO_DIM + 1; i++)
    {
        char temp[20];
        sprintf(temp, ", p%i: %5i", i, simplex->vertices == NULL ? -1 : simplex->vertices[i]->id);
        strcat(result, temp);
    }

    strcat(result, "\n");

    return result;
}

void saveToLogs(char *file, int line, char *additionalInformation, char *(*printData)(void *), void *data)
{
    printf("File %s, line %i: %s \n", file, line, additionalInformation);
    char *temp = printData(data);
    printf("%s \n", temp);
    free(temp);
}

void saveToLogsWithFormat(char *file, int line, const char *additionalInformationFormat, ...)
{
    printf("File %s, line %i: ", file, line);
    va_list args;
    va_start(args, additionalInformationFormat);
    vprintf(additionalInformationFormat, args);
    va_end(args);
}

void saveToLogsWithFormatWithData(char *file, int line, char *(*printData)(void *), void *data, const char *additionalInformationFormat, ...)
{
    printf("File %s, line %i: ", file, line);
    va_list args;
    va_start(args, additionalInformationFormat);
    vprintf(additionalInformationFormat, args);
    va_end(args);
    char *temp = printData(data);
    printf("%s \n", temp);
    free(temp);
}