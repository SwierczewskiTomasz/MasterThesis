#include "Log.h"

char *printLongPoint(Point point)
{
    int n = NO_DIM * 25;
    char *result = (char*)malloc(n * sizeof(char));

    for (int i = 0; i < NO_DIM; i++)
    {
        char temp[20];
        sprintf(temp, ", c%i: %10.4f", i, point.coords[i]);
        strcat(result, temp);
    }

    return result;
}

char *printLongPointId(PointId *point)
{
    int n = NO_DIM * 20 + 40;
    char *result = (char *)malloc(n * sizeof(char));
    sprintf(result, "%14p", point);

    for (int i = 0; i < NO_DIM; i++)
    {
        char temp[20];
        sprintf(temp, ", c%i: %10.4f", i, point->point.coords[i]);
        strcat(result, temp);
    }

    return result;
}

char *printLongEdge(Edge *edge)
{
    int n = 600;
    char *result = (char *)malloc(n * sizeof(char));

    sprintf(result, "Edge: %14p, points: ", edge);

    for (int i = 0; i < NO_DIM; i++)
    {
        char *temp = printLongPointId(edge->points[i]);
        int length = strlen(temp) + 10;
        char *temp2 = (char *)malloc(length * sizeof(char));
        sprintf(temp2, ", p%i: %s", i, temp);
        strcat(result, temp2);
        free(temp);
        free(temp2);
    }

    char *printFirst = printLongSimplex(edge->first);
    char *printSecond = printLongSimplex(edge->second);

    char temp[300];
    sprintf(temp, ", first: %s, second: %s, secondIndex: %i, neighbors: ", printFirst, printSecond, edge->secondIndex);
    strcat(result, temp);

    for (int i = 0; i < NO_DIM; i++)
    {
        char temp2[20];
        sprintf(temp2, ", n%i: %14p", i, edge->neighbors[i]);
        strcat(result, temp2);
    }

    strcat(result, "\n");

    free(printFirst);
    free(printSecond);

    return result;
}

char *printShortEdge(Edge *edge)
{
    int n = 600;
    char *result = (char *)malloc(n * sizeof(char));
    sprintf(result, "Edge: %3i, points: ", edge->id);

    for (int i = 0; i < NO_DIM; i++)
    {
        char temp[10];
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
        sprintf(temp2, ", n%i: %3i", i, edge->neighbors[i] == NULL ? -1 : edge->neighbors[i]->id);
        strcat(result, temp2);
    }

    strcat(result, "\n");

    return result;
}


char *printLongEdgeOfEdge(EdgeOfEdge *edge)
{
    int n = (NO_DIM * 20 + 20) * NO_DIM + 200;
    char *result = (char *)malloc(n * sizeof(char));

    sprintf(result, "EdgeOfEdge: %14p, first: %14p, second: %14p", edge, edge->first, edge->second);
    for (int i = 0; i < NO_DIM; i++)
    {
        int n = NO_DIM * 20 + 30;
        char *temp = (char *)malloc(n * sizeof(char));
        char *pointIdString = printLongPointId(edge->points[i]);
        sprintf(temp, ", p%i: %s", i, pointIdString);
        strcat(result, temp);
        free(pointIdString);
        free(temp);
    }
    strcat(result, "\n");

    return result;
}


char *printShortEdgeOfEdge(EdgeOfEdge *edge)
{
    int n = 300;
    char *result = (char*)malloc(n * sizeof(char));
    sprintf(result, "EdgeOfEdge: %i, first: %i, second: %i", edge->id, edge->first == NULL?-1:edge->first->id, edge->second == NULL?-1:edge->second->id);

    for(int i = 0; i < NO_DIM; i++)
    {
        char temp[10];
        sprintf(temp, ", p%i: %i", i, edge->points[i]->id);
        strcat(result, temp);
    }
    strcat(result, "\n");
    return result;
}

char *printLongSimplex(Simplex *simplex)
{
    int n = NO_DIM * (25 + 20 + 20 + 10 + 25 * (NO_DIM + 1)) + 200;
    printf("PrintLongSimplex n size: %i \n", n);
    char *result = (char *)malloc(n * sizeof(char));

    char *circumcenter = printLongPoint(simplex->circumcenter);

    sprintf(result, "Simplex: %i, circumcenter: %s, circumradius: %10.4f, hilbertId: %i, hilbertDimension: %i, boxId: ",
            simplex->id, circumcenter, simplex->circumradius, simplex->hilbertId, simplex->hilbertDimension);

    for (int i = 0; i < NO_DIM; i++)
    {
        char temp[20];
        sprintf(temp, ", %i", simplex->boxId[i]);
        strcat(result, temp);
    }

    strcat(result, "\n Neighbors: ");

    for (int i = 0; i < NO_DIM; i++)
    {
        char temp[20];
        sprintf(temp, ", %i: %i", i, simplex->neighbors[i]);
        strcat(result, temp);
    }

    strcat(result, "\n Vertices: ");
    for (int i = 0; i < NO_DIM + 1; i++)
    {
        char *temp = printLongPointId(simplex->vertices[i]);
        char *temp1 = (char *)malloc((10 + strlen(temp)) * sizeof(char));
        sprintf(temp1, ", %i: %s", i, temp);
        strcat(result, temp1);
        free(temp);
        free(temp1);
    }

    strcat(result, "\n");

    free(circumcenter);

    return result;
}

char *printShortSimplex(Simplex *simplex)
{
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

void saveToLogs(char* file, int line, char* additionalInformation, char* (*printData)(void *), void* data)
{
    sprintf(stdout, "File %s, line %i: %s \n", file, line, additionalInformation);
    char* temp = printData(data);
    sprintf("%s \n", temp);
    free(temp);
}