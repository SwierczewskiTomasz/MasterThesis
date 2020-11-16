#include <stdio.h>
#include <stdlib.h>

#if defined(WIND32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <time.h>
#include <Windows.h>
#else
#include <sys/time.h>
#include <unistd.h>
#endif

#include <math.h>
#include "serialDT.h"

long long doubleLinkedListInsertTime = 0;
long long doubleLinkedListInsertTime2 = 0;
long long doubleLinkedListRemoveTime = 0;

long long createPolygonTime = 0;
long long searchingTrianglesToModifyTime = 0;
long long searchingTrianglesToModifyTime2 = 0;
long long createNewTrianglesTime = 0;

long long redBlackTreeInsertTime = 0;
long long redBlackTreeGetTime = 0;
long long redBlackTreeRemoveTime = 0;
long long redBlackTreeNextNodeTime = 0;

int main(int argc, char **argv)
{
    // TIPP();

    int n = 0;
    for(int i = 0; i < 60; i++)
    {
        printf("n: %d\n", n);
        n = generateNextTestNumberOfPoints(n);
    }

    testRedBlackTree();
    testDoubleLinkedList();
    return 0;
}

void TIPP()
{
    // putPointsToPartitions(partitions, points);

    // Set *initialPoints;
    // int k = 10000;
    // chooseRandomlyInitialPoints(partitions, points, initialPoints, k);

    // DelaunayTriangulation *initialMesh;
    Partition *partition = (Partition *)malloc(sizeof(Partition));
    partition->triangles = (DoubleLinkedList *)malloc(sizeof(DoubleLinkedList));
    partition->vertices = (DoubleLinkedList *)malloc(sizeof(DoubleLinkedList));

    int k = 8192;
    int n = k;

    // printf("Generowanie partycji \n");
    generateInitialMesh(partition, k);

    // printf("Obliczanie DT \n");
    // DelaunayTriangulation DT = computeDelaunayTriangulation(partition);
    // printf("partition->vertices->first->prev: %p\n", partition->vertices->first->prev);
    // printf("partition->triangles->first->prev: %p\n", partition->triangles->first->prev);

    struct timeval te;
    gettimeofday(&te, NULL);
    long long time1 = te.tv_sec * 1000000LL + te.tv_usec / 1000;
    computeDelaunayTriangulation(partition, n);
    struct timeval te2;
    gettimeofday(&te2, NULL);
    long long time2 = te2.tv_sec * 1000000LL + te2.tv_usec / 1000;

    printf("%lld\n", time2 - time1);
    // printf("After DT\n");
    printf("doubleLinkedListRemoveTime: %lld\n", doubleLinkedListRemoveTime);
    printf("doubleLinkedListInsertTime: %lld\n", doubleLinkedListInsertTime);
    printf("doubleLinkedListInsertTime2: %lld\n", doubleLinkedListInsertTime2);

    printf("createPolygonTime: %lld\n", createPolygonTime);
    printf("searchingTrianglesToModifyTime: %lld\n", searchingTrianglesToModifyTime);
    printf("searchingTrianglesToModifyTime2: %lld\n", searchingTrianglesToModifyTime2);
    printf("createNewTrianglesTime: %lld\n", createNewTrianglesTime);

    printf("redBlackTreeInsertTime: %lld\n", redBlackTreeInsertTime);
    printf("redBlackTreeGetTime: %lld\n", redBlackTreeGetTime);
    printf("redBlackTreeRemoveTime: %lld\n", redBlackTreeRemoveTime);
    printf("redBlackTreeNextNodeTime: %lld\n", redBlackTreeNextNodeTime);

    FILE *fp;
    fp = fopen("./out/outputVertices.txt", "w+");

    void *pointer = partition->vertices->first;

    while (pointer != NULL)
    {
        PointId *point = (PointId *)getDataFromNode(pointer);
        fprintf(fp, "%f, %f \n", point->point.x, point->point.y);
        pointer = getNextNode(pointer);
    }

    fclose(fp);

    fp = fopen("./out/outputTriangles.txt", "w+");

    pointer = partition->triangles->first;

    while (pointer != NULL)
    {
        // printf("Load next triangle\n");
        Simplex *simplex = (Simplex *)getDataFromNode(pointer);
        // printf("Loaded\n");
        // fprintf(fp, "%f, %f, %f, %f, %f, %f, %f, %f, %f \n", simplex->object.circumcenter.x, simplex->object.circumcenter.y, simplex->object.circumradius, simplex->object.vertices[0].point.x, simplex->object.vertices[0].point.y, simplex->object.vertices[1].point.x, simplex->object.vertices[1].point.y, simplex->object.vertices[2].point.x, simplex->object.vertices[2].point.y);
        fprintf(fp, "%f, %f\n%f, %f\n\n%f, %f\n%f, %f\n\n%f, %f\n%f, %f\n\n",
                simplex->object.vertices[0].point.x, simplex->object.vertices[0].point.y,
                simplex->object.vertices[1].point.x, simplex->object.vertices[1].point.y,
                simplex->object.vertices[1].point.x, simplex->object.vertices[1].point.y,
                simplex->object.vertices[2].point.x, simplex->object.vertices[2].point.y,
                simplex->object.vertices[2].point.x, simplex->object.vertices[2].point.y,
                simplex->object.vertices[0].point.x, simplex->object.vertices[0].point.y);

        pointer = getNextNode(pointer);
        // printf("Moved to next\n");
    }
    // printf("After while \n");
    fclose(fp);
    // printf("File closed \n");
}

void putPointsToPartitions(Set *partitions, Set *points)
{
    fprintf(stderr, "Error in %s line %i: putPointsToPartitions function is not implemented \n", (char *)__FILE__, __LINE__);
}

void chooseRandomlyInitialPoints(Set *partitions, Set *points, Set *initialPoints, int k)
{
    fprintf(stderr, "Error in %s line %i: chooseRandomlyInitialPoints function is not implemented \n", (char *)__FILE__, __LINE__);
}

