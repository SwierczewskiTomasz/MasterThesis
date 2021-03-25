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
#include "../validateResult.h"

int findInPolygonListCount = 0;

long long redBlackTreeInsertCount = 0;
long long redBlackTreeGetCount = 0;
long long redBlackTreeRemoveCount = 0;
long long redBlackTreeNextNodeCount = 0;
long long redBlackTreePrevNodeCount = 0;

long long redBlackTreeInsertDLLCount = 0;
long long redBlackTreeGetDLLCount = 0;
long long redBlackTreeRemoveDLLCount = 0;
long long redBlackTreeNextNodeDLLCount = 0;
long long redBlackTreePrevNodeDLLCount = 0;

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
long long redBlackTreePrevNodeTime = 0;

long long redBlackTreeInsertDLLTime = 0;
long long redBlackTreeGetDLLTime = 0;
long long redBlackTreeRemoveDLLTime = 0;
long long redBlackTreeNextNodeDLLTime = 0;
long long redBlackTreePrevNodeDLLTime = 0;

long long findFirstSimplexTime = 0;
long long trianglesToModifyTime = 0;
long long findPolygonTime = 0;
long long createTreeOfEdgeOfEdgesTime = 0;
long long uploadInformationsAboutNeighborsInEdgesTime = 0;
long long updateAndAddSimplexesTime = 0;
long long NextNodeAfterAddingTime = 0;

