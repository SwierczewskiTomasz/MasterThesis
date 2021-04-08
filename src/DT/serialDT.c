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
#include "../DTFE/DTFE.h"
#include "../IO/io.h"

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

long long serialDT(UserOptions *options)
{
    Partition *partition = (Partition *)malloc(sizeof(Partition));
    initializePartition(partition);
    partition->hilbertDimension = options->PHgridSize;

    // generateInitialMesh(partition, k, hilbertDimension);

    // asciiLoad("../data/ELEPHANT_N1_R1_out27_f0.001.ascii", partition);
    // asciiLoad2("../data/Hellwing/ELEPHANT_GR_R1_out38_f0.001.ascii", partition);

    long long time1 = 0, time2 = 0;

    if (!options->onlyDTFE)
    {
        supertriangles(partition, options);
        asciiLoad2(options->inputFilename, partition);

        struct timeval te;
        gettimeofday(&te, NULL);
        time1 = te.tv_sec * 1000000LL + te.tv_usec;

        computeDelaunayTriangulation(partition, options);

        struct timeval te2;
        gettimeofday(&te2, NULL);
        time2 = te2.tv_sec * 1000000LL + te2.tv_usec;

        printf("%lld\n", time2 - time1);
    }
    else
    {
        int loaded = loadDT(options, partition);
        printf("Loaded: %i \n", loaded);
        printf("Vertices: %i \n", partition->vertices->count);
        printf("Triangles: %i \n", partition->triangles->count);

        // sleep(5);
    }

#if DEBUG_TRIANGULATION == 1
    printf("Trójkąty: \n");
    printRedBlackTreeDLLString(partition->triangles, printLongSimplex);
    printf("Wierzchołki: \n");
    printRedBlackTreeString(partition->vertices, printLongPointId);
#endif

    if (options->onlyDT)
    {        
        int count = saveDT(options, partition);
        printf("Saved %i triangles\n", count);
        return time2 - time1;
    }

    long long time3 = DTFE(partition, options);
    printf("%lld\n", time3);

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

    //     FILE *fp;
    //     fp = fopen("./out/outputVertices2.txt", "w+");

    //     //void *pointer = partition->vertices->first;
    //     redBlackTreeNode *pointer = minimumInRedBlackSubTree(partition->vertices->first);

    //     while (pointer != NULL)
    //     {
    //         PointId *point = (PointId *)pointer->data;
    //         // fprintf(fp, "%10.4f, %10.4f \n", point->point.x, point->point.y);
    //         pointer = getNextNodeFromRedBlackTree(partition->vertices, pointer);
    //     }

    //     fclose(fp);

    //     fp = fopen("./out/outputTriangles2.txt", "w+");

    // #if REDBLACKTREEDLL == 1
    //     redBlackTreeDLLNode *pointerTriangle = minimumInRedBlackSubTreeDLL(partition->triangles->first);
    // #else
    //     redBlackTreeNode *pointerTriangle = minimumInRedBlackSubTree(partition->triangles->first);
    // #endif

    //     while (pointerTriangle != NULL)
    //     {
    //         // printf("Load next triangle\n");
    //         Simplex *simplex = (Simplex *)pointerTriangle->data;
    //         // printf("Loaded\n");
    //         // fprintf(fp, "%10.4f, %10.4f, %10.4f, %10.4f, %10.4f, %10.4f, %10.4f, %10.4f, %10.4f \n", simplex->circumcenter.x, simplex->circumcenter.y, simplex->circumradius, simplex->vertices[0]->point.x, simplex->vertices[0]->point.y, simplex->vertices[1]->point.x, simplex->vertices[1]->point.y, simplex->vertices[2]->point.x, simplex->vertices[2]->point.y);
    // #if NO_DIM == 2
    //         // fprintf(fp, "%10.4f, %10.4f\n%10.4f, %10.4f\n\n%10.4f, %10.4f\n%10.4f, %10.4f\n\n%10.4f, %10.4f\n%10.4f, %10.4f\n\n",
    //         //         simplex->vertices[0]->point.x, simplex->vertices[0]->point.y,
    //         //         simplex->vertices[1]->point.x, simplex->vertices[1]->point.y,
    //         //         simplex->vertices[1]->point.x, simplex->vertices[1]->point.y,
    //         //         simplex->vertices[2]->point.x, simplex->vertices[2]->point.y,
    //         //         simplex->vertices[2]->point.x, simplex->vertices[2]->point.y,
    //         //         simplex->vertices[0]->point.x, simplex->vertices[0]->point.y);
    // #elif NO_DIM == 3
    //         int r = rand() % 200;
    //         int g = rand() % 200;
    //         int b = rand() % 200;

    //         double e = (double)rand() / (double)RAND_MAX * 0;

    //         // if (!(simplex->vertices[0]->id < 8 || simplex->vertices[1]->id < 8 || simplex->vertices[2]->id < 8 || simplex->vertices[3]->id < 8))
    //         // {
    //         // fprintf(fp, "%10.4f, %10.4f, %10.4f, %i, %i, %i\n%10.4f, %10.4f, %10.4f, %i, %i, %i\n\n%10.4f, %10.4f, %10.4f, %i, %i, %i\n%10.4f, %10.4f, %10.4f, %i, %i, %i\n\n%10.4f, %10.4f, %10.4f, %i, %i, %i\n%10.4f, %10.4f, %10.4f, %i, %i, %i\n\n",
    //         //         simplex->vertices[0]->point.x + e, simplex->vertices[0]->point.y + e, simplex->vertices[0]->point.z + e, r, g, b,
    //         //         simplex->vertices[1]->point.x + e, simplex->vertices[1]->point.y + e, simplex->vertices[1]->point.z + e, r, g, b,
    //         //         simplex->vertices[1]->point.x + e, simplex->vertices[1]->point.y + e, simplex->vertices[1]->point.z + e, r, g, b,
    //         //         simplex->vertices[2]->point.x + e, simplex->vertices[2]->point.y + e, simplex->vertices[2]->point.z + e, r, g, b,
    //         //         simplex->vertices[2]->point.x + e, simplex->vertices[2]->point.y + e, simplex->vertices[2]->point.z + e, r, g, b,
    //         //         simplex->vertices[0]->point.x + e, simplex->vertices[0]->point.y + e, simplex->vertices[0]->point.z + e, r, g, b);

    //         // fprintf(fp, "%10.4f, %10.4f, %10.4f, %i, %i, %i\n%10.4f, %10.4f, %10.4f, %i, %i, %i\n\n%10.4f, %10.4f, %10.4f, %i, %i, %i\n%10.4f, %10.4f, %10.4f, %i, %i, %i\n\n%10.4f, %10.4f, %10.4f, %i, %i, %i\n%10.4f, %10.4f, %10.4f, %i, %i, %i\n\n\n",
    //         //         simplex->vertices[0]->point.x + e, simplex->vertices[0]->point.y + e, simplex->vertices[0]->point.z + e, r, g, b,
    //         //         simplex->vertices[3]->point.x + e, simplex->vertices[3]->point.y + e, simplex->vertices[3]->point.z + e, r, g, b,
    //         //         simplex->vertices[1]->point.x + e, simplex->vertices[1]->point.y + e, simplex->vertices[1]->point.z + e, r, g, b,
    //         //         simplex->vertices[3]->point.x + e, simplex->vertices[3]->point.y + e, simplex->vertices[3]->point.z + e, r, g, b,
    //         //         simplex->vertices[2]->point.x + e, simplex->vertices[2]->point.y + e, simplex->vertices[2]->point.z + e, r, g, b,
    //         //         simplex->vertices[3]->point.x + e, simplex->vertices[3]->point.y + e, simplex->vertices[3]->point.z + e, r, g, b);
    //         // }
    // #endif
    // #if REDBLACKTREEDLL == 1
    //         pointerTriangle = getNextNodeFromRedBlackTreeDLL(partition->triangles, pointerTriangle);
    // #else
    //         pointerTriangle = getNextNodeFromRedBlackTree(partition->triangles, pointerTriangle);
    // #endif
    //     }

    //     fclose(fp);

    FILE *fp;
    fp = fopen("./out/outputVerticesDensity.txt", "w+");

    for (int i = 0; i < 128; i++)
    {
        for (int j = 0; j < 128; j++)
        {
            for (int k = 0; k < 128; k++)
            {
                fprintf(fp, "%e\n", partition->densityMatrix[i][j][k].density * 1000000000);
            }
            // fprintf(fp, "%f, %f, %lf, %f, %e \n", partition->densityMatrix[i][j][100].coords[0], partition->densityMatrix[i][j][100].coords[1], partition->densityMatrix[i][j][100].density, partition->densityMatrix[i][j][100].density * 1000000, partition->densityMatrix[i][j][100].density);
            // for (int k = 0; k < 10; k++)
            // {
            //     // fprintf(fp, "%f, %f, %f, %f \n", partition->densityMatrix[i][j][k].coords[0], partition->densityMatrix[i][j][k].coords[1], partition->densityMatrix[i][j][k].coords[2], partition->densityMatrix[i][j][k].density);
            //     fprintf(fp, "%f, %f, %lf, %f, %e \n", partition->densityMatrix[i][j][k].coords[0], partition->densityMatrix[i][j][k].coords[1], partition->densityMatrix[i][j][k].density, partition->densityMatrix[i][j][k].density * 1000000, partition->densityMatrix[i][j][k].density);
            // }
        }
        // fprintf(fp, "\n");
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

void generateInitialMesh(Partition *partition, int nParticles, UserOptions *options)
{
    srand(0);

    supertriangles(partition, options);

    if (nParticles == 0)
        return;

    PointId *pointFirst;

    FLOATING_POINT_PRECISION coords[NO_DIM];
    for (int i = 0; i < NO_DIM; i++)
    {
        coords[i] = (double)rand() / (double)(RAND_MAX)*100;
    }

    pointFirst = newPointId(coords);

    insertIntoRedBlackTree(partition->vertices, pointFirst);

    for (int i = 0; i < nParticles - 1; i++)
    {
        PointId *point;

        for (int i = 0; i < NO_DIM; i++)
        {
            coords[i] = (double)rand() / (double)(RAND_MAX)*100;
        }

        point = newPointId(coords);

        insertIntoRedBlackTree(partition->vertices, point);
    }
}

void computeDelaunayTriangulation(Partition *partition, UserOptions *options)
{
    redBlackTreeNode *pointer = minimumInRedBlackSubTree(partition->vertices->first);

    int c = 0;

    while (pointer != NULL)
    {
        c++;
        PointId *point = (PointId *)pointer->data;

        theMostNewInsertPoint(point, partition, options);

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

        // if(c == 10000)
        //     break;

        if (c % 1000 == 0)
        {
            printf("\rComputed points in DT: %i", c);
            fflush(stdout);
        }
    }
    printf("\n");
}

void theMostNewInsertPoint(PointId *point, Partition *partition, UserOptions *options)
{

#if DEBUG_TRIANGULATION == 1
    saveToLogs((char *)__FILE__, __LINE__, "theMostNewInsertPoint function, inserting: ", printLongPointId, point);
#endif

#if MEASURE_TIME == 1
    struct timeval start;
    gettimeofday(&start, NULL);
    long long startTime = start.tv_sec * 1000000LL + start.tv_usec;
#endif

    Simplex *simplex = findFirstSimplexToModify(point, partition, options);

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
    saveToLogs((char *)__FILE__, __LINE__, "theMostNewInsertPoint function - founded simplex to modify:", printLongSimplex, simplex);
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
    saveToLogsWithFormat((char *)__FILE__, __LINE__, "theMostNewInsertPoint function - \x1B[34mfounded triangles to modify\x1B[0m (list):\n");

    while (current != NULL)
    {
        simplex = (Simplex *)current->data;
        saveToLogs((char *)__FILE__, __LINE__, "Founded simplex to modify:", printLongSimplex, simplex);
        current = current->next;
    }
    current = trianglesToModify->first;
    saveToLogsWithFormat((char *)__FILE__, __LINE__, "Now we will create polygon. \n\n");
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
    saveToLogsWithFormat((char *)__FILE__, __LINE__, "Created polygon (list):\n");

    while (currentEdge != NULL)
    {
        saveToLogs((char *)__FILE__, __LINE__, "Edge: ", printShortEdge, currentEdge->edge);
        currentEdge = currentEdge->next;
    }
    currentEdge = edges->first;

    saveToLogsWithFormat((char *)__FILE__, __LINE__, "End of polygon list\n\n");
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
    saveToLogsWithFormat((char *)__FILE__, __LINE__, "\nUploaded edges by adding information about neighbors:\n");

    while (currentEdge != NULL)
    {
        saveToLogs((char *)__FILE__, __LINE__, "Edge: ", printShortEdge, currentEdge->edge);
        currentEdge = currentEdge->next;
    }
    currentEdge = edges->first;

    printf("\nTree edges of edges:\n\n");
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
    printRedBlackTreeDLLString(partition->triangles, printLongSimplex);
#endif

    LinkedList *simplexList = createSimplexList(edges, point, options);

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
    saveToLogs((char *)__FILE__, __LINE__, "theMostNewInsertPoint function, ended inserting of point:", printLongPointId, point);

    printf("Triangles:\n");
    printRedBlackTreeDLLString(partition->triangles, printLongSimplex);
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

// double squareOfDistanceFromPointToLine(Point point, Point point1, Point point2)
// {
//     double A = point2.y - point1.y;
//     double B = point2.x - point1.x;
//     double C = point2.x * point1.y - point1.x * point2.y;

//     // printf("A: %10.4f, B: %10.4f, C: %10.4f\n", A, B, C);

//     double temp = A * point.x + B * point.y + C;
//     double squareOfDistance = temp * temp / (A * A + B * B);
//     return squareOfDistance;
// }

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
    //     double dx = point1.x - point2.x;
    //     double dy = point1.y - point2.y;
    // #if NO_DIM == 2
    //     return dx * dx + dy * dy;
    // #else
    //     double dz = point1.z - point2.z;
    //     return dx * dx + dy * dy + dz * dz;
    // #endif
    double result = 0;
    for (int i = 0; i < NO_DIM; i++)
    {
        double d = point1.coords[i] - point2.coords[i];
        result += d * d;
    }
    return result;
}

// double comparePositionOfTwoTriangles(void *a, void *b)
// {
//     // printf("Compare position of two triangles\n");
//     Simplex *s1 = (Simplex *)a;
//     Simplex *s2 = (Simplex *)b;
//     // double r = s2->circumcenter.x;
//     // printf("Data loaded\n");
//     double result = s1->circumcenter.x + s1->circumradius - (s2->circumcenter.x + s2->circumradius);
//     // printf("Result computed\n");
//     if (result == 0)
//         return pointsArrayEquals(s1->vertices, s2->vertices, NO_DIM + 1);
//     return result;
// }

// double comparePositionOfTwoTrianglesHilbert(void *a, void *b)
// {
//     // printf("Compare position of two triangles\n");
//     Simplex *s1 = (Simplex *)a;
//     Simplex *s2 = (Simplex *)b;
//     // double r = s2->circumcenter.x;
//     // printf("Data loaded\n");
//     double result = s1->hilbertId - s2->hilbertId;
//     if (result != 0)
//         return result;
//     result = s1->circumcenter.x + s1->circumradius - (s2->circumcenter.x + s2->circumradius);
//     // printf("Result computed\n");
//     if (result == 0)
//         return pointsArrayEquals(s1->vertices, s2->vertices, NO_DIM + 1);
//     return result;
// }

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

    result = s1->circumcenter.coords[0] + s1->circumradius - (s2->circumcenter.coords[0] + s2->circumradius);

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
        char *temp = printLongPointId(point);
        printf("Node: %14p, Data: %14p, Parent: %14p, Left: %14p, Right: %14p, Colour: %s, Point: %s\n", node, node->data, node->parent, node->left, node->right, node->colour == Red ? "Red  " : "Black", temp);
        free(temp);
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
        char *temp = printData(node->data);
        printf("Node: %14p, Data: %14p, Parent: %14p, Left: %14p, Right: %14p, Colour: %s, %s\n", node, node->data, node->parent, node->left, node->right, node->colour == Red ? "Red  " : "Black", temp);
        free(temp);
        node = getNextNodeFromRedBlackTree(tree, node);
    }
    printf("\n\n");
}