void generateInitialMesh(Partition *partition, int nParticles)
{
    srand(0);

    // redBlackTree *tree = (redBlackTree *)malloc(sizeof(redBlackTree));
    // tree->compare = comparePositionOfTwoPoints;

    DoubleLinkedListNode *first = (DoubleLinkedListNode *)malloc(sizeof(DoubleLinkedListNode));
    PointId *point1 = (PointId *)malloc(sizeof(PointId));
    PointId *point2 = (PointId *)malloc(sizeof(PointId));
    PointId *point3 = (PointId *)malloc(sizeof(PointId));
    PointId *point4 = (PointId *)malloc(sizeof(PointId));

    point1->point.x = 0;
    point1->point.y = 0;
    point2->point.x = 100;
    point2->point.y = 0;
    point3->point.x = 0;
    point3->point.y = 100;
    point4->point.x = 100;
    point4->point.y = 100;

    // insertIntoDoubleLinkedList(partition->vertices, first, point2, comparePositionOfTwoPoints);
    // insertIntoDoubleLinkedList(partition->vertices, first, point3, comparePositionOfTwoPoints);
    // insertIntoDoubleLinkedList(partition->vertices, first, point4, comparePositionOfTwoPoints);

    PointId *pointFirst = (PointId *)malloc(sizeof(PointId));
    double uniformDistribution2 = 1 - (double)rand() / (double)(RAND_MAX);
    double uniformDistribution3 = 1 - (double)rand() / (double)(RAND_MAX);

    // double R = sqrt(-2 * log(uniformDistribution2));
    // double Theta = 2 * M_PI * uniformDistribution3;

    // double wsp = 10;

    // double x,y;
    // x = wsp * R * cos(Theta) + 50;
    // y = wsp * R * sin(Theta) + 50;

    // double x = R * cos(Theta)/7;
    // double y = R * sin(Theta)/7;

    // x = x*fabs(x)*2+50;
    // y = y*fabs(y)*2+50;

    double x = (double)rand() / (double)(RAND_MAX)*100;
    double y = (double)rand() / (double)(RAND_MAX)*100;

    pointFirst->point.x = x;
    pointFirst->point.y = y;
    partition->vertices->first = first;
    first->data = pointFirst;
    // insertIntoRedBlackTree(tree, pointFirst);
    for (int i = 0; i < nParticles - 1; i++)
    {
        PointId *point = (PointId *)malloc(sizeof(PointId));

        // uniformDistribution2 = 1 - (double)rand() / (double)(RAND_MAX);
        // uniformDistribution3 = 1 - (double)rand() / (double)(RAND_MAX);

        // R = sqrt(-2 * log(uniformDistribution2));
        // Theta = 2 * M_PI * uniformDistribution3;

        // x = wsp * R * cos(Theta) + 50;
        // y = wsp * R * sin(Theta) + 50;

        // x = x*fabs(x)*40+50;
        // y = y*fabs(y)*40+50;

        x = (double)rand() / (double)(RAND_MAX)*100;
        y = (double)rand() / (double)(RAND_MAX)*100;

        point->point.x = x;
        point->point.y = y;
        insertIntoDoubleLinkedList(partition->vertices, first, point, comparePositionOfTwoPoints);
        // insertIntoRedBlackTree(tree, point);
    }

    // Create 2 super triangles
    PointId points[3] = {*point1, *point2, *point3};
    Simplex *result = (Simplex *)malloc(sizeof(Simplex));
    createNewSimplex(result, points);
    DoubleLinkedListNode *firstTriangle = (DoubleLinkedListNode *)malloc(sizeof(DoubleLinkedListNode));
    partition->triangles->first = firstTriangle;
    firstTriangle->data = result;
    firstTriangle->next = NULL;
    firstTriangle->prev = NULL;

    PointId newPoints[3] = {*point2, *point3, *point4};
    Simplex *result2 = (Simplex *)malloc(sizeof(Simplex));
    createNewSimplex(result2, newPoints);
    insertIntoDoubleLinkedList(partition->triangles, firstTriangle, result2, comparePositionOfTwoTriangles);

    // printf("partition->vertices->first->prev: %p\n", partition->vertices->first->prev);
    // printf("partition->triangles->first->prev: %p\n", partition->triangles->first->prev);

    printf("1\n");
    // printf("%p\n", tree->first);

    // printRedBlackTree(tree);

    void *pointer = partition->vertices->first;

    // sleep(3);

    // while (pointer != NULL)
    // {
    //     PointId *point = (PointId *)getDataFromNode(pointer);
    //     redBlackTreeNode *node = getFromRedBlackTree(tree, point);
    //     if (node != NULL)
    //         removeFromRedBlackTree(tree, node);

    //     // printf("Removed point: x: %f, y: %f\n", point->point.x, point->point.y);
    //     pointer = getNextNode(pointer);
    // }

    // printRedBlackTree(tree);
}

double comparePositionOfTwoPoints(void *a, void *b)
{
    PointId *s1 = (PointId *)a;
    PointId *s2 = (PointId *)b;

    return s1->point.x - s2->point.x;
}

void computeDelaunayTriangulation(Partition *partition, int stopAtStep)
{
    int count = partition->vertices->count;
    void *pointer = partition->vertices->first;

    int c = 0;

    while (pointer != NULL)
    {
        c++;
        PointId *point = (PointId *)getDataFromNode(pointer);
        // printf("Inserting point: x: %f, y: %f\n", point->point.x, point->point.y);
        //insertPoint(point, partition);
        newInsertPoint(point, partition);
        // printf("Point inserted: x: %f, y: %f\n", point->point.x, point->point.y);
        pointer = getNextNode(pointer);
        // printf("Next point\n");
        if (c == stopAtStep)
            break;
    }
}