long long TIPP(int k, int n, int hilbertDimension, bool onlyCompute)
{
    // putPointsToPartitions(partitions, points);

    // Set *initialPoints;
    // int k = 10000;
    // chooseRandomlyInitialPoints(partitions, points, initialPoints, k);

    // DelaunayTriangulation *initialMesh;
    Partition *partition = (Partition *)malloc(sizeof(Partition));
    initializePartition(partition);

    // printf("Generowanie partycji \n");
    generateInitialMesh(partition, k, hilbertDimension);

#if DEBUG_TRIANGULATION == 1
    printf("Trójkąty: \n");

    //printRedBlackTreeString(partition->triangles, printShortSimplex);
    printRedBlackTreeString(partition->triangles, printShortSimplex);

    printf("Wierzchołki: \n");

    //printRedBlackTree(partition->vertices);
    printRedBlackTreeString(partition->vertices, printLongPointId);
#endif

    // printf("Obliczanie DT \n\n");
    // DelaunayTriangulation DT = computeDelaunayTriangulation(partition);
    // printf("partition->vertices->first->prev: %14p\n", partition->vertices->first->prev);
    // printf("partition->triangles->first->prev: %14p\n", partition->triangles->first->prev);

    struct timeval te;
    gettimeofday(&te, NULL);
    long long time1 = te.tv_sec * 1000000LL + te.tv_usec;
    computeDelaunayTriangulation(partition, n, hilbertDimension);
    struct timeval te2;
    gettimeofday(&te2, NULL);
    long long time2 = te2.tv_sec * 1000000LL + te2.tv_usec;

    if(onlyCompute)
    {
        printf("%lld\n", time2 - time1);
        return time2 - time1;
    }
    else
    {
        printf("%d, %lld\n", n, time2 - time1);
    }
    // printf("After DT\n");
    // printf("doubleLinkedListRemoveTime: %lld\n", doubleLinkedListRemoveTime);
    // printf("doubleLinkedListInsertTime: %lld\n", doubleLinkedListInsertTime);
    // printf("doubleLinkedListInsertTime2: %lld\n", doubleLinkedListInsertTime2);

    // printf("createPolygonTime: %lld\n", createPolygonTime);
    // printf("searchingTrianglesToModifyTime: %lld\n", searchingTrianglesToModifyTime);
    // printf("searchingTrianglesToModifyTime2: %lld\n", searchingTrianglesToModifyTime2);
    // printf("createNewTrianglesTime: %lld\n", createNewTrianglesTime);

    // printf("redBlackTreeInsertTime: %lld\n", redBlackTreeInsertTime);
    // printf("redBlackTreeGetTime: %lld\n", redBlackTreeGetTime);
    // printf("redBlackTreeRemoveTime: %lld\n", redBlackTreeRemoveTime);
    // printf("redBlackTreeNextNodeTime: %lld\n", redBlackTreeNextNodeTime);

    // printf("redBlackTreeInsertDLLTime: %lld\n", redBlackTreeInsertDLLTime);
    // printf("redBlackTreeGetDLLTime: %lld\n", redBlackTreeGetDLLTime);
    // printf("redBlackTreeRemoveDLLTime: %lld\n", redBlackTreeRemoveDLLTime);
    // printf("redBlackTreeNextNodeDLLTime: %lld\n", redBlackTreeNextNodeDLLTime);

    // printf("findFirstSimplexTime: %lld\n", findFirstSimplexTime);
    // printf("trianglesToModifyTime: %lld\n", trianglesToModifyTime);
    // printf("findPolygonTime: %lld\n", findPolygonTime);
    // printf("createTreeOfEdgeOfEdgesTime: %lld\n", createTreeOfEdgeOfEdgesTime);
    // printf("uploadInformationsAboutNeighborsInEdgesTime: %lld\n", uploadInformationsAboutNeighborsInEdgesTime);
    // printf("updateAndAddSimplexesTime: %lld\n", updateAndAddSimplexesTime);
    // printf("NextNodeAfterAddingTime: %lld\n", NextNodeAfterAddingTime);

    // printf("%lld\n", redBlackTreeInsertTime);
    // printf("%lld\n", redBlackTreeGetTime);
    // printf("%lld\n", redBlackTreeRemoveTime);
    // printf("%lld\n", redBlackTreeNextNodeTime);

    // printf("%lld\n", redBlackTreeInsertDLLTime);
    // printf("%lld\n", redBlackTreeGetDLLTime);
    // printf("%lld\n", redBlackTreeRemoveDLLTime);
    // printf("%lld\n", redBlackTreeNextNodeDLLTime);

    // printf("%lld\n", findFirstSimplexTime);
    // printf("%lld\n", trianglesToModifyTime);
    // printf("%lld\n", findPolygonTime);
    // printf("%lld\n", createTreeOfEdgeOfEdgesTime);
    // printf("%lld\n", uploadInformationsAboutNeighborsInEdgesTime);
    // printf("%lld\n", updateAndAddSimplexesTime);
    // printf("%lld\n", NextNodeAfterAddingTime);

    printf("Counts: \n");
    printf("%i\n", findInPolygonListCount);
    printf("%lld\n", redBlackTreeInsertCount);
    printf("%lld\n", redBlackTreeGetCount);
    printf("%lld\n", redBlackTreeRemoveCount);
    printf("%lld\n", redBlackTreeNextNodeCount);

    printf("%lld\n", redBlackTreeInsertDLLCount);
    printf("%lld\n", redBlackTreeGetDLLCount);
    printf("%lld\n", redBlackTreeRemoveDLLCount);
    printf("%lld\n", redBlackTreeNextNodeDLLCount);

    FILE *fp;
    fp = fopen("./out/outputVertices2.txt", "w+");

    //void *pointer = partition->vertices->first;
    redBlackTreeNode *pointer = minimumInRedBlackSubTree(partition->vertices->first);

    while (pointer != NULL)
    {
        PointId *point = (PointId *)pointer->data;
        fprintf(fp, "%10.4f, %10.4f \n", point->point.x, point->point.y);
        pointer = getNextNodeFromRedBlackTree(partition->vertices, pointer);
    }

    fclose(fp);

    fp = fopen("./out/outputTriangles2.txt", "w+");

#if REDBLACKTREEDLL == 1
    redBlackTreeDLLNode *pointerTriangle = minimumInRedBlackSubTreeDLL(partition->triangles->first);
#else
    redBlackTreeNode *pointerTriangle = minimumInRedBlackSubTree(partition->triangles->first);
#endif

    while (pointerTriangle != NULL)
    {
        // printf("Load next triangle\n");
        Simplex *simplex = (Simplex *)pointerTriangle->data;
        // printf("Loaded\n");
        // fprintf(fp, "%10.4f, %10.4f, %10.4f, %10.4f, %10.4f, %10.4f, %10.4f, %10.4f, %10.4f \n", simplex->circumcenter.x, simplex->circumcenter.y, simplex->circumradius, simplex->vertices[0]->point.x, simplex->vertices[0]->point.y, simplex->vertices[1]->point.x, simplex->vertices[1]->point.y, simplex->vertices[2]->point.x, simplex->vertices[2]->point.y);
#if NO_DIM == 2
        fprintf(fp, "%10.4f, %10.4f\n%10.4f, %10.4f\n\n%10.4f, %10.4f\n%10.4f, %10.4f\n\n%10.4f, %10.4f\n%10.4f, %10.4f\n\n",
                simplex->vertices[0]->point.x, simplex->vertices[0]->point.y,
                simplex->vertices[1]->point.x, simplex->vertices[1]->point.y,
                simplex->vertices[1]->point.x, simplex->vertices[1]->point.y,
                simplex->vertices[2]->point.x, simplex->vertices[2]->point.y,
                simplex->vertices[2]->point.x, simplex->vertices[2]->point.y,
                simplex->vertices[0]->point.x, simplex->vertices[0]->point.y);
#elif NO_DIM == 3
        int r = rand() % 200;
        int g = rand() % 200;
        int b = rand() % 200;

        double e = (double)rand() / (double)RAND_MAX * 0;

        // if (!(simplex->vertices[0]->id < 8 || simplex->vertices[1]->id < 8 || simplex->vertices[2]->id < 8 || simplex->vertices[3]->id < 8))
        // {
        fprintf(fp, "%10.4f, %10.4f, %10.4f, %i, %i, %i\n%10.4f, %10.4f, %10.4f, %i, %i, %i\n\n%10.4f, %10.4f, %10.4f, %i, %i, %i\n%10.4f, %10.4f, %10.4f, %i, %i, %i\n\n%10.4f, %10.4f, %10.4f, %i, %i, %i\n%10.4f, %10.4f, %10.4f, %i, %i, %i\n\n",
                simplex->vertices[0]->point.x + e, simplex->vertices[0]->point.y + e, simplex->vertices[0]->point.z + e, r, g, b,
                simplex->vertices[1]->point.x + e, simplex->vertices[1]->point.y + e, simplex->vertices[1]->point.z + e, r, g, b,
                simplex->vertices[1]->point.x + e, simplex->vertices[1]->point.y + e, simplex->vertices[1]->point.z + e, r, g, b,
                simplex->vertices[2]->point.x + e, simplex->vertices[2]->point.y + e, simplex->vertices[2]->point.z + e, r, g, b,
                simplex->vertices[2]->point.x + e, simplex->vertices[2]->point.y + e, simplex->vertices[2]->point.z + e, r, g, b,
                simplex->vertices[0]->point.x + e, simplex->vertices[0]->point.y + e, simplex->vertices[0]->point.z + e, r, g, b);

        fprintf(fp, "%10.4f, %10.4f, %10.4f, %i, %i, %i\n%10.4f, %10.4f, %10.4f, %i, %i, %i\n\n%10.4f, %10.4f, %10.4f, %i, %i, %i\n%10.4f, %10.4f, %10.4f, %i, %i, %i\n\n%10.4f, %10.4f, %10.4f, %i, %i, %i\n%10.4f, %10.4f, %10.4f, %i, %i, %i\n\n\n",
                simplex->vertices[0]->point.x + e, simplex->vertices[0]->point.y + e, simplex->vertices[0]->point.z + e, r, g, b,
                simplex->vertices[3]->point.x + e, simplex->vertices[3]->point.y + e, simplex->vertices[3]->point.z + e, r, g, b,
                simplex->vertices[1]->point.x + e, simplex->vertices[1]->point.y + e, simplex->vertices[1]->point.z + e, r, g, b,
                simplex->vertices[3]->point.x + e, simplex->vertices[3]->point.y + e, simplex->vertices[3]->point.z + e, r, g, b,
                simplex->vertices[2]->point.x + e, simplex->vertices[2]->point.y + e, simplex->vertices[2]->point.z + e, r, g, b,
                simplex->vertices[3]->point.x + e, simplex->vertices[3]->point.y + e, simplex->vertices[3]->point.z + e, r, g, b);
        // }
#endif
#if REDBLACKTREEDLL == 1
        pointerTriangle = getNextNodeFromRedBlackTreeDLL(partition->triangles, pointerTriangle);
#else
        pointerTriangle = getNextNodeFromRedBlackTree(partition->triangles, pointerTriangle);
#endif
    }

    fclose(fp);

#if VALIDATE_RESULT == 1
    validateResult(partition);
#endif

    freePartition(partition);
    free(partition);

    return time2 - time1;
}