void printRedBlackTreeDLLString(redBlackTreeDLL *tree, char *(*printData)(void *))
{
    printf("\nRed-Black Tree:\n");
    redBlackTreeDLLNode *node = minimumInRedBlackSubTreeDLL(tree->first);
    printf("tree->first: %14p\n", tree->first);

    while (node != NULL)
    {
        char *temp = printData(node->data);
        printf("Node: %14p, Data: %14p, Parent: %14p, Left: %14p, Right: %14p, Colour: %s, \n%s \n", node, node->data, node->parent, node->left, node->right, node->colour == Red ? "Red  " : "Black", temp);
        free(temp);
        node = getNextNodeFromRedBlackTreeDLL(tree, node);
    }
    printf("\n\n");
}

// void printRedBlackTreeTriangles(redBlackTree *tree)
// {
//     printf("\nRed-Black Tree:\n");
//     redBlackTreeNode *node = minimumInRedBlackSubTree(tree->first);
//     printf("tree->first: %14p\n", tree->first);

//     while (node != NULL)
//     {
//         Simplex *simplex = (Simplex *)node->data;
//         printf("Node: %14p, Data: %14p, Parent: %14p, Left: %14p, Right: %14p, Colour: %s \n", node, node->data, node->parent, node->left, node->right, node->colour == Red ? "Red  " : "Black");
// #if NO_DIM == 2
//         // printf("Simplex: circumcenter: x: %10.4f, y: %10.4f, circumradius: %10.4f, Points: p1: x: %10.4f, y: %10.4f, p2: x: %10.4f, y: %10.4f, p3: x: %10.4f, y: %10.4f, Neighbors: n1: %14p, n2: %14p, n3: %14p\n",
//         //        simplex->circumcenter.x, simplex->circumcenter.y, simplex->circumradius, simplex->vertices[0]->point.x, simplex->vertices[0]->point.y,
//         //        simplex->vertices[1]->point.x, simplex->vertices[1]->point.y, simplex->vertices[2]->point.x, simplex->vertices[2]->point.y, simplex->neighbors[0], simplex->neighbors[1], simplex->neighbors[2]);
// #endif
// #if NO_DIM == 3
//         printf("Simplex: circumcenter: x: %10.4f, y: %10.4f, z: %10.4f, circumradius: %10.4f, Points: p1: x: %10.4f, y: %10.4f, z: %10.4f, p2: x: %10.4f, y: %10.4f, z: %10.4f,
// p3: x: %10.4f, y: %10.4f, z: %10.4f, p4: x: %10.4f, y: %10.4f, z: %10.4f, Neighbors: n1: %14p, n2: %14p, n3: %14p, n4: %14p\n",
//                simplex->circumcenter.x, simplex->circumcenter.y, simplex->circumcenter.z, simplex->circumradius, simplex->vertices[0]->point.x, simplex->vertices[0]->point.y, simplex->vertices[0]->point.z,
//                simplex->vertices[1]->point.x, simplex->vertices[1]->point.y, simplex->vertices[1]->point.z, simplex->vertices[2]->point.x, simplex->vertices[2]->point.y, simplex->vertices[2]->point.z,
//                simplex->vertices[3]->point.x, simplex->vertices[3]->point.y, simplex->vertices[3]->point.z, simplex->neighbors[0], simplex->neighbors[1], simplex->neighbors[2], simplex->neighbors[3]);
// #endif
//         node = getNextNodeFromRedBlackTree(tree, node);
//     }
//     printf("\n\n");
// }