void newInsertPoint(PointId *point, Partition *partition)
{
    int count = partition->triangles->count;
    DoubleLinkedListNode *pointer = partition->triangles->first;
    DoubleLinkedList list;
    DoubleLinkedListNode *current;
    current = list.first;
    list.first = NULL;
    int c = 0;

    struct timeval te1;
    gettimeofday(&te1, NULL);
    long long time1 = te1.tv_sec * 1000000LL + te1.tv_usec / 1000;

    // printf("Inserting point in newInsertPoint\n");

    while (pointer != NULL)
    {

        Simplex *data = (Simplex *)getDataFromNode(pointer);
        double squareDistance = squareOfDistanceFromPointToPoint(data->object.circumcenter, point->point);
        double squareRadius = data->object.circumradius * data->object.circumradius;

        if (squareDistance <= squareRadius)
        {
            struct timeval te3;
            gettimeofday(&te3, NULL);
            long long time3 = te3.tv_sec * 1000000LL + te3.tv_usec / 1000;
            if (c == 0)
            {
                current = (DoubleLinkedListNode *)malloc(sizeof(DoubleLinkedListNode));
                current->data = pointer;
                list.first = current;
                current->next = NULL;
                current->prev = NULL;
            }
            else
            {
                DoubleLinkedListNode *newNode = (DoubleLinkedListNode *)malloc(sizeof(DoubleLinkedListNode));
                newNode->data = pointer;
                current->next = newNode;
                newNode->next = NULL;
                newNode->prev = current;
                current = newNode;
            }
            c++;
            Simplex *result = data;
            // printf("Triangle founded to modify: %f, %f, %f, %f, %f, %f, %f, %f, %f \n", result->object.circumcenter.x, result->object.circumcenter.y, result->object.circumradius, result->object.vertices[0].point.x, result->object.vertices[0].point.y, result->object.vertices[1].point.x, result->object.vertices[1].point.y, result->object.vertices[2].point.x, result->object.vertices[2].point.y);
            struct timeval te4;
            gettimeofday(&te4, NULL);
            long long time4 = te4.tv_sec * 1000000LL + te4.tv_usec / 1000;
            searchingTrianglesToModifyTime2 += time4 - time3;
        }

        pointer = getNextNode(pointer);
    }
    // printf("Searched %d triangles to modify.\n", c);

    struct timeval te2;
    gettimeofday(&te2, NULL);
    long long time2 = te2.tv_sec * 1000000LL + te2.tv_usec / 1000;
    searchingTrianglesToModifyTime += time2 - time1;

    current = list.first;

    PolygonList *edges = (PolygonList *)malloc(sizeof(PolygonList));
    PolygonList *removedEdges = (PolygonList *)malloc(sizeof(PolygonList));

    while (current != NULL)
    {
        DoubleLinkedListNode *fromCurrent = (DoubleLinkedListNode *)getDataFromNode(current);
        Simplex *data = fromCurrent->data;

        Edge *currentEdges[3];
        currentEdges[0] = createNewEdge(data->object.vertices[0], data->object.vertices[1]);
        currentEdges[1] = createNewEdge(data->object.vertices[1], data->object.vertices[2]);
        currentEdges[2] = createNewEdge(data->object.vertices[2], data->object.vertices[0]);

        for (int i = 0; i < 3; i++)
        {
            PolygonLinkedListNode *founded = findInPolygonList(edges, currentEdges[i]);
            if (founded == NULL)
            {
                founded = findInPolygonList(removedEdges, currentEdges[i]);
                if (founded == NULL)
                {
                    insertIntoPolygonList(edges, currentEdges[i]);
                    // printf("Edge inserted to list: P1: %f, %f; P2: %f, %f\n", currentEdges[i]->points[0].point.x, currentEdges[i]->points[0].point.y,
                    //        currentEdges[i]->points[1].point.x, currentEdges[i]->points[1].point.y);
                }
            }
            else
            {
                removeFromPolygonList(edges, founded);
                insertIntoPolygonList(removedEdges, founded->edge);
                // printf("Edge removed: P1: %f, %f; P2: %f, %f\n", currentEdges[i]->points[0].point.x, currentEdges[i]->points[0].point.y,
                //        currentEdges[i]->points[1].point.x, currentEdges[i]->points[1].point.y);
            }
        }
        removeFromDoubleLinkedList(partition->triangles, current->data);
        current = current->next;
    }
    current = list.first;

    struct timeval te3;
    gettimeofday(&te3, NULL);
    long long time3 = te3.tv_sec * 1000000LL + te3.tv_usec / 1000;
    createPolygonTime += time3 - time2;

    PolygonLinkedListNode *currentNode = edges->first;

    while (currentNode != NULL)
    {
        Simplex *result = (Simplex *)malloc(sizeof(Simplex));
        PointId points[3] = {*point, currentNode->edge->points[0], currentNode->edge->points[1]};
        createNewSimplex(result, points);

        insertIntoDoubleLinkedList2(partition->triangles, result, comparePositionOfTwoTriangles);
        // printf("Triangle inserted: %f, %f, %f, %f, %f, %f, %f, %f, %f \n", result->object.circumcenter.x, result->object.circumcenter.y, result->object.circumradius, result->object.vertices[0].point.x, result->object.vertices[0].point.y, result->object.vertices[1].point.x, result->object.vertices[1].point.y, result->object.vertices[2].point.x, result->object.vertices[2].point.y);

        currentNode = currentNode->next;
    }

    struct timeval te4;
    gettimeofday(&te4, NULL);
    long long time4 = te4.tv_sec * 1000000LL + te4.tv_usec / 1000;
    createNewTrianglesTime += time4 - time3;

    // while(current != NULL)
    // {
    //     DoubleLinkedListNode *fromCurrent = (DoubleLinkedListNode*)getDataFromNode(current);
    //     //Simplex *data = (Simplex *)getDataFromNode(current);
    //     Simplex *data = fromCurrent->data;
    //     Simplex *simplex = data;
    //     printf("Triangle to modify: %f, %f, %f, %f, %f, %f, %f, %f, %f \n", simplex->object.circumcenter.x, simplex->object.circumcenter.y, simplex->object.circumradius, simplex->object.vertices[0].point.x, simplex->object.vertices[0].point.y, simplex->object.vertices[1].point.x, simplex->object.vertices[1].point.y, simplex->object.vertices[2].point.x, simplex->object.vertices[2].point.y);

    //     int c1 = 0;
    //     DoubleLinkedListNode *f = partition->triangles->first;
    //     while(f != NULL)
    //     {
    //         c1++;
    //         f = f->next;
    //     }
    //     printf("Jest %d trójkątów w partition->triangles \n", c1);

    //     void *newPointer = removeFromDoubleLinkedList(partition->triangles, current->data);

    //     c1 = 0;
    //     f = partition->triangles->first;
    //     while(f != NULL)
    //     {
    //         c1++;
    //         f = f->next;
    //     }
    //     printf("Jest %d trójkątów w partition->triangles \n", c1);
    //     //void *newPointer = current;
    //     //printf("Triangle removed \n");
    //     PointId *pointsForCombination = (PointId*)malloc((NO_DIM + 2)*sizeof(PointId));
    //     pointsForCombination[0] = *point;
    //     for(int i = 0; i < NO_DIM + 1; i++)
    //     {
    //         pointsForCombination[i + 1] = data->object.vertices[i];
    //     }

    //     // printf("Before combo\n");

    //     Point **combo = combination(pointsForCombination, NO_DIM + 2);

    //     // printf("After combo\n");

    //     for(int i = 0; i < NO_DIM + 1; i++)
    //     {
    //         PointId *points = combo[i];
    //         Simplex *result = (Simplex *)malloc(sizeof(Simplex));
    //         createNewSimplex(result, points);
    //         double squareDistance = squareOfDistanceFromPointToPoint(result->object.circumcenter, data->object.vertices[i].point);
    //         double squareRadius = result->object.circumradius * result->object.circumradius;
    //         if (squareDistance > squareRadius)
    //         {
    //             // newPointer = insertIntoDoubleLinkedList(partition->triangles, newPointer, result, comparePositionOfTwoTriangles);
    //             insertIntoDoubleLinkedList2(partition->triangles, result, comparePositionOfTwoTriangles);
    //             printf("Triangle inserted: %f, %f, %f, %f, %f, %f, %f, %f, %f \n", result->object.circumcenter.x, result->object.circumcenter.y, result->object.circumradius, result->object.vertices[0].point.x, result->object.vertices[0].point.y, result->object.vertices[1].point.x, result->object.vertices[1].point.y, result->object.vertices[2].point.x, result->object.vertices[2].point.y);

    //             // printf("Next triangle inserted \n");
    //         }
    //     }

    //     current = getNextNode(current);
    // }
}