void initializePartition(Partition *partition)
{
    partition->vertices = newRedBlackTree(comparePointsVoids, free);
    partition->globalVertices = newRedBlackTree(comparePointsVoids, free);
#if REDBLACKTREEDLL == 1
    partition->triangles = newRedBlackTreeDLL(comparePositionOfTwoTrianglesBox, freeSimplex);
#else
    partition->triangles = newRedBlackTree(comparePositionOfTwoTrianglesBox, freeSimplex);
#endif
}

void freePartition(Partition *partition)
{
    removeRedBlackTree(partition->vertices, true);
    removeRedBlackTree(partition->globalVertices, true);
#if REDBLACKTREEDLL == 1
    removeRedBlackTreeDLL(partition->triangles, true);
#else
    removeRedBlackTree(partition->triangles, true);
#endif
}

void putPointsToPartitions(Set *partitions, Set *points)
{
    fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: putPointsToPartitions function is not implemented \n", (char *)__FILE__, __LINE__);
}

void chooseRandomlyInitialPoints(Set *partitions, Set *points, Set *initialPoints, int k)
{
    fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: chooseRandomlyInitialPoints function is not implemented \n", (char *)__FILE__, __LINE__);
}

void generateInitialMesh(Partition *partition, int nParticles, int hilbertDimension)
{
    srand(0);

    supertriangles(partition, hilbertDimension);

    // redBlackTree *tree = (redBlackTree *)malloc(sizeof(redBlackTree));
    // tree->compare = comparePositionOfTwoPoints;

    // DoubleLinkedListNode *first = (DoubleLinkedListNode *)malloc(sizeof(DoubleLinkedListNode));
    // PointId *point1 = (PointId *)malloc(sizeof(PointId));
    // PointId *point2 = (PointId *)malloc(sizeof(PointId));
    // PointId *point3 = (PointId *)malloc(sizeof(PointId));
    // PointId *point4 = (PointId *)malloc(sizeof(PointId));

    // point1->point.x = 0;
    // point1->point.y = 0;
    // point2->point.x = 100;
    // point2->point.y = 0;
    // point3->point.x = 0;
    // point3->point.y = 100;
    // point4->point.x = 100;
    // point4->point.y = 100;

    if (nParticles == 0)
        return;

    // insertIntoDoubleLinkedList(partition->vertices, first, point2, comparePositionOfTwoPoints);
    // insertIntoDoubleLinkedList(partition->vertices, first, point3, comparePositionOfTwoPoints);
    // insertIntoDoubleLinkedList(partition->vertices, first, point4, comparePositionOfTwoPoints);

    PointId *pointFirst; // = (PointId *)malloc(sizeof(PointId));
    // double uniformDistribution2 = 1 - (double)rand() / (double)(RAND_MAX);
    // double uniformDistribution3 = 1 - (double)rand() / (double)(RAND_MAX);

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

    // double x = (double)rand() / (double)(RAND_MAX)*100;
    // double y = (double)rand() / (double)(RAND_MAX)*100;

    // pointFirst->point.x = x;
    // pointFirst->point.y = y;

    FLOATING_POINT_PRECISION coords[NO_DIM];
    for (int i = 0; i < NO_DIM; i++)
    {
        coords[i] = (double)rand() / (double)(RAND_MAX)*100;
    }

#if NO_DIM == 2
    pointFirst = newPointId(coords[0], coords[1]);
#elif NO_DIM == 3
    pointFirst = newPointId(coords[0], coords[1], coords[2]);
#else
    pointFirst = newPointId(coords);
#endif

    insertIntoRedBlackTree(partition->vertices, pointFirst);

    for (int i = 0; i < nParticles - 1; i++)
    {
        PointId *point;

        // uniformDistribution2 = 1 - (double)rand() / (double)(RAND_MAX);
        // uniformDistribution3 = 1 - (double)rand() / (double)(RAND_MAX);

        // R = sqrt(-2 * log(uniformDistribution2));
        // Theta = 2 * M_PI * uniformDistribution3;

        // x = wsp * R * cos(Theta) + 50;
        // y = wsp * R * sin(Theta) + 50;

        // x = x*fabs(x)*40+50;
        // y = y*fabs(y)*40+50;

        for (int i = 0; i < NO_DIM; i++)
        {
            coords[i] = (double)rand() / (double)(RAND_MAX)*100;
        }

#if NO_DIM == 2
        point = newPointId(coords[0], coords[1]);
#elif NO_DIM == 3
        point = newPointId(coords[0], coords[1], coords[2]);
#else
        point = newPointId(coords);
#endif

        // insertIntoDoubleLinkedList(partition->vertices, first, point, comparePositionOfTwoPoints);
        insertIntoRedBlackTree(partition->vertices, point);
    }

    // Create 2 super triangles
    // PointId points[3] = {*point1, *point2, *point3};
    // Simplex *result = (Simplex *)malloc(sizeof(Simplex));
    // createNewSimplex(result, points);
    // DoubleLinkedListNode *firstTriangle = (DoubleLinkedListNode *)malloc(sizeof(DoubleLinkedListNode));
    // partition->triangles->first = firstTriangle;
    // firstTriangle->data = result;
    // firstTriangle->next = NULL;
    // firstTriangle->prev = NULL;

    // PointId newPoints[3] = {*point2, *point3, *point4};
    // Simplex *result2 = (Simplex *)malloc(sizeof(Simplex));
    // createNewSimplex(result2, newPoints);
    // insertIntoDoubleLinkedList(partition->triangles, firstTriangle, result2, comparePositionOfTwoTriangles);

    // printf("partition->vertices->first->prev: %14p\n", partition->vertices->first->prev);
    // printf("partition->triangles->first->prev: %14p\n", partition->triangles->first->prev);

    // printf("1\n");
    // printf("%14p\n", tree->first);

    // printRedBlackTree(tree);

    // void *pointer = partition->vertices->first;

    // sleep(3);

    // while (pointer != NULL)
    // {
    //     PointId *point = (PointId *)getDataFromNode(pointer);
    //     redBlackTreeNode *node = getFromRedBlackTree(tree, point);
    //     if (node != NULL)
    //         removeFromRedBlackTree(tree, node);

    //     // printf("Removed point: x: %10.4f, y: %10.4f\n", point->point.x, point->point.y);
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

void computeDelaunayTriangulation(Partition *partition, int stopAtStep, int hilbertDimension)
{
    // int count = partition->vertices->count;
    redBlackTreeNode *pointer = minimumInRedBlackSubTree(partition->vertices->first);

    int c = 0;

    while (pointer != NULL)
    {
        c++;
        PointId *point = (PointId *)pointer->data;

        //PointId *point = (PointId *)getDataFromNode(pointer);
        // printf("Inserting point: x: %10.4f, y: %10.4f\n", point->point.x, point->point.y);
        //insertPoint(point, partition);
        // newInsertPoint(point, partition);
        theMostNewInsertPoint(point, partition, hilbertDimension);

        // printf("Point inserted: x: %10.4f, y: %10.4f\n", point->point.x, point->point.y);
        //pointer = getNextNode(pointer);

#if MEASURE_TIME == 1
        struct timeval start;
        gettimeofday(&start, NULL);
        long long startTime = start.tv_sec * 1000000LL + start.tv_usec;
#endif

        pointer = getNextNodeFromRedBlackTree(partition->vertices, pointer);

#if MEASURE_TIME == 1
        struct timeval end;
        gettimeofday(&end, NULL);
        long long endTime = end.tv_sec * 1000000LL + end.tv_usec;
        NextNodeAfterAddingTime += endTime - startTime;
#endif

        // printf("Next point\n");
        if (c == stopAtStep)
            break;
    }
}

void theMostNewInsertPoint(PointId *point, Partition *partition, int hilbertDimension)
{

#if DEBUG_TRIANGULATION == 1
    printf("File %s, line %i: theMostNewInsertPoint function.\n", (char *)__FILE__, __LINE__);
    printf("theMostNewInsertPoint function, %s \n\n", printLongPointId(point));
#endif

#if MEASURE_TIME == 1
    struct timeval start;
    gettimeofday(&start, NULL);
    long long startTime = start.tv_sec * 1000000LL + start.tv_usec;
#endif

    Simplex *simplex = findFirstSimplexToModifyBoxId2(point, partition, hilbertDimension);

#if MEASURE_TIME == 1
    struct timeval end;
    gettimeofday(&end, NULL);
    long long endTime = end.tv_sec * 1000000LL + end.tv_usec;
    findFirstSimplexTime += endTime - startTime;
#endif

    if (simplex == NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: Something very weird - We didn't found simplex to modify. \n\n", (char *)__FILE__, __LINE__);
        return;
    }

#if DEBUG_TRIANGULATION == 1
    printf("File %s, line %i: theMostNewInsertPoint function.\n", (char *)__FILE__, __LINE__);
    // printf("theMostNewInsertPoint function - founded simplex to modify: %14p, center: x: %10.4f, y: %10.4f, radius: %10.4f\n", simplex, simplex->circumcenter.x, simplex->circumcenter.y, simplex->circumradius);
    // printf("Points: p1: x: %10.4f, y: %10.4f, p2: x: %10.4f, y: %10.4f, p3: x: %10.4f, y: %10.4f\n", simplex->vertices[0]->point.x, simplex->vertices[0]->point.y,
    //        simplex->vertices[1]->point.x, simplex->vertices[1]->point.y, simplex->vertices[2]->point.x, simplex->vertices[2]->point.y);
    // printf("Neighbors: 0: %14p, 1: %14p, 2: %14p\n\n", simplex->neighbors[0], simplex->neighbors[1], simplex->neighbors[2]);
    printf("theMostNewInsertPoint function - founded simplex to modify: %s\n\n", printShortSimplex(simplex));
#endif

#if MEASURE_TIME == 1
    gettimeofday(&start, NULL);
    startTime = start.tv_sec * 1000000LL + start.tv_usec;
#endif

    LinkedList *trianglesToModify = findTrianglesToModify(simplex, point);

#if MEASURE_TIME == 1
    gettimeofday(&end, NULL);
    endTime = end.tv_sec * 1000000LL + end.tv_usec;
    trianglesToModifyTime += endTime - startTime;
#endif

#if DEBUG_TRIANGULATION == 1
    LinkedListNode *current = trianglesToModify->first;
    printf("File %s, line %i: theMostNewInsertPoint function.\n", (char *)__FILE__, __LINE__);
    printf("theMostNewInsertPoint function - \x1B[34mfounded triangles to modify\x1B[0m (list):\n");

    while (current != NULL)
    {
        simplex = (Simplex *)current->data;
        // printf("Founded simplex to modify: %14p, center: x: %10.4f, y: %10.4f, radius: %10.4f\n", simplex, simplex->circumcenter.x, simplex->circumcenter.y, simplex->circumradius);
        // printf("Points: p1: x: %10.4f, y: %10.4f, p2: x: %10.4f, y: %10.4f, p3: x: %10.4f, y: %10.4f\n", simplex->vertices[0]->point.x, simplex->vertices[0]->point.y,
        //        simplex->vertices[1]->point.x, simplex->vertices[1]->point.y, simplex->vertices[2]->point.x, simplex->vertices[2]->point.y);
        // printf("Neighbors: 0: %14p, 1: %14p, 2: %14p\n\n", simplex->neighbors[0], simplex->neighbors[1], simplex->neighbors[2]);
        printf("Founded simplex to modify: %s \n\n", printShortSimplex(simplex));
        current = current->next;
    }
    current = trianglesToModify->first;
    printf("Now we will create polygon. \n\n");
#endif

#if MEASURE_TIME == 1
    gettimeofday(&start, NULL);
    startTime = start.tv_sec * 1000000LL + start.tv_usec;
#endif

    PolygonList *edges = findPolygon(point, partition, trianglesToModify);

#if MEASURE_TIME == 1
    gettimeofday(&end, NULL);
    endTime = end.tv_sec * 1000000LL + end.tv_usec;
    findPolygonTime += endTime - startTime;
#endif

#if DEBUG_TRIANGULATION == 1
    PolygonLinkedListNode *currentEdge = edges->first;
    printf("File %s, line %i: theMostNewInsertPoint function.\n", (char *)__FILE__, __LINE__);
    printf("Created polygon (list):\n");
    while (currentEdge != NULL)
    {
        // printf("Edge: %14p, Points: p1: x: %10.4f, y: %10.4f, p2: x: %10.4f, y: %10.4f, first: %14p, second: %14p, secondIndex: %d, neighbors: n1: %14p, n2: %14p \n",
        //        currentEdge->edge, currentEdge->edge->points[0]->point.x, currentEdge->edge->points[0]->point.y,
        //        currentEdge->edge->points[1]->point.x, currentEdge->edge->points[1]->point.y, currentEdge->edge->first, currentEdge->edge->second,
        //        currentEdge->edge->secondIndex, currentEdge->edge->neighbors[0], currentEdge->edge->neighbors[1]);
        printf("Edge: %s \n", printShortEdge(currentEdge->edge));
        currentEdge = currentEdge->next;
    }
    currentEdge = edges->first;
    printf("End of polygon list \n\n");
#endif

    // Teraz analizujemy każdą "krawędź krawędzi" (wymyśleć jak to lepiej nazwać) - dla każdej krawędzi sprawdzam jej krawędzi.
    // W 2D będą to tylko wierzchołki, w 3D będą to krawędzie, w 4D trójkąty i tak dalej.

#if MEASURE_TIME == 1
    gettimeofday(&start, NULL);
    startTime = start.tv_sec * 1000000LL + start.tv_usec;
#endif

    redBlackTree *treeEdgeOfEdges = createTreeOfEdgeOfEdges(edges);

#if MEASURE_TIME == 1
    gettimeofday(&end, NULL);
    endTime = end.tv_sec * 1000000LL + end.tv_usec;
    createTreeOfEdgeOfEdgesTime += endTime - startTime;
#endif

#if MEASURE_TIME == 1
    gettimeofday(&start, NULL);
    startTime = start.tv_sec * 1000000LL + start.tv_usec;
#endif

    uploadInformationsAboutNeighborsInEdges(edges, treeEdgeOfEdges);

#if MEASURE_TIME == 1
    gettimeofday(&end, NULL);
    endTime = end.tv_sec * 1000000LL + end.tv_usec;
    uploadInformationsAboutNeighborsInEdgesTime += endTime - startTime;
#endif

#if DEBUG_TRIANGULATION == 1
    printf("File %s, line %i: theMostNewInsertPoint function.\n", (char *)__FILE__, __LINE__);
    printf("\nUploaded edges by adding information about neighbors:\n");
    while (currentEdge != NULL)
    {
        // printf("Edge: %14p, Points: p1: x: %10.4f, y: %10.4f, p2: x: %10.4f, y: %10.4f, first: %14p, second: %14p, secondIndex: %d, neighbors: n1: %14p, n2: %14p \n",
        //        currentEdge->edge, currentEdge->edge->points[0]->point.x, currentEdge->edge->points[0]->point.y,
        //        currentEdge->edge->points[1]->point.x, currentEdge->edge->points[1]->point.y, currentEdge->edge->first, currentEdge->edge->second,
        //        currentEdge->edge->secondIndex, currentEdge->edge->neighbors[0], currentEdge->edge->neighbors[1]);
        printf("Edge: %s \n", printShortEdge(currentEdge->edge));
        currentEdge = currentEdge->next;
    }
    currentEdge = edges->first;
    printf("\nTree edges of edges:\n\n");
    // redBlackTreeNode *edgeOfEdgeCurrent = minimumInRedBlackSubTree(treeEdgeOfEdges->first);
    // while (edgeOfEdgeCurrent != NULL)
    // {
    //     EdgeOfEdge *currentEdgeOfEdge = edgeOfEdgeCurrent->data;
    //     if (currentEdgeOfEdge == NULL)
    //     {
    //         printf("HMMM?\n");
    //         break;
    //     }
    //     printf("redBlackTreeNode: %14p, edgeOfEdge: %14p, first: %14p, second: %14p, Points: p1: x: %10.4f, y: %10.4f \n", edgeOfEdgeCurrent,
    //            currentEdgeOfEdge, currentEdgeOfEdge->first, currentEdgeOfEdge->second, currentEdgeOfEdge->points[0]->point.x, currentEdgeOfEdge->points[0]->point.y);
    //     edgeOfEdgeCurrent = getNextNodeFromRedBlackTree(treeEdgeOfEdges, edgeOfEdgeCurrent);
    // }
    printRedBlackTreeString(treeEdgeOfEdges, printLongEdgeOfEdge);
    printf("\n");
#endif

#if MEASURE_TIME == 1
    gettimeofday(&start, NULL);
    startTime = start.tv_sec * 1000000LL + start.tv_usec;
#endif

    removeRedBlackTree(treeEdgeOfEdges, true);

    // Teraz mamy dla każdej informacji także o sąsiadach. Możemy to wykorzystać do zapisywania sąsiadów w sympleksach.
    // PointId points[3] = {*point, currentNode->edge->points[0], currentNode->edge->points[1]};

#if DEBUG_TRIANGULATION == 1
    printf("File %s, line %i: theMostNewInsertPoint function.\n", (char *)__FILE__, __LINE__);
    printf("Just before adding new simplexes to triangles tree. \n\npartition->triangles tree:\n");
    printRedBlackTreeString(partition->triangles, printShortSimplex);
#endif

    LinkedList *simplexList = createSimplexList(edges, point, hilbertDimension);

#if DEBUG_TRIANGULATION == 1
    printf("File %s, line %i: theMostNewInsertPoint function.\n", (char *)__FILE__, __LINE__);
    printf("Created linked list with simplexes, now we should correct neighbors and add to Red Black Tree. \n");
#endif

    updateAndAddSimplexes(edges, partition);

    removePolygonList(edges, true);
    removeLinkedList(simplexList, false);
    removeLinkedList(trianglesToModify, true);

#if MEASURE_TIME == 1
    gettimeofday(&end, NULL);
    endTime = end.tv_sec * 1000000LL + end.tv_usec;
    updateAndAddSimplexesTime += endTime - startTime;
#endif

#if DEBUG_TRIANGULATION == 1
    printf("File %s, line %i: theMostNewInsertPoint function.\n", (char *)__FILE__, __LINE__);
    printf("theMostNewInsertPoint function, ended inserting of point: %14p, x: %10.4f, y: %10.4f\n\n", point, point->point.x, point->point.y);
    printf("Triangles:\n");
    printRedBlackTreeString(partition->triangles, printShortSimplex);
    printf("Vertices:\n");
    printRedBlackTree(partition->vertices);
#endif
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

double squareOfDistanceFromPointToLine(Point point, Point point1, Point point2)
{
    double A = point2.y - point1.y;
    double B = point2.x - point1.x;
    double C = point2.x * point1.y - point1.x * point2.y;

    // printf("A: %10.4f, B: %10.4f, C: %10.4f\n", A, B, C);

    double temp = A * point.x + B * point.y + C;
    double squareOfDistance = temp * temp / (A * A + B * B);
    return squareOfDistance;
}

// #if NO_DIM == 3
// double squareOfDistanceFromPointToPlane(Point point, Point point1, Point point2, Point point3)
// {
//     int n = NO_DIM + 1;

//     Point points[3] = {point1, point2, point3};

//     double **aMatrix = (double **)malloc(n * sizeof(double *));
//     double **bMatrix = (double **)malloc(n * sizeof(double *));
//     double **cMatrix = (double **)malloc(n * sizeof(double *));
//     double **dMatrix = (double **)malloc(n * sizeof(double *));

//     for (int i = 0; i < n; i++)
//     {
//         aMatrix[i] = (double *)malloc(n * sizeof(double));
//         bMatrix[i] = (double *)malloc(n * sizeof(double));
//         cMatrix[i] = (double *)malloc(n * sizeof(double));
//         dMatrix[i] = (double *)malloc(n * sizeof(double));
//     }

//     for (int i = 0; i < n; i++)
//     {
//         aMatrix[i][0] = 1;
//         aMatrix[i][1] = points[i].y;
//         aMatrix[i][2] = points[i].z;

//         bMatrix[i][0] = points[i].x;
//         bMatrix[i][1] = 1;
//         bMatrix[i][2] = points[i].z;

//         cMatrix[i][0] = points[i].x;
//         cMatrix[i][1] = points[i].y;
//         cMatrix[i][2] = 1;

//         dMatrix[i][0] = points[i].x;
//         dMatrix[i][1] = points[i].y;
//         dMatrix[i][2] = points[i].z;
//     }

//     double detA = determinant(aMatrix, n);
//     double detB = determinant(bMatrix, n);
//     double detC = determinant(cMatrix, n);
//     double detD = determinant(dMatrix, n);

//     double D = -detD;
//     double A = -D / detD * detA;
//     double B = -D / detD * detB;
//     double C = -D / detD * detC;

//     double temp = A * point.x + B * point.y + C * point.z + D;
//     double squareOfDistance = temp * temp / (A * A + B * B + C * C);
//     return squareOfDistance;
// }
// #endif

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
    // double r = s2->circumcenter.x;
    // printf("Data loaded\n");
    double result = s1->circumcenter.x + s1->circumradius - (s2->circumcenter.x + s2->circumradius);
    // printf("Result computed\n");
    if (result == 0)
        return pointsArrayEquals(s1->vertices, s2->vertices, NO_DIM + 1);
    return result;
}

double comparePositionOfTwoTrianglesHilbert(void *a, void *b)
{
    // printf("Compare position of two triangles\n");
    Simplex *s1 = (Simplex *)a;
    Simplex *s2 = (Simplex *)b;
    // double r = s2->circumcenter.x;
    // printf("Data loaded\n");
    double result = s1->hilbertId - s2->hilbertId;
    if (result != 0)
        return result;
    result = s1->circumcenter.x + s1->circumradius - (s2->circumcenter.x + s2->circumradius);
    // printf("Result computed\n");
    if (result == 0)
        return pointsArrayEquals(s1->vertices, s2->vertices, NO_DIM + 1);
    return result;
}

double comparePositionOfTwoTrianglesBox(void *a, void *b)
{

    Simplex *s1 = (Simplex *)a;
    Simplex *s2 = (Simplex *)b;

    double result = 0.0;

    // printf("S1: id: %i, coords: %i, %i, S2: id: %i, coords: %i, %i\n", s1->id, s1->boxId[0], s1->boxId[1], s2->id, s2->boxId[0], s2->boxId[1]);

    for (int i = 0; i < NO_DIM; i++)
    {
        result = s1->boxId[i] - s2->boxId[i];
        if (result != 0)
            return result;
    }

    result = s1->circumcenter.x + s1->circumradius - (s2->circumcenter.x + s2->circumradius);

    if (result == 0)
        return pointsArrayEquals(s1->vertices, s2->vertices, NO_DIM + 1);
    return result;
}

double comparePositionOfTwoTrianglesBox2(void *a, void *b)
{

    Simplex *s1 = (Simplex *)a;
    Simplex *s2 = (Simplex *)b;

    double result;

    for (int i = 0; i < NO_DIM; i++)
    {
        result = s1->boxId[i] - s2->boxId[i];
        if (result != 0)
            return result;
    }
    

    return result;
}

double comparePointers(void *a, void *b)
{
    return (double)((long *)a - (long *)b);
}

void changePointsInSimplex(PointId *points, void *pointer)
{
    Simplex *simplex = (Simplex *)pointer;
    memcpy(simplex->vertices, points, (NO_DIM + 1) * sizeof(PointId));

    calculateCircumcircle(simplex);
}

void printRedBlackTree(redBlackTree *tree)
{
    printf("\nRed-Black Tree:\n");
    redBlackTreeNode *node = minimumInRedBlackSubTree(tree->first);
    printf("tree->first: %14p\n", tree->first);

    while (node != NULL)
    {
        PointId *point = (PointId *)node->data;
        printf("Node: %14p, Data: %14p, Parent: %14p, Left: %14p, Right: %14p, Colour: %s, x: %10.4f, y: %10.4f\n", node, node->data, node->parent, node->left, node->right, node->colour == Red ? "Red  " : "Black", point->point.x, point->point.y);
        node = getNextNodeFromRedBlackTree(tree, node);
    }
    printf("\n\n");
}

void printRedBlackTreeString(redBlackTree *tree, char *(*printData)(void *))
{
    printf("\nRed-Black Tree:\n");
    redBlackTreeNode *node = minimumInRedBlackSubTree(tree->first);
    printf("tree->first: %14p\n", tree->first);

    while (node != NULL)
    {
        printf("Node: %14p, Data: %14p, Parent: %14p, Left: %14p, Right: %14p, Colour: %s, %s\n", node, node->data, node->parent, node->left, node->right, node->colour == Red ? "Red  " : "Black", printData(node->data));
        node = getNextNodeFromRedBlackTree(tree, node);
    }
    printf("\n\n");
}

void printRedBlackTreeTriangles(redBlackTree *tree)
{
    printf("\nRed-Black Tree:\n");
    redBlackTreeNode *node = minimumInRedBlackSubTree(tree->first);
    printf("tree->first: %14p\n", tree->first);

    while (node != NULL)
    {
        Simplex *simplex = (Simplex *)node->data;
        printf("Node: %14p, Data: %14p, Parent: %14p, Left: %14p, Right: %14p, Colour: %s \n", node, node->data, node->parent, node->left, node->right, node->colour == Red ? "Red  " : "Black");
#if NO_DIM == 2
        printf("Simplex: circumcenter: x: %10.4f, y: %10.4f, circumradius: %10.4f, Points: p1: x: %10.4f, y: %10.4f, p2: x: %10.4f, y: %10.4f, p3: x: %10.4f, y: %10.4f, Neighbors: n1: %14p, n2: %14p, n3: %14p\n",
               simplex->circumcenter.x, simplex->circumcenter.y, simplex->circumradius, simplex->vertices[0]->point.x, simplex->vertices[0]->point.y,
               simplex->vertices[1]->point.x, simplex->vertices[1]->point.y, simplex->vertices[2]->point.x, simplex->vertices[2]->point.y, simplex->neighbors[0], simplex->neighbors[1], simplex->neighbors[2]);
#endif
#if NO_DIM == 3
        printf("Simplex: circumcenter: x: %10.4f, y: %10.4f, z: %10.4f, circumradius: %10.4f, Points: p1: x: %10.4f, y: %10.4f, z: %10.4f, p2: x: %10.4f, y: %10.4f, z: %10.4f, \
p3: x: %10.4f, y: %10.4f, z: %10.4f, p4: x: %10.4f, y: %10.4f, z: %10.4f, Neighbors: n1: %14p, n2: %14p, n3: %14p, n4: %14p\n",
               simplex->circumcenter.x, simplex->circumcenter.y, simplex->circumcenter.z, simplex->circumradius, simplex->vertices[0]->point.x, simplex->vertices[0]->point.y, simplex->vertices[0]->point.z,
               simplex->vertices[1]->point.x, simplex->vertices[1]->point.y, simplex->vertices[1]->point.z, simplex->vertices[2]->point.x, simplex->vertices[2]->point.y, simplex->vertices[2]->point.z,
               simplex->vertices[3]->point.x, simplex->vertices[3]->point.y, simplex->vertices[3]->point.z, simplex->neighbors[0], simplex->neighbors[1], simplex->neighbors[2], simplex->neighbors[3]);
#endif
        node = getNextNodeFromRedBlackTree(tree, node);
    }
    printf("\n\n");
}
