#include <stdio.h>
#include <stdlib.h>

#if defined(WIND32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#include <time.h>
#include <Windows.h>
#else
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#endif

#include <math.h>
#include "serialDT.h"
// #include "../../Utilities/validateResult.h"
// #include "../../DTFE/DTFE.h"
// #include "../../IO/io.h"
#include "../../oneHeaderToRuleThemAll.h"
// #include "../../Utilities/utilities.h"

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

long long LUTRBTDLLInsertCount = 0;
long long LUTRBTDLLGetCount = 0;
long long LUTRBTDLLPrevNodeCount = 0;
long long LUTRBTDLLNextNodeCount = 0;
long long LUTRBTDLLRemoveCount = 0;

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
    initializePartition(partition, options);
    partition->hilbertDimension = options->PHgridSize;

    long long time1 = 0, time2 = 0;

    if (!options->onlyDTFE)
    {
        supertriangles(partition, options);

        if(NO_DIM == 3)
            if(strcmp(options->inputFilename, "") != 0)
                asciiLoad2(options->inputFilename, partition, options);
            else
            {
                printf("No file to read given! Randoming the data. \n");
                randData(partition, options);
            }
        else
            randData(partition, options);

        struct timeval te;
        gettimeofday(&te, NULL);
        time1 = te.tv_sec * 1000000LL + te.tv_usec;

        computeDelaunayTriangulation(partition, options);

        struct timeval te2;
        gettimeofday(&te2, NULL);
        time2 = te2.tv_sec * 1000000LL + te2.tv_usec;

        printf("\nElapsed time in us: %lld, in s: %f\n", time2 - time1, (double)(time2 - time1)/1000000.0);
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
    printf("\nElapsed time in us: %lld, in s: %f\n", time3, (double)(time3)/1000000.0);

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

    // printf("Counts: \n");
    // printf("%i\n", findInPolygonListCount);
    // printf("%lld\n", redBlackTreeInsertCount);
    // printf("%lld\n", redBlackTreeGetCount);
    // printf("%lld\n", redBlackTreeRemoveCount);
    // printf("%lld\n", redBlackTreeNextNodeCount);

    // printf("%lld\n", redBlackTreeInsertDLLCount);
    // printf("%lld\n", redBlackTreeGetDLLCount);
    // printf("%lld\n", redBlackTreeRemoveDLLCount);
    // printf("%lld\n", redBlackTreeNextNodeDLLCount);

    // printf("%lld\n", LUTRBTDLLInsertCount);
    // printf("%lld\n", LUTRBTDLLGetCount);
    // printf("%lld\n", LUTRBTDLLRemoveCount);
    // printf("%lld\n", LUTRBTDLLNextNodeCount);

    if(options->saveFileType == 0)
        saveDTFEToBinaryFile(options, partition);
    else
        saveDTFEToTextFile(options, partition);
    
    // Saving statistics about Monte-Carlo method
    // saveStatisticsToTextFile(options, partition);

#if VALIDATE_RESULT == 1
    validateResult(partition);
#endif

    freePartition(partition);
    free(partition);

    return time2 - time1;
}

void initializePartition(Partition *partition, UserOptions *options)
{
    partition->vertices = newRedBlackTree(comparePointsVoids, free);
    partition->globalVertices = newRedBlackTree(comparePointsVoids, free);
#if REDBLACKTREEDLL == 1
    partition->triangles = newRedBlackTreeDLL(comparePositionOfTwoTrianglesBox, freeSimplex);
#elif REDBLACKTREEDLL == 2
    partition->triangles = generateLUTRBTDLL(options->PHgridSize, comparePositionOfTwoTrianglesZCurve);
#else
    partition->triangles = newRedBlackTree(comparePositionOfTwoTrianglesBox, freeSimplex);
#endif
    partition->gridMatrix = (BlockSizeArrayDouble**)malloc(INTERPOLATED_FIELDS * sizeof(BlockSizeArrayDouble*));

    BLOCK_TYPE size = 1;
    for(int i = 0; i < NO_DIM; i++)
        size *= options->gridSize;

    for(int i = 0; i < INTERPOLATED_FIELDS; i++)
        partition->gridMatrix[i] = generateBlockSizeArrayDouble(size);

}

void freePartition(Partition *partition)
{
    removeRedBlackTree(partition->vertices, true);
    removeRedBlackTree(partition->globalVertices, true);
#if REDBLACKTREEDLL == 1
    removeRedBlackTreeDLL(partition->triangles, true);
#elif REDBLACKTREEDLL == 2
    removeLUTRBTDLL(partition->triangles, true);
#else
    removeRedBlackTree(partition->triangles, true);
#endif
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

        if(options->points != -1)
            if (c == options->points)
                break;
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

#if REDBLACKTREEDLL == 2
    Simplex *simplex = findFirstSimplexToModifyLUT(point, partition, options);
#else
    Simplex *simplex = findFirstSimplexToModify(point, partition, options);
#endif

#if MEASURE_TIME == 1
    struct timeval end;
    gettimeofday(&end, NULL);
    long long endTime = end.tv_sec * 1000000LL + end.tv_usec;
    findFirstSimplexTime += endTime - startTime;
#endif

    if (simplex == NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: Something very weird - We didn't found simplex to modify. \n\n", (char *)__FILE__, __LINE__);
#if REDBLACKTREEDLL == 2
        Simplex *simplex = findFirstSimplexToModifyLUT(point, partition, options);
#endif
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

    LinkedList *simplexList = createSimplexList(edges, point, options, partition);

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

double squareOfDistanceFromPointToPoint(Point point1, Point point2)
{
    double result = 0;
    for (int i = 0; i < NO_DIM; i++)
    {
        double d = point1.coords[i] - point2.coords[i];
        result += d * d;
    }
    return result;
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


void randData(Partition *partition, UserOptions *options)
{
    srand(time(NULL));

    int n = options->points;

    for(int i = 0; i < n; i++)
    {
        PointId *point = newEmptyPointId();
        for(int j = 0; j < NO_DIM; j++)
            point->point.coords[j] = ((double)rand() / RAND_MAX);

        point->mass = options->massInSuperpoints;

        insertIntoRedBlackTree(partition->vertices, point);
    }
}