//Taka kombinacja, że pierwszy punkt zawsze musi się znaleźć
PointId **combination(PointId *data, int n)
{
    PointId **result = (PointId **)malloc((n - 1) * sizeof(PointId *));
    for (int i = 0; i < n - 1; i++)
    {
        result[i] = (PointId *)malloc((n - 1) * sizeof(PointId));
        for (int j = 0; j < i + 1; j++)
        {
            result[i][j] = data[j];
        }
        for (int j = i + 2; j < n; j++)
        {
            result[i][j - 1] = data[j];
        }
    }
    return result;
}

void insertPoint(PointId *point, Partition *partition)
{
    int count = partition->triangles->count;
    DoubleLinkedListNode *pointer = partition->triangles->first;

    while (pointer != NULL)
    {
        Simplex *data = (Simplex *)getDataFromNode(pointer);

        Simplex *simplex = data;
        printf("Trying to find good simplex: %f, %f, %f, %f, %f, %f, %f, %f, %f \n", simplex->object.circumcenter.x, simplex->object.circumcenter.y,
               simplex->object.circumradius, simplex->object.vertices[0].point.x, simplex->object.vertices[0].point.y, simplex->object.vertices[1].point.x, simplex->object.vertices[1].point.y, simplex->object.vertices[2].point.x, simplex->object.vertices[2].point.y);

        double squareDistance = squareOfDistanceFromPointToPoint(data->object.circumcenter, point->point);
        double squareRadius = data->object.circumradius * data->object.circumradius;
        if (squareDistance == squareRadius)
        {
            printf("Equal distance and radius\n");

            // Now we have situation, when the inserting point is on circumcircle of triangle (or circumsphere of tetrahedron).
            // In 2D we have one from 3 situations - (I name here the points from triangle A, B and C). 1. New point is between A and B.
            // 2. New point is between B and C. 3. New point is between C and A. I will check this by finding minimal distance to every
            // edge. In 3D we have 4 cases and I will check distance to faces (planes).

            Simplex *result = (Simplex *)malloc(sizeof(Simplex));

#if NO_DIM == 2
            double distanceAB = squareOfDistanceFromPointToLine(point->point, data->object.vertices[0].point, data->object.vertices[1].point);
            double distanceBC = squareOfDistanceFromPointToLine(point->point, data->object.vertices[1].point, data->object.vertices[2].point);
            double distanceCA = squareOfDistanceFromPointToLine(point->point, data->object.vertices[2].point, data->object.vertices[0].point);

            if (distanceAB < distanceBC)
            {
                if (distanceAB < distanceCA)
                {
                    PointId points[3] = {*point, data->object.vertices[0], data->object.vertices[1]};
                    createNewSimplex(result, points);
                }
                else
                {
                    PointId points[3] = {*point, data->object.vertices[0], data->object.vertices[2]};
                    createNewSimplex(result, points);
                }
            }
            else
            {
                PointId points[3] = {*point, data->object.vertices[1], data->object.vertices[2]};
                createNewSimplex(result, points);
            }
#else
            double distanceABC = squareOfDistanceFromPointToPlane(point.point, data->object.vertices[0].point, data->object.vertices[1].point, data->object.vertices[2].point);
            double distanceABD = squareOfDistanceFromPointToPlane(point.point, data->object.vertices[0].point, data->object.vertices[1].point, data->object.vertices[3].point);
            double distanceACD = squareOfDistanceFromPointToPlane(point.point, data->object.vertices[0].point, data->object.vertices[2].point, data->object.vertices[3].point);
            double distanceBCD = squareOfDistanceFromPointToPlane(point.point, data->object.vertices[1].point, data->object.vertices[2].point, data->object.vertices[3].point);

            if (distanceABC < distanceABD)
            {
                if (distanceABC < distanceACD)
                {
                    if (distanceABC < distanceBCD)
                    {
                        PointId points[4] = {point, data->object.vertices[0], data->object.vertices[1], data->object.vertices[2]};
                        result = createNewSimplex(points);
                    }
                    else
                    {
                        PointId points[4] = {point, data->object.vertices[1], data->object.vertices[2], data->object.vertices[3]};
                        result = createNewSimplex(points);
                    }
                }
                else
                {
                    PointId points[4] = {point, data->object.vertices[0], data->object.vertices[2], data->object.vertices[3]};
                    result = createNewSimplex(points);
                }
            }
            else
            {
                PointId points[4] = {point, data->object.vertices[0], data->object.vertices[1], data->object.vertices[3]};
                result = createNewSimplex(points);
            }
#endif
            insertIntoDoubleLinkedList(partition->triangles, pointer, result, comparePositionOfTwoTriangles);
            //return;
        }
        else if (squareDistance < squareRadius)
        {
            printf("Distance smaller than radius\n");
            Simplex *result = (Simplex *)malloc(sizeof(Simplex));

#if NO_DIM == 2
            double distanceAB = squareOfDistanceFromPointToLine(point->point, data->object.vertices[0].point, data->object.vertices[1].point);
            double distanceBC = squareOfDistanceFromPointToLine(point->point, data->object.vertices[1].point, data->object.vertices[2].point);
            double distanceCA = squareOfDistanceFromPointToLine(point->point, data->object.vertices[2].point, data->object.vertices[0].point);

            printf("Point: x: %f, y: %f\n", point->point.x, point->point.y);
            printf("Point[0]: x: %f, y: %f\n", data->object.vertices[0].point.x, data->object.vertices[0].point.y);
            printf("Point[1]: x: %f, y: %f\n", data->object.vertices[1].point.x, data->object.vertices[1].point.y);
            printf("Point[2]: x: %f, y: %f\n", data->object.vertices[2].point.x, data->object.vertices[2].point.y);

            printf("distanceAB: %f\n", distanceAB);
            printf("distanceBC: %f\n", distanceBC);
            printf("distanceCA: %f\n", distanceCA);

            if (distanceAB < distanceBC)
            {
                if (distanceAB < distanceCA)
                {
                    printf("AB\n");
                    PointId points[3] = {*point, data->object.vertices[1], data->object.vertices[2]};
                    createNewSimplex(result, points);

                    printf("Inserting first triangle to Double Linked List:\n");

                    insertIntoDoubleLinkedList(partition->triangles, pointer, result, comparePositionOfTwoTriangles);

                    printf("partition->vertices->first->prev: %p\n", partition->vertices->first->prev);
                    printf("partition->triangles->first->prev: %p\n", partition->triangles->first->prev);

                    PointId modifiedPoints[3] = {*point, data->object.vertices[0], data->object.vertices[2]};

                    printf("partition->vertices->first->prev: %p\n", partition->vertices->first->prev);
                    printf("partition->triangles->first->prev: %p\n", partition->triangles->first->prev);

                    changePointsInSimplex(modifiedPoints, data);

                    printf("partition->vertices->first->prev: %p\n", partition->vertices->first->prev);
                    printf("partition->triangles->first->prev: %p\n", partition->triangles->first->prev);

                    printf("Remove triangle from DoubleLinkedList\n");

                    void *newPointer = removeFromDoubleLinkedList(partition->triangles, pointer);

                    printf("Inserting second triangle to Double Linked List\n");

                    insertIntoDoubleLinkedList(partition->triangles, newPointer, data, comparePositionOfTwoTriangles);

                    printf("Triangles inserted to Double Linked List\n");
                }
                else
                {
                    printf("CA\n");
                    PointId points[3] = {*point, data->object.vertices[1], data->object.vertices[2]};
                    createNewSimplex(result, points);

                    printf("Inserting first triangle to Double Linked List:\n");

                    insertIntoDoubleLinkedList(partition->triangles, pointer, result, comparePositionOfTwoTriangles);

                    printf("partition->vertices->first->prev: %p\n", partition->vertices->first->prev);
                    printf("partition->triangles->first->prev: %p\n", partition->triangles->first->prev);

                    PointId modifiedPoints[3] = {*point, data->object.vertices[0], data->object.vertices[1]};

                    printf("partition->vertices->first->prev: %p\n", partition->vertices->first->prev);
                    printf("partition->triangles->first->prev: %p\n", partition->triangles->first->prev);

                    changePointsInSimplex(modifiedPoints, data);

                    printf("partition->vertices->first->prev: %p\n", partition->vertices->first->prev);
                    printf("partition->triangles->first->prev: %p\n", partition->triangles->first->prev);

                    printf("Remove triangle from DoubleLinkedList\n");

                    void *newPointer = removeFromDoubleLinkedList(partition->triangles, pointer);

                    printf("Inserting second triangle to Double Linked List\n");

                    insertIntoDoubleLinkedList(partition->triangles, newPointer, data, comparePositionOfTwoTriangles);

                    printf("Triangles inserted to Double Linked List\n");
                }
            }
            else
            {
                printf("BC\n");
                PointId points[3] = {*point, data->object.vertices[0], data->object.vertices[2]};
                createNewSimplex(result, points);

                printf("Inserting first triangle to Double Linked List:\n");

                insertIntoDoubleLinkedList(partition->triangles, pointer, result, comparePositionOfTwoTriangles);

                // printf("partition->vertices->first->prev: %p\n", partition->vertices->first->prev);
                // printf("partition->triangles->first->prev: %p\n", partition->triangles->first->prev);

                PointId modifiedPoints[3] = {*point, data->object.vertices[0], data->object.vertices[1]};

                // printf("partition->vertices->first->prev: %p\n", partition->vertices->first->prev);
                // printf("partition->triangles->first->prev: %p\n", partition->triangles->first->prev);

                changePointsInSimplex(modifiedPoints, data);

                // printf("partition->vertices->first->prev: %p\n", partition->vertices->first->prev);
                // printf("partition->triangles->first->prev: %p\n", partition->triangles->first->prev);

                printf("Remove triangle from DoubleLinkedList\n");

                void *newPointer = removeFromDoubleLinkedList(partition->triangles, pointer);

                printf("Inserting second triangle to Double Linked List\n");

                insertIntoDoubleLinkedList(partition->triangles, newPointer, data, comparePositionOfTwoTriangles);

                printf("Triangles inserted to Double Linked List\n");
            }
#else
            // double distanceABC = squareOfDistanceFromPointToPlane(point.point, data->object.vertices[0].point, data->object.vertices[1].point, data->object.vertices[2].point);
            // double distanceABD = squareOfDistanceFromPointToPlane(point.point, data->object.vertices[0].point, data->object.vertices[1].point, data->object.vertices[3].point);
            // double distanceACD = squareOfDistanceFromPointToPlane(point.point, data->object.vertices[0].point, data->object.vertices[2].point, data->object.vertices[3].point);
            // double distanceBCD = squareOfDistanceFromPointToPlane(point.point, data->object.vertices[1].point, data->object.vertices[2].point, data->object.vertices[3].point);

            // if (distanceABC < distanceABD)
            // {
            //     if (distanceABC < distanceACD)
            //     {
            //         if (distanceABC < distanceBCD)
            //         {
            //             PointId points[4] = {point, data->object.vertices[0], data->object.vertices[1], data->object.vertices[2]};
            //             result = createNewSimplex(points);
            //             PointId modifiedPoints[4] = {point, data->object.vertices[0], data->object.vertices[2], data->object.vertices[2]};
            //             changePointsInSimplex(modifiedPoints, pointer);
            //         }
            //         else
            //         {
            //             PointId points[4] = {point, data->object.vertices[1], data->object.vertices[2], data->object.vertices[3]};
            //             result = createNewSimplex(points);
            //             PointId modifiedPoints[4] = {point, data->object.vertices[0], data->object.vertices[2], data->object.vertices[3]};
            //             changePointsInSimplex(modifiedPoints, pointer);
            //         }
            //     }
            //     else
            //     {
            //         PointId points[4] = {point, data->object.vertices[0], data->object.vertices[2], data->object.vertices[3]};
            //         result = createNewSimplex(points);
            //         PointId modifiedPoints[4] = {point, data->object.vertices[0], data->object.vertices[2], data->object.vertices[3]};
            //         changePointsInSimplex(modifiedPoints, pointer);
            //     }
            // }
            // else
            // {
            //     PointId points[4] = {point, data->object.vertices[0], data->object.vertices[1], data->object.vertices[3]};
            //     result = createNewSimplex(points);
            //     PointId modifiedPoints[4] = {point, data->object.vertices[0], data->object.vertices[2], data->object.vertices[3]};
            //     changePointsInSimplex(modifiedPoints, pointer);
            // }

            PointId pointsBCDE[4] = {data->object.vertices[1], data->object.vertices[2], data->object.vertices[3], point};
            PointId pointsACDE[4] = {data->object.vertices[0], data->object.vertices[2], data->object.vertices[3], point};
            PointId pointsABDE[4] = {data->object.vertices[0], data->object.vertices[1], data->object.vertices[3], point};
            PointId pointsABCE[4] = {data->object.vertices[0], data->object.vertices[1], data->object.vertices[2], point};

            double pointAInsideBCDE = pointInsideCircumcircle(data->object.vertices[0].point, pointsBCDE);
            double pointBInsideACDE = pointInsideCircumcircle(data->object.vertices[1].point, pointsACDE);
            double pointCInsideABDE = pointInsideCircumcircle(data->object.vertices[2].point, pointsABDE);
            double pointDInsideABCE = pointInsideCircumcircle(data->object.vertices[3].point, pointsABCE);

            if (pointAInsideBCDE < 0)
            {
                PointId points[4] = pointsBCDE;
                result = createNewSimplex(points);
            }
            else if (pointBInsideACDE < 0)
            {
                PointId points[4] = pointsACDE;
                result = createNewSimplex(points);
            }
            else if (pointCInsideABDE < 0)
            {
                PointId points[4] = pointsABDE;
                result = createNewSimplex(points);
            }
            else if (pointDInsideABCE < 0)
            {
                PointId points[4] = pointsABCE;
                result = createNewSimplex(points);
            }

            if (pointDInsideABCE < 0)
            {
                PointId modifiedPoints[4] = pointsABCE;
                changePointsInSimplex(modifiedPoints, pointer);
            }
            else if (pointCInsideABDE < 0)
            {
                PointId modifiedPoints[4] = pointsABDE;
                changePointsInSimplex(modifiedPoints, pointer);
            }
            else if (pointBInsideACDE < 0)
            {
                PointId modifiedPoints[4] = pointsACDE;
                changePointsInSimplex(modifiedPoints, pointer);
            }
            else if (pointAInsideBCDE < 0)
            {
                PointId modifiedPoints[4] = pointsBCDE;
                changePointsInSimplex(modifiedPoints, pointer);
            }

#endif
            // printf("Inserting first triangle to Double Linked List:\n");
            //insertIntoDoubleLinkedList(partition->triangles, pointer, result, comparePositionOfTwoTriangles);
            // printf("Inserting second triangle to Double Linked List\n");
            // void *newPointer = removeFromDoubleLinkedList(partition->triangles, pointer);
            // insertIntoDoubleLinkedList(partition->triangles, newPointer, pointer, comparePositionOfTwoTriangles);
            // printf("Triangles inserted to Double Linked List\n");
            //return;
        }
        //printf("This isn't this triangle \n");
        pointer = getNextNode(pointer);
    }
}

void createNewSimplex(Simplex *result, PointId points[NO_DIM + 1])
{
    int n = NO_DIM + 1;
    //Trzeba nadać unikanlne id

    memcpy(result->object.vertices, points, (NO_DIM + 1) * sizeof(PointId));
    calculateCircumcircle(result);
    // printf("Created new simplex\n");
}

double pointInsideCircumcircle(Point point, PointId points[NO_DIM + 1])
{
    //If >0, point inside
    Simplex simplex;
    memcpy(simplex.object.vertices, points, (NO_DIM + 1) * sizeof(PointId));

#if NO_DIM == 2
    int n = NO_DIM + 1;

    double r[NO_DIM + 1];
    for (int i = 0; i < n; i++)
    {
        r[i] = simplex.object.vertices[i].point.x * simplex.object.vertices[i].point.x + simplex.object.vertices[i].point.y * simplex.object.vertices[i].point.y;
    }

    double **bxMatrix = (double **)malloc(n * sizeof(double *));
    double **byMatrix = (double **)malloc(n * sizeof(double *));
    double **aMatrix = (double **)malloc(n * sizeof(double *));
    double **cMatrix = (double **)malloc(n * sizeof(double *));

    for (int i = 0; i < n; i++)
    {
        bxMatrix[i] = (double *)malloc(n * sizeof(double));
        byMatrix[i] = (double *)malloc(n * sizeof(double));
        aMatrix[i] = (double *)malloc(n * sizeof(double));
        cMatrix[i] = (double *)malloc(n * sizeof(double));
    }

    for (int i = 0; i < n; i++)
    {
        bxMatrix[i][0] = r[i];
        bxMatrix[i][1] = simplex.object.vertices[i].point.y;
        bxMatrix[i][2] = 1;

        byMatrix[i][0] = r[i];
        byMatrix[i][1] = simplex.object.vertices[i].point.x;
        byMatrix[i][2] = 1;

        aMatrix[i][0] = simplex.object.vertices[i].point.x;
        aMatrix[i][1] = simplex.object.vertices[i].point.y;
        aMatrix[i][2] = 1;

        cMatrix[i][0] = r[i];
        cMatrix[i][1] = simplex.object.vertices[i].point.x;
        cMatrix[i][2] = simplex.object.vertices[i].point.y;
    }

    double bx = -determinant(bxMatrix, n);
    double by = determinant(byMatrix, n);
    double a = determinant(aMatrix, n);
    double c = -determinant(cMatrix, n);

    double x0 = -bx / (2 * a);
    double y0 = -by / (2 * a);

    //Zastanowić się, czy potrzebujemy radius, czy wystarczy nam radius^2. Wtedy jedna operacja sqrt mniej.
    double radius = sqrt(bx * bx + by * by - 4 * a * c) / (2 * abs(a));

    simplex.object.circumcenter.x = x0;
    simplex.object.circumcenter.y = y0;
    simplex.object.circumradius = radius;
#else
    int n = NO_DIM + 1;

    double r[NO_DIM + 1];
    for (int i = 0; i < n; i++)
    {
        r[i] = simplex.object.vertices[i].point.x * simplex.object.vertices[i].point.x + simplex.object.vertices[i].point.y * simplex.object.vertices[i].point.y + simplex.object.vertices[i].point.z * simplex.object.vertices[i].point.z;
    }

    double **bxMatrix = (double **)malloc(n * sizeof(double *));
    double **byMatrix = (double **)malloc(n * sizeof(double *));
    double **bzMatrix = (double **)malloc(n * sizeof(double *));
    double **aMatrix = (double **)malloc(n * sizeof(double *));
    double **cMatrix = (double **)malloc(n * sizeof(double *));

    for (int i = 0; i < n; i++)
    {
        bxMatrix[i] = (double *)malloc(n * sizeof(double));
        byMatrix[i] = (double *)malloc(n * sizeof(double));
        bzMatrix[i] = (double *)malloc(n * sizeof(double));
        aMatrix[i] = (double *)malloc(n * sizeof(double));
        cMatrix[i] = (double *)malloc(n * sizeof(double));
    }

    for (int i = 0; i < n; i++)
    {
        bxMatrix[i][0] = r[i];
        bxMatrix[i][1] = simplex.object.vertices[i].point.y;
        bxMatrix[i][2] = simplex.object.vertices[i].point.z;
        bxMatrix[i][3] = 1;

        byMatrix[i][0] = r[i];
        byMatrix[i][1] = simplex.object.vertices[i].point.x;
        byMatrix[i][2] = simplex.object.vertices[i].point.z;
        byMatrix[i][3] = 1;

        bzMatrix[i][0] = r[i];
        bzMatrix[i][1] = simplex.object.vertices[i].point.x;
        bzMatrix[i][2] = simplex.object.vertices[i].point.y;
        bzMatrix[i][3] = 1;

        aMatrix[i][0] = simplex.object.vertices[i].point.x;
        aMatrix[i][1] = simplex.object.vertices[i].point.y;
        aMatrix[i][2] = simplex.object.vertices[i].point.z;
        aMatrix[i][3] = 1;

        cMatrix[i][0] = r[i];
        cMatrix[i][1] = simplex.object.vertices[i].point.x;
        cMatrix[i][2] = simplex.object.vertices[i].point.y;
        cMatrix[i][3] = simplex.object.vertices[i].point.z;
    }

    double bx = determinant(bxMatrix, n);
    double by = -determinant(byMatrix, n);
    double bz = determinant(bzMatrix, n);
    double a = determinant(aMatrix, n);
    double c = -determinant(cMatrix, n);

    double x0 = bx / (2 * a);
    double y0 = by / (2 * a);
    double z0 = bz / (2 * a);

    double radius = sqrt(bx * bx + by * by + bz * bz - 4 * a * c) / (2 * abs(a));

    simplex.object.circumcenter.x = x0;
    simplex.object.circumcenter.y = y0;
    simplex.object.circumcenter.z = z0;
    simplex.object.circumradius = radius;

    double squareDistance = squareOfDistanceFromPointToPoint(simplex.object.circumcenter, point);
    double squareRadius = simplex.object.circumradius * simplex.object.circumradius;

    return squareRadius - squareDistance;
#endif
}

void calculateCircumcircle(Simplex *simplex)
{
#if NO_DIM == 2
    int n = NO_DIM + 1;

    double r[NO_DIM + 1];
    for (int i = 0; i < n; i++)
    {
        r[i] = simplex->object.vertices[i].point.x * simplex->object.vertices[i].point.x + simplex->object.vertices[i].point.y * simplex->object.vertices[i].point.y;
    }

    double **bxMatrix = (double **)malloc(n * sizeof(double *));
    double **byMatrix = (double **)malloc(n * sizeof(double *));
    double **aMatrix = (double **)malloc(n * sizeof(double *));
    double **cMatrix = (double **)malloc(n * sizeof(double *));

    for (int i = 0; i < n; i++)
    {
        bxMatrix[i] = (double *)malloc(n * sizeof(double));
        byMatrix[i] = (double *)malloc(n * sizeof(double));
        aMatrix[i] = (double *)malloc(n * sizeof(double));
        cMatrix[i] = (double *)malloc(n * sizeof(double));
    }

    for (int i = 0; i < n; i++)
    {
        bxMatrix[i][0] = r[i];
        bxMatrix[i][1] = simplex->object.vertices[i].point.y;
        bxMatrix[i][2] = 1;

        byMatrix[i][0] = r[i];
        byMatrix[i][1] = simplex->object.vertices[i].point.x;
        byMatrix[i][2] = 1;

        aMatrix[i][0] = simplex->object.vertices[i].point.x;
        aMatrix[i][1] = simplex->object.vertices[i].point.y;
        aMatrix[i][2] = 1;

        cMatrix[i][0] = r[i];
        cMatrix[i][1] = simplex->object.vertices[i].point.x;
        cMatrix[i][2] = simplex->object.vertices[i].point.y;
    }

    double bx = -determinant(bxMatrix, n);
    double by = determinant(byMatrix, n);
    double a = determinant(aMatrix, n);
    double c = -determinant(cMatrix, n);

    // printf("Point 1 - x: %f, y: %f \n", simplex->object.vertices[0].point.x, simplex->object.vertices[0].point.y);
    // printf("Point 2 - x: %f, y: %f \n", simplex->object.vertices[1].point.x, simplex->object.vertices[1].point.y);
    // printf("Point 3 - x: %f, y: %f \n", simplex->object.vertices[2].point.x, simplex->object.vertices[2].point.y);
    // printf("r[0]: %f \n", r[0]);
    // printf("r[1]: %f \n", r[1]);
    // printf("r[2]: %f \n\n", r[2]);
    // printf("bx: %f, by: %f, a: %f, c: %f \n", bx, by, a, c);

    // printf("\nbxMatrix:\n");
    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < n; j++)
    //     {
    //         printf("%f ", bxMatrix[i][j]);
    //     }
    //     printf("\n");
    // }

    // printf("\nbyMatrix:\n");
    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < n; j++)
    //     {
    //         printf("%f ", byMatrix[i][j]);
    //     }
    //     printf("\n");
    // }

    // printf("\naMatrix:\n");
    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < n; j++)
    //     {
    //         printf("%f ", aMatrix[i][j]);
    //     }
    //     printf("\n");
    // }

    // printf("\ncMatrix:\n");
    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < n; j++)
    //     {
    //         printf("%f ", cMatrix[i][j]);
    //     }
    //     printf("\n");
    // }

    double x0 = -bx / (2 * a);
    double y0 = -by / (2 * a);

    // printf("x0: %f, y0: %f\n", x0, y0);

    //Zastanowić się, czy potrzebujemy radius, czy wystarczy nam radius^2. Wtedy jedna operacja sqrt mniej.
    double radius = sqrt(bx * bx + by * by - 4 * a * c) / (2 * fabs(a));
    // printf("radius: %f\n", radius);
    double licznik = bx * bx + by * by - 4 * a * c;
    double sqrtLicznik = sqrt(licznik);
    double mianownik = 2 * abs(a);
    //printf("bx: %f, by: %f, a: %f, c: %f, radius: %f, licznik: %f, sqrtLicznik: %f, mianownik: %f \n", bx, by, a, c, radius, licznik, sqrtLicznik, mianownik);

    simplex->object.circumcenter.x = x0;
    simplex->object.circumcenter.y = y0;
    simplex->object.circumradius = radius;

    // printf("End circumcircle\n");
#else
    int n = NO_DIM + 1;

    double r[NO_DIM + 1];
    for (int i = 0; i < n; i++)
    {
        r[i] = simplex.object.vertices[i].point.x * simplex.object.vertices[i].point.x + simplex.object.vertices[i].point.y * simplex.object.vertices[i].point.y + simplex.object.vertices[i].point.z * simplex.object.vertices[i].point.z;
    }

    double **bxMatrix = (double **)malloc(n * sizeof(double *));
    double **byMatrix = (double **)malloc(n * sizeof(double *));
    double **bzMatrix = (double **)malloc(n * sizeof(double *));
    double **aMatrix = (double **)malloc(n * sizeof(double *));
    double **cMatrix = (double **)malloc(n * sizeof(double *));

    for (int i = 0; i < n; i++)
    {
        bxMatrix[i] = (double *)malloc(n * sizeof(double));
        byMatrix[i] = (double *)malloc(n * sizeof(double));
        bzMatrix[i] = (double *)malloc(n * sizeof(double));
        aMatrix[i] = (double *)malloc(n * sizeof(double));
        cMatrix[i] = (double *)malloc(n * sizeof(double));
    }

    for (int i = 0; i < n; i++)
    {
        bxMatrix[i][0] = r[i];
        bxMatrix[i][1] = simplex.object.vertices[i].point.y;
        bxMatrix[i][2] = simplex.object.vertices[i].point.z;
        bxMatrix[i][3] = 1;

        byMatrix[i][0] = r[i];
        byMatrix[i][1] = simplex.object.vertices[i].point.x;
        byMatrix[i][2] = simplex.object.vertices[i].point.z;
        byMatrix[i][3] = 1;

        bzMatrix[i][0] = r[i];
        bzMatrix[i][1] = simplex.object.vertices[i].point.x;
        bzMatrix[i][2] = simplex.object.vertices[i].point.y;
        bzMatrix[i][3] = 1;

        aMatrix[i][0] = simplex.object.vertices[i].point.x;
        aMatrix[i][1] = simplex.object.vertices[i].point.y;
        aMatrix[i][2] = simplex.object.vertices[i].point.z;
        aMatrix[i][3] = 1;

        cMatrix[i][0] = r[i];
        cMatrix[i][1] = simplex.object.vertices[i].point.x;
        cMatrix[i][2] = simplex.object.vertices[i].point.y;
        cMatrix[i][3] = simplex.object.vertices[i].point.z;
    }

    double bx = determinant(bxMatrix, n);
    double by = -determinant(byMatrix, n);
    double bz = determinant(bzMatrix, n);
    double a = determinant(aMatrix, n);
    double c = -determinant(cMatrix, n);

    double x0 = bx / (2 * a);
    double y0 = by / (2 * a);
    double z0 = bz / (2 * a);

    double radius = sqrt(bx * bx + by * by + bz * bz - 4 * a * c) / (2 * abs(a));

    simplex.object.circumcenter.x = x0;
    simplex.object.circumcenter.y = y0;
    simplex.object.circumcenter.z = z0;
    simplex.object.circumradius = radius;
#endif
}

double squareOfDistanceFromPointToLine(Point point, Point point1, Point point2)
{
    double A = point2.y - point1.y;
    double B = point2.x - point1.x;
    double C = point2.x * point1.y - point1.x * point2.y;

    // printf("A: %f, B: %f, C: %f\n", A, B, C);

    double temp = A * point.x + B * point.y + C;
    double squareOfDistance = temp * temp / (A * A + B * B);
    return squareOfDistance;
}

#if NO_DIM == 3
double squareOfDistanceFromPointToPlane(Point point, Point point1, Point point2, Point point3)
{
    int n = NO_DIM + 1;

    Point points[3] = {point1, point2, point3};

    double **aMatrix = (double **)malloc(n * sizeof(double *));
    double **bMatrix = (double **)malloc(n * sizeof(double *));
    double **cMatrix = (double **)malloc(n * sizeof(double *));
    double **dMatrix = (double **)malloc(n * sizeof(double *));

    for (int i = 0; i < n; i++)
    {
        aMatrix[i] = (double *)malloc(n * sizeof(double));
        bMatrix[i] = (double *)malloc(n * sizeof(double));
        cMatrix[i] = (double *)malloc(n * sizeof(double));
        dMatrix[i] = (double *)malloc(n * sizeof(double));
    }

    for (int i = 0; i < n; i++)
    {
        aMatrix[i][0] = 1;
        aMatrix[i][1] = points[i].y;
        aMatrix[i][2] = points[i].z;

        bMatrix[i][0] = points[i].x;
        bMatrix[i][1] = 1;
        bMatrix[i][2] = points[i].z;

        cMatrix[i][0] = points[i].x;
        cMatrix[i][1] = points[i].y;
        cMatrix[i][2] = 1;

        dMatrix[i][0] = points[i].x;
        dMatrix[i][1] = points[i].y;
        dMatrix[i][2] = points[i].z;
    }

    double detA = determinant(aMatrix, n);
    double detB = determinant(bMatrix, n);
    double detC = determinant(cMatrix, n);
    double detD = determinant(dMatrix, n);

    double D = -detD;
    double A = -D / detD * detA;
    double B = -D / detD * detB;
    double C = -D / detD * detC;

    double temp = A * point.x + B * point.y + C * point.z + D;
    double squareOfDistance = temp * temp / (A * A + B * B + C * C);
    return squareOfDistance;
}
#endif

double squareOfDistanceFromPointToPoint(Point point1, Point point2)
{
    double dx = point1.x - point2.x;
    double dy = point1.y - point2.y;
#if NO_DIM == 2
    return dx * dx + dy * dy;
#else
    double dz = point1.z - point2.z;
    return dx * dx + dy * dy + dz * dz;
#endif
}

double comparePositionOfTwoTriangles(void *a, void *b)
{
    // printf("Compare position of two triangles\n");
    Simplex *s1 = (Simplex *)a;
    Simplex *s2 = (Simplex *)b;
    // double r = s2->object.circumcenter.x;
    // printf("Data loaded\n");
    double result = s1->object.circumcenter.x + s1->object.circumradius - (s2->object.circumcenter.x + s2->object.circumradius);
    // printf("Result computed\n");
    return result;
}

void changePointsInSimplex(PointId *points, void *pointer)
{
    Simplex *simplex = (Simplex *)pointer;
    memcpy(simplex->object.vertices, points, (NO_DIM + 1) * sizeof(PointId));

    calculateCircumcircle(simplex);
}

void printRedBlackTree(redBlackTree *tree)
{
    printf("\n\nRed-Black Tree:\n");
    redBlackTreeNode *node = minimumInRedBlackSubTree(tree->first);
    printf("tree->first: %p\n", tree->first);

    while (node != NULL)
    {
        PointId *point = (PointId *)node->data;
        printf("Node: %p, Parent: %p, Left: %p, Right: %p, Colour: %s, x: %f, y: %f\n", node, node->parent, node->left, node->right, node->colour == Red ? "Red" : "Black", point->point.x, point->point.y);
        node = getNextNodeFromRedBlackTree(tree, node);
    }
}