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

void TIPP(int k, int n)
{
    // putPointsToPartitions(partitions, points);

    // Set *initialPoints;
    // int k = 10000;
    // chooseRandomlyInitialPoints(partitions, points, initialPoints, k);

    // DelaunayTriangulation *initialMesh;
    Partition *partition = (Partition *)malloc(sizeof(Partition));
    initializePartition(partition);

    // printf("Generowanie partycji \n");
    generateInitialMesh(partition, k);

#if DEBUG_TRIANGULATION == 1
    printf("Trójkąty: \n");

    printRedBlackTreeTriangles(partition->triangles);

    printf("Wierzchołki: \n");

    printRedBlackTree(partition->vertices);
#endif

    // printf("Obliczanie DT \n\n");
    // DelaunayTriangulation DT = computeDelaunayTriangulation(partition);
    // printf("partition->vertices->first->prev: %14p\n", partition->vertices->first->prev);
    // printf("partition->triangles->first->prev: %14p\n", partition->triangles->first->prev);

    struct timeval te;
    gettimeofday(&te, NULL);
    long long time1 = te.tv_sec * 1000000LL + te.tv_usec;
    computeDelaunayTriangulation(partition, n);
    struct timeval te2;
    gettimeofday(&te2, NULL);
    long long time2 = te2.tv_sec * 1000000LL + te2.tv_usec;

    printf("%d, %lld\n", n, time2 - time1);
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

    // FILE *fp;
    // fp = fopen("./out/outputVertices.txt", "w+");

    // //void *pointer = partition->vertices->first;
    // redBlackTreeNode *pointer = minimumInRedBlackSubTree(partition->vertices->first);

    // while (pointer != NULL)
    // {
    //     PointId *point = (PointId *)pointer->data;
    //     fprintf(fp, "%10.4f, %10.4f \n", point->point.x, point->point.y);
    //     pointer = getNextNodeFromRedBlackTree(partition->vertices, pointer);
    // }

    // fclose(fp);

    // fp = fopen("./out/outputTriangles.txt", "w+");

    // pointer = minimumInRedBlackSubTree(partition->triangles->first);

    // while (pointer != NULL)
    // {
    //     // printf("Load next triangle\n");
    //     Simplex *simplex = (Simplex *)pointer->data;
    //     // printf("Loaded\n");
    //     // fprintf(fp, "%10.4f, %10.4f, %10.4f, %10.4f, %10.4f, %10.4f, %10.4f, %10.4f, %10.4f \n", simplex->circumcenter.x, simplex->circumcenter.y, simplex->circumradius, simplex->vertices[0].point.x, simplex->vertices[0].point.y, simplex->vertices[1].point.x, simplex->vertices[1].point.y, simplex->vertices[2].point.x, simplex->vertices[2].point.y);
    //     fprintf(fp, "%10.4f, %10.4f\n%10.4f, %10.4f\n\n%10.4f, %10.4f\n%10.4f, %10.4f\n\n%10.4f, %10.4f\n%10.4f, %10.4f\n\n",
    //             simplex->vertices[0].point.x, simplex->vertices[0].point.y,
    //             simplex->vertices[1].point.x, simplex->vertices[1].point.y,
    //             simplex->vertices[1].point.x, simplex->vertices[1].point.y,
    //             simplex->vertices[2].point.x, simplex->vertices[2].point.y,
    //             simplex->vertices[2].point.x, simplex->vertices[2].point.y,
    //             simplex->vertices[0].point.x, simplex->vertices[0].point.y);

    //     pointer = getNextNodeFromRedBlackTree(partition->triangles, pointer);
    // }

    // fclose(fp);
    freePartition(partition);
    free(partition);
}

void initializePartition(Partition *partition)
{
    partition->vertices = newRedBlackTree(comparePointsVoids, free);
    partition->globalVertices = newRedBlackTree(comparePointsVoids, free);
    partition->triangles = newRedBlackTree(comparePositionOfTwoTriangles, freeSimplex);
}

void freePartition(Partition *partition)
{
    removeRedBlackTree(partition->vertices, true);
    removeRedBlackTree(partition->globalVertices, true);
    removeRedBlackTree(partition->triangles, true);
}

void putPointsToPartitions(Set *partitions, Set *points)
{
    fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: putPointsToPartitions function is not implemented \n", (char *)__FILE__, __LINE__);
}

void chooseRandomlyInitialPoints(Set *partitions, Set *points, Set *initialPoints, int k)
{
    fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: chooseRandomlyInitialPoints function is not implemented \n", (char *)__FILE__, __LINE__);
}

void generateInitialMesh(Partition *partition, int nParticles)
{
    srand(0);

    supertriangles(partition);

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

    // insertIntoDoubleLinkedList(partition->vertices, first, point2, comparePositionOfTwoPoints);
    // insertIntoDoubleLinkedList(partition->vertices, first, point3, comparePositionOfTwoPoints);
    // insertIntoDoubleLinkedList(partition->vertices, first, point4, comparePositionOfTwoPoints);

    PointId *pointFirst = (PointId *)malloc(sizeof(PointId));
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

    double x = (double)rand() / (double)(RAND_MAX)*100;
    double y = (double)rand() / (double)(RAND_MAX)*100;

    pointFirst->point.x = x;
    pointFirst->point.y = y;
    insertIntoRedBlackTree(partition->vertices, pointFirst);

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

void computeDelaunayTriangulation(Partition *partition, int stopAtStep)
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
        theMostNewInsertPoint(point, partition);

        // printf("Point inserted: x: %10.4f, y: %10.4f\n", point->point.x, point->point.y);
        //pointer = getNextNode(pointer);

        pointer = getNextNodeFromRedBlackTree(partition->vertices, pointer);

        // printf("Next point\n");
        if (c == stopAtStep)
            break;
    }
}

void theMostNewInsertPoint(PointId *point, Partition *partition)
{

#if DEBUG_TRIANGULATION == 1
    printf("File %s, line %i: theMostNewInsertPoint function.\n", (char *)__FILE__, __LINE__);
    printf("theMostNewInsertPoint function, point: %14p, x: %10.4f, y: %10.4f\n\n", point, point->point.x, point->point.y);
#endif

    Simplex *simplex = findFirstSimplexToModify(point, partition);

    if (simplex == NULL)
    {
        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: Something very weird - We didn't found simplex to modify. \n\n", (char *)__FILE__, __LINE__);
        return;
    }

#if DEBUG_TRIANGULATION == 1
    printf("File %s, line %i: theMostNewInsertPoint function.\n", (char *)__FILE__, __LINE__);
    printf("theMostNewInsertPoint function - founded simplex to modify: %14p, center: x: %10.4f, y: %10.4f, radius: %10.4f\n", simplex, simplex->circumcenter.x, simplex->circumcenter.y, simplex->circumradius);
    printf("Points: p1: x: %10.4f, y: %10.4f, p2: x: %10.4f, y: %10.4f, p3: x: %10.4f, y: %10.4f\n", simplex->vertices[0].point.x, simplex->vertices[0].point.y,
           simplex->vertices[1].point.x, simplex->vertices[1].point.y, simplex->vertices[2].point.x, simplex->vertices[2].point.y);
    printf("Neighbors: 0: %14p, 1: %14p, 2: %14p\n\n", simplex->neighbors[0], simplex->neighbors[1], simplex->neighbors[2]);
#endif

    LinkedList *trianglesToModify = findTrianglesToModify(simplex, point);

#if DEBUG_TRIANGULATION == 1
    LinkedListNode *current = trianglesToModify->first;
    printf("File %s, line %i: theMostNewInsertPoint function.\n", (char *)__FILE__, __LINE__);
    printf("theMostNewInsertPoint function - \x1B[34mfounded triangles to modify\x1B[0m (list):\n");

    while (current != NULL)
    {
        simplex = (Simplex *)current->data;
        printf("Founded simplex to modify: %14p, center: x: %10.4f, y: %10.4f, radius: %10.4f\n", simplex, simplex->circumcenter.x, simplex->circumcenter.y, simplex->circumradius);
        printf("Points: p1: x: %10.4f, y: %10.4f, p2: x: %10.4f, y: %10.4f, p3: x: %10.4f, y: %10.4f\n", simplex->vertices[0].point.x, simplex->vertices[0].point.y,
               simplex->vertices[1].point.x, simplex->vertices[1].point.y, simplex->vertices[2].point.x, simplex->vertices[2].point.y);
        printf("Neighbors: 0: %14p, 1: %14p, 2: %14p\n\n", simplex->neighbors[0], simplex->neighbors[1], simplex->neighbors[2]);
        current = current->next;
    }
    current = trianglesToModify->first;
    printf("Now we will create polygon. \n\n");
#endif

    PolygonList *edges = findPolygon(point, partition, trianglesToModify);

#if DEBUG_TRIANGULATION == 1
    PolygonLinkedListNode *currentEdge = edges->first;
    printf("File %s, line %i: theMostNewInsertPoint function.\n", (char *)__FILE__, __LINE__);
    printf("Created polygon (list):\n");
    while (currentEdge != NULL)
    {
        printf("Edge: %14p, Points: p1: x: %10.4f, y: %10.4f, p2: x: %10.4f, y: %10.4f, first: %14p, second: %14p, secondIndex: %d, neighbors: n1: %14p, n2: %14p \n",
               currentEdge->edge, currentEdge->edge->points[0].point.x, currentEdge->edge->points[0].point.y,
               currentEdge->edge->points[1].point.x, currentEdge->edge->points[1].point.y, currentEdge->edge->first, currentEdge->edge->second,
               currentEdge->edge->secondIndex, currentEdge->edge->neighbors[0], currentEdge->edge->neighbors[1]);
        currentEdge = currentEdge->next;
    }
    currentEdge = edges->first;
    printf("\n");
#endif

    // Teraz analizujemy każdą "krawędź krawędzi" (wymyśleć jak to lepiej nazwać) - dla każdej krawędzi sprawdzam jej krawędzi.
    // W 2D będą to tylko wierzchołki, w 3D będą to krawędzie, w 4D trójkąty i tak dalej.

    redBlackTree *treeEdgeOfEdges = createTreeOfEdgeOfEdges(edges);
    uploadInformationsAboutNeighborsInEdges(edges, treeEdgeOfEdges);

#if DEBUG_TRIANGULATION == 1
    printf("File %s, line %i: theMostNewInsertPoint function.\n", (char *)__FILE__, __LINE__);
    printf("\nUploaded edges by adding information about neighbors:\n");
    while (currentEdge != NULL)
    {
        printf("Edge: %14p, Points: p1: x: %10.4f, y: %10.4f, p2: x: %10.4f, y: %10.4f, first: %14p, second: %14p, secondIndex: %d, neighbors: n1: %14p, n2: %14p \n",
               currentEdge->edge, currentEdge->edge->points[0].point.x, currentEdge->edge->points[0].point.y,
               currentEdge->edge->points[1].point.x, currentEdge->edge->points[1].point.y, currentEdge->edge->first, currentEdge->edge->second,
               currentEdge->edge->secondIndex, currentEdge->edge->neighbors[0], currentEdge->edge->neighbors[1]);
        currentEdge = currentEdge->next;
    }
    currentEdge = edges->first;
    printf("\nTree edges of edges:\n\n");
    redBlackTreeNode *edgeOfEdgeCurrent = minimumInRedBlackSubTree(treeEdgeOfEdges->first);
    while (edgeOfEdgeCurrent != NULL)
    {
        EdgeOfEdge *currentEdgeOfEdge = edgeOfEdgeCurrent->data;
        if (currentEdgeOfEdge == NULL)
        {
            printf("HMMM?\n");
            break;
        }
        printf("redBlackTreeNode: %14p, edgeOfEdge: %14p, first: %14p, second: %14p, Points: p1: x: %10.4f, y: %10.4f \n", edgeOfEdgeCurrent,
               currentEdgeOfEdge, currentEdgeOfEdge->first, currentEdgeOfEdge->second, currentEdgeOfEdge->points[0].point.x, currentEdgeOfEdge->points[0].point.y);
        edgeOfEdgeCurrent = getNextNodeFromRedBlackTree(treeEdgeOfEdges, edgeOfEdgeCurrent);
    }
    printf("\n");
#endif

    removeRedBlackTree(treeEdgeOfEdges, true);

    // Teraz mamy dla każdej informacji także o sąsiadach. Możemy to wykorzystać do zapisywania sąsiadów w sympleksach.
    // PointId points[3] = {*point, currentNode->edge->points[0], currentNode->edge->points[1]};

#if DEBUG_TRIANGULATION == 1
    printf("File %s, line %i: theMostNewInsertPoint function.\n", (char *)__FILE__, __LINE__);
    printf("Just before adding new simplexes to triangles tree. \n\npartition->triangles tree:\n");
    printRedBlackTreeTriangles(partition->triangles);
#endif

    LinkedList *simplexList = createSimplexList(edges, point);

#if DEBUG_TRIANGULATION == 1
    printf("File %s, line %i: theMostNewInsertPoint function.\n", (char *)__FILE__, __LINE__);
    printf("Created linked list with simplexes, now we should correct neighbors and add to Red Black Tree. \n");
#endif

    updateAndAddSimplexes(edges, partition);

    removePolygonList(edges, true);
    removeLinkedList(simplexList, false);
    removeLinkedList(trianglesToModify, true);

#if DEBUG_TRIANGULATION == 1
    printf("File %s, line %i: theMostNewInsertPoint function.\n", (char *)__FILE__, __LINE__);
    printf("theMostNewInsertPoint function, ended inserting of point: %14p, x: %10.4f, y: %10.4f\n\n", point, point->point.x, point->point.y);
    printf("Triangles:\n");
    printRedBlackTreeTriangles(partition->triangles);
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
    // double r = s2->circumcenter.x;
    // printf("Data loaded\n");
    double result = s1->circumcenter.x + s1->circumradius - (s2->circumcenter.x + s2->circumradius);
    // printf("Result computed\n");
    if (result == 0)
        return pointsArrayEquals(s1->vertices, s2->vertices, NO_DIM + 1);
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

void printRedBlackTreeString(redBlackTree *tree, char* (*printData)(void *))
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
        printf("Simplex: circumcenter: x: %10.4f, y: %10.4f, circumradius: %10.4f, Points: p1: x: %10.4f, y: %10.4f, p2: x: %10.4f, y: %10.4f, p3: x: %10.4f, y: %10.4f, Neighbors: n1: %14p, n2: %14p, n3: %14p\n",
               simplex->circumcenter.x, simplex->circumcenter.y, simplex->circumradius, simplex->vertices[0].point.x, simplex->vertices[0].point.y,
               simplex->vertices[1].point.x, simplex->vertices[1].point.y, simplex->vertices[2].point.x, simplex->vertices[2].point.y, simplex->neighbors[0], simplex->neighbors[1], simplex->neighbors[2]);
        node = getNextNodeFromRedBlackTree(tree, node);
    }
    printf("\n\n");
}

Simplex *findFirstSimplexToModify(PointId *point, Partition *partition)
{
    // redBlackTreeNode *pointer = minimumInRedBlackSubTree(partition->triangles->first);
    Simplex *forSearch = (Simplex*)malloc(sizeof(Simplex));
    forSearch->circumcenter.x = point->point.x;
    forSearch->circumradius = 0;
    redBlackTreeNode *pointer = getFromRedBlackTreeFirstSmaller(partition->triangles, forSearch);

    free(forSearch);

    Simplex *simplex;
    double squareDistance;
    double squareRadius;

    while (pointer != NULL)
    {
        simplex = (Simplex *)pointer->data;
        squareDistance = squareOfDistanceFromPointToPoint(simplex->circumcenter, point->point);
        squareRadius = simplex->circumradius * simplex->circumradius;

#if DEBUG_TRIANGULATION == 1
        printf("File %s, line %i: theMostNewInsertPoint function.\n", (char *)__FILE__, __LINE__);
        printf("Analyze of simplex - %14p\n\n", simplex);
#endif

        if (squareDistance <= squareRadius)
        {
#if DEBUG_TRIANGULATION == 1
            printf("File %s, line %i: theMostNewInsertPoint function.\n", (char *)__FILE__, __LINE__);
            printf("Founded simplex to modify - %14p, distance: %10.4f, radius: %10.4f\n\n", simplex, sqrt(squareDistance), sqrt(squareRadius));
#endif
            break;
        }

        //pointer = getNextNode(pointer);
        pointer = getNextNodeFromRedBlackTree(partition->triangles, pointer);
    }

    return simplex;
}

LinkedList *findTrianglesToModify(Simplex *simplex, PointId *point)
{
    LinkedList *trianglesToModify = newLinkedList(freeSimplex);

    // Teraz stwórz sobie listę odwiedzanych po kolei
    // Trzeba oznaczać te sympleksy, które już odwiedziliśmy.

    // Niech lista trianglesToModify przechowuje listę trójkątów do modyfikacji
    // Niech lista listToAnalyze przechowuje listę trójkątów, które muszę jeszcze odwiedzić
    // A drzewo tree te, które już dodałem kiedykolwiek do listy do analizy (aby nie odwiedzać ich kolejny raz).

    LinkedList *listToAnalyze = newLinkedList(freeSimplex);
    redBlackTree *tree = newRedBlackTree(comparePointers, freeSimplex);

    pushToLinkedList(listToAnalyze, simplex);
    insertIntoRedBlackTree(tree, simplex);

    while (listToAnalyze->count != 0)
    {
        simplex = popFromLinkedList(listToAnalyze);

#if DEBUG_TRIANGULATION == 1
        printf("File %s, line %i: theMostNewInsertPoint function.\n", (char *)__FILE__, __LINE__);
        printf("theMostNewInsertPoint function - simplex to analyze: %14p, center: x: %10.4f, y: %10.4f, radius: %10.4f\n", simplex, simplex->circumcenter.x, simplex->circumcenter.y, simplex->circumradius);
        printf("Points: p1: x: %10.4f, y: %10.4f, p2: x: %10.4f, y: %10.4f, p3: x: %10.4f, y: %10.4f\n", simplex->vertices[0].point.x, simplex->vertices[0].point.y,
               simplex->vertices[1].point.x, simplex->vertices[1].point.y, simplex->vertices[2].point.x, simplex->vertices[2].point.y);
        printf("Neighbors: 0: %14p, 1: %14p, 2: %14p\n\n", simplex->neighbors[0], simplex->neighbors[1], simplex->neighbors[2]);

        // printf("Tree (tree with simplexes anytime added to analyze): \n");
        // printRedBlackTreeTriangles(tree);
#endif

        double squareDistance = squareOfDistanceFromPointToPoint(simplex->circumcenter, point->point);
        double squareRadius = simplex->circumradius * simplex->circumradius;

        if (squareDistance <= squareRadius)
        {
            pushToLinkedList(trianglesToModify, simplex);

#if DEBUG_TRIANGULATION == 1
            printf("File %s, line %i: theMostNewInsertPoint function.\n", (char *)__FILE__, __LINE__);
            printf("This triangle must be later modified. Added to Linked List. Simplex: %14p \n\n", simplex);
#endif

            for (int i = 0; i < NO_DIM + 1; i++)
            {
                Simplex *toAdd = simplex->neighbors[i];

                if (toAdd == NULL)
                    continue;

                redBlackTreeNode *nodeFromTree = getFromRedBlackTree(tree, toAdd);
                Simplex *fromTree = NULL;

                if (nodeFromTree != NULL)
                {
                    fromTree = (Simplex *)nodeFromTree->data;
                }

                if (fromTree == NULL)
                {
#if DEBUG_TRIANGULATION == 1
                    printf("File %s, line %i: theMostNewInsertPoint function.\n", (char *)__FILE__, __LINE__);
                    printf("This neighbor must be later analized. Added to Linked List: %14p \n\n", toAdd);
#endif
                    pushToLinkedList(listToAnalyze, toAdd);
                    insertIntoRedBlackTree(tree, toAdd);
                }
                else
                {
                    if (toAdd != fromTree)
                    {
                        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: Something very weird - firstly founded this pointer in tree, but later is other that expected. toAdd: %14p, fromTree: %14p\n", (char *)__FILE__, __LINE__, toAdd, fromTree);
                        // #if DEBUG_TRIANGULATION == 1
                        //                             printf("This neighbor must be later analized. Also he has the same circum as current, but other points. Added to Linked List: %14p \n\n", toAdd);
                        // #endif
                        //                             pushToLinkedList(listToAnalyze, toAdd);
                    }
                    // Exists in tree, so we processed ealier this simplex.
                }
            }
        }
    }

    removeLinkedList(listToAnalyze, false);
    removeRedBlackTree(tree, false);

    return trianglesToModify;
}

PolygonList *findPolygon(PointId *point, Partition *partition, LinkedList *trianglesToModify)
{
    PolygonList *edges = newPolygonList(freeEdge);
    PolygonList *removedEdges = newPolygonList(freeEdge);
    LinkedListNode *current = trianglesToModify->first;

    while (current != NULL)
    {
        Simplex *data = current->data;

#if DEBUG_TRIANGULATION == 1
        Simplex *simplex = data;
        printf("File %s, line %i: theMostNewInsertPoint function.\n", (char *)__FILE__, __LINE__);
        printf("Creating polygon. Analyze of simplex: %14p, center: x: %10.4f, y: %10.4f, radius: %10.4f\n", simplex, simplex->circumcenter.x, simplex->circumcenter.y, simplex->circumradius);
        printf("Points: p1: x: %10.4f, y: %10.4f, p2: x: %10.4f, y: %10.4f, p3: x: %10.4f, y: %10.4f\n", simplex->vertices[0].point.x, simplex->vertices[0].point.y,
               simplex->vertices[1].point.x, simplex->vertices[1].point.y, simplex->vertices[2].point.x, simplex->vertices[2].point.y);
        printf("Neighbors: 0: %14p, 1: %14p, 2: %14p\n\n", simplex->neighbors[0], simplex->neighbors[1], simplex->neighbors[2]);
#endif

        for (int i = 0; i < NO_DIM + 1; i++)
        {
            Edge *edge = createNewEdge(data, i);

// Do usunięcia
#if DEBUG_TRIANGULATION == 1
            printf("File %s, line %i: theMostNewInsertPoint function.\n", (char *)__FILE__, __LINE__);
            printf("Current Edge: %14p, Points: p1: x: %10.4f, y: %10.4f, p2: x: %10.4f, y: %10.4f, first: %14p, second: %14p, secondIndex: %d, neighbors: n1: %14p, n2: %14p \n\n",
                   edge, edge->points[0].point.x, edge->points[0].point.y,
                   edge->points[1].point.x, edge->points[1].point.y, edge->first, edge->second,
                   edge->secondIndex, edge->neighbors[0], edge->neighbors[1]);
#endif

            PolygonLinkedListNode *founded = findInPolygonList(edges, edge);
#if DEBUG_TRIANGULATION == 1
            printf("File %s, line %i: theMostNewInsertPoint function.\n", (char *)__FILE__, __LINE__);
            printf("Current edge: %14p, Founded edge in edges: %14p\n", edge, founded);
            printf("Current Edge: %14p, Points: p1: x: %10.4f, y: %10.4f, p2: x: %10.4f, y: %10.4f, first: %14p, second: %14p, secondIndex: %d, neighbors: n1: %14p, n2: %14p \n\n",
                   edge, edge->points[0].point.x, edge->points[0].point.y,
                   edge->points[1].point.x, edge->points[1].point.y, edge->first, edge->second,
                   edge->secondIndex, edge->neighbors[0], edge->neighbors[1]);
            if (founded != NULL)
                printf("Edge from founded: %14p, p1: x: %10.4f, y: %10.4f, p2: x: %10.4f, y: %10.4f\n", founded->edge, founded->edge->points[0].point.x, founded->edge->points[0].point.y, founded->edge->points[1].point.x, founded->edge->points[1].point.y);
            printf("\n");
#endif

            if (founded == NULL)
            {
                founded = findInPolygonList(removedEdges, edge);
                if (founded == NULL)
                {
                    insertIntoPolygonList(edges, edge);
                }
            }
            else
            {
#if DEBUG_TRIANGULATION == 1
                printf("File %s, line %i: theMostNewInsertPoint function.\n", (char *)__FILE__, __LINE__);
                printf("Edge founded and removed from polygon list: %14p, p1: x: %10.4f, y: %10.4f, p2: x: %10.4f, y: %10.4f\n\n", founded->edge, founded->edge->points[0].point.x, founded->edge->points[0].point.y, founded->edge->points[1].point.x, founded->edge->points[1].point.y);
#endif
                freeEdge(edge);
                insertIntoPolygonList(removedEdges, founded->edge);
                removeFromPolygonList(edges, founded);
            }
        }

#if DEBUG_TRIANGULATION == 1
        printf("partition->triangles Tree:\n");
        printRedBlackTreeTriangles(partition->triangles);
#endif
        //removeFromDoubleLinkedList(partition->triangles, current->data);
        redBlackTreeNode *fromTree = getFromRedBlackTree(partition->triangles, data);
        if (fromTree == NULL)
            fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: Something very weird - Don't found simplex in triangles tree (partition->triangles), which one we want to remove. Simplex: %14p, fromTree: %14p \n", (char *)__FILE__, __LINE__, data, fromTree);

#if DEBUG_TRIANGULATION == 1
        printf("Removing from triangle tree this simplex: \x1B[33m%14p, node: %14p\x1B[0m\n", fromTree->data, fromTree);
        simplex = (Simplex *)fromTree->data;
        printf("Node: %14p, Simplex: %14p, Parent: %14p, Left: %14p, Right: %14p, Colour: %s \n", fromTree, fromTree->data, fromTree->parent, fromTree->left, fromTree->right, fromTree->colour == Red ? "Red  " : "Black");
        printf("Simplex: circumcenter: x: %10.4f, y: %10.4f, circumradius: %10.4f, Points: p1: x: %10.4f, y: %10.4f, p2: x: %10.4f, y: %10.4f, p3: x: %10.4f, y: %10.4f, Neighbors: n1: %14p, n2: %14p, n3: %14p\n\n",
               simplex->circumcenter.x, simplex->circumcenter.y, simplex->circumradius, simplex->vertices[0].point.x, simplex->vertices[0].point.y,
               simplex->vertices[1].point.x, simplex->vertices[1].point.y, simplex->vertices[2].point.x, simplex->vertices[2].point.y, simplex->neighbors[0], simplex->neighbors[1], simplex->neighbors[2]);
        printf("partition->triangles: \n");
        printRedBlackTreeTriangles(partition->triangles);
#endif

        removeFromRedBlackTree(partition->triangles, fromTree);

#if DEBUG_TRIANGULATION == 1
        printf("partition->triangles: \n");
        printRedBlackTreeTriangles(partition->triangles);
#endif

        //Potencjalnie niebezpieczne
        // freeSimplex(data);
        current = current->next;
    }

    removePolygonList(removedEdges, true);
    return edges;
}

redBlackTree *createTreeOfEdgeOfEdges(PolygonList *edges)
{
    redBlackTree *treeEdgeOfEdges = newRedBlackTree(compareTwoEdgesOfEdges, freeEdgeOfEdge);
    PolygonLinkedListNode *currentEdge = edges->first;

    while (currentEdge != NULL)
    {
        for (int i = 0; i < NO_DIM; i++)
        {
            EdgeOfEdge *e = newEdgeOfEdge(currentEdge->edge, i);
#if DEBUG_TRIANGULATION == 1
            printf("File %s, line %i: theMostNewInsertPoint function.\n", (char *)__FILE__, __LINE__);
            printf("Created edge of edge: %14p, first: %14p, second: %14p, p1: x: %10.4f, y: %10.4f\n\n", e, e->first, e->second, e->points[0].point.x, e->points[0].point.y);
#endif
            redBlackTreeNode *nodeFromTree = getFromRedBlackTree(treeEdgeOfEdges, e);
            EdgeOfEdge *fromTree = NULL;

            if (nodeFromTree != NULL)
            {
                fromTree = (EdgeOfEdge *)nodeFromTree->data;
            }

#if DEBUG_TRIANGULATION == 1
            printf("File %s, line %i: theMostNewInsertPoint function.\n", (char *)__FILE__, __LINE__);
            printf("NodeFromTree: %14p ", nodeFromTree);
            if (nodeFromTree != NULL)
                printf("fromTree: %14p", fromTree);
            printf("\n\n");
#endif

            if (fromTree == NULL)
            {
#if DEBUG_TRIANGULATION == 1
                printf("File %s, line %i: theMostNewInsertPoint function.\n", (char *)__FILE__, __LINE__);
                printf("Before inserting edge of edge to tree: %14p, first: %14p, second: %14p, p1: x: %10.4f, y: %10.4f\n\n", e, e->first, e->second, e->points[0].point.x, e->points[0].point.y);
#endif
                insertIntoRedBlackTree(treeEdgeOfEdges, e);
#if DEBUG_TRIANGULATION == 1
                printf("File %s, line %i: theMostNewInsertPoint function.\n", (char *)__FILE__, __LINE__);
                printf("After inserting edge of edge to tree: %14p, first: %14p, second: %14p, p1: x: %10.4f, y: %10.4f\n\n", e, e->first, e->second, e->points[0].point.x, e->points[0].point.y);
#endif
            }
            else
            {
                freeEdgeOfEdge(e);
                if (fromTree->second == NULL)
                {
                    fromTree->second = currentEdge->edge;
                    currentEdge->edge->neighbors[i] = fromTree->first;
#if DEBUG_TRIANGULATION == 1
                    printf("File %s, line %i: theMostNewInsertPoint function.\n", (char *)__FILE__, __LINE__);
                    printf("Founded edge of edge in tree: %14p, first: %14p, second: %14p, p1: x: %10.4f, y: %10.4f\n", currentEdge->edge, currentEdge->edge->first, currentEdge->edge->second, currentEdge->edge->points[0].point.x, currentEdge->edge->points[0].point.y);
                    printf("i: %d, Neighbors: n1: %14p, n2: %14p \n", i, currentEdge->edge->neighbors[0], currentEdge->edge->neighbors[1]);
                    printf("Edge of Edge fromTree: %14p, first: %14p, second: %14p\n\n", fromTree, fromTree->first, fromTree->second);
#endif
                }
                else
                {
                    fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: Something very weird - founded more than 2 edges for one edge of edges. Should be only 2 edges. \n", (char *)__FILE__, __LINE__);
                    fprintf(stderr, "fromTree: %14p, first: %14p, second: %14p, Points: p1: x: %10.4f, y: %10.4f\n\n", fromTree, fromTree->first, fromTree->second, fromTree->points[0].point.x, fromTree->points[0].point.y);
                    sleep(4);
                }
            }
        }

        currentEdge = currentEdge->next;
    }

    return treeEdgeOfEdges;
}

void uploadInformationsAboutNeighborsInEdges(PolygonList *edges, redBlackTree *treeEdgeOfEdges)
{
    PolygonLinkedListNode *currentEdge = edges->first;
    while (currentEdge != NULL)
    {
        for (int i = 0; i < NO_DIM; i++)
        {
            EdgeOfEdge *e = newEdgeOfEdge(currentEdge->edge, i);

#if DEBUG_TRIANGULATION == 1
            printf("File %s, line %i: theMostNewInsertPoint function.\n", (char *)__FILE__, __LINE__);
            printf("Created edge of edge: %14p, first: %14p, second: %14p, p1: x: %10.4f, y: %10.4f\n\n", e, e->first, e->second, e->points[0].point.x, e->points[0].point.y);
#endif

            redBlackTreeNode *nodeFromTree = getFromRedBlackTree(treeEdgeOfEdges, e);
            EdgeOfEdge *fromTree = NULL;

            if (nodeFromTree != NULL)
            {
                fromTree = (EdgeOfEdge *)nodeFromTree->data;
            }

#if DEBUG_TRIANGULATION == 1
            printf("File %s, line %i: theMostNewInsertPoint function.\n", (char *)__FILE__, __LINE__);
            printf("NodeFromTree: %14p ", nodeFromTree);
            if (nodeFromTree != NULL)
                printf("fromTree: %14p, first: %14p, second: %14p, Points: p1: x: %10.4f, y: %10.4f", fromTree, fromTree->first, fromTree->second, fromTree->points[0].point.x, fromTree->points[0].point.y);
            printf("\n\n");
#endif

            if (fromTree == NULL)
            {
                fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: Something very weird - we didn't found this EdgeOfEdge in tree. \n", (char *)__FILE__, __LINE__);
            }
            else
            {
                if (fromTree->second == currentEdge->edge)
                {
                    if (fromTree->first != NULL)
                    {
                        currentEdge->edge->neighbors[i] = fromTree->first;
                    }
                    else
                    {
                        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: Something very weird - Second Edge should be connected to this Edge of Edge. \n", (char *)__FILE__, __LINE__);
                    }
                }
                else
                {
                    if (fromTree->first == currentEdge->edge)
                    {
                        if (fromTree->second != NULL)
                        {
                            currentEdge->edge->neighbors[i] = fromTree->second;
                        }
                        else
                        {
                            fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: Something very weird - Second Edge should be connected to this Edge of Edge. \n", (char *)__FILE__, __LINE__);
                        }
                    }
                    else
                    {
                        fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: Something very weird - We should be connected to this Edge of Edge. \n", (char *)__FILE__, __LINE__);
                    }
                }

#if DEBUG_TRIANGULATION == 1
                printf("File %s, line %i: theMostNewInsertPoint function.\n", (char *)__FILE__, __LINE__);
                printf("Current edge: %14p, first: %14p, second: %14p, p1: x: %10.4f, y: %10.4f\n", currentEdge->edge, currentEdge->edge->first, currentEdge->edge->second, currentEdge->edge->points[0].point.x, currentEdge->edge->points[0].point.y);
                printf("i: %d, Neighbors: n1: %14p, n2: %14p \n", i, currentEdge->edge->neighbors[0], currentEdge->edge->neighbors[1]);
                printf("Edge of Edge fromTree: %14p, first: %14p, second: %14p\n\n", fromTree, fromTree->first, fromTree->second);
#endif

                //                 if (fromTree->second != NULL)
                //                 {
                //                     currentEdge->edge->neighbors[i] = fromTree->second;
                // #if DEBUG_TRIANGULATION == 1
                //                     printf("File %s, line %i: theMostNewInsertPoint function.\n", (char *)__FILE__, __LINE__);
                //                     printf("Current edge: %14p, first: %14p, second: %14p, p1: x: %10.4f, y: %10.4f\n", currentEdge->edge, currentEdge->edge->first, currentEdge->edge->second, currentEdge->edge->points[0].point.x, currentEdge->edge->points[0].point.y);
                //                     printf("i: %d, Neighbors: n1: %14p, n2: %14p \n", i, currentEdge->edge->neighbors[0], currentEdge->edge->neighbors[1]);
                //                     printf("Edge of Edge fromTree: %14p, first: %14p, second: %14p\n\n", fromTree, fromTree->first, fromTree->second);
                // #endif
                //                 }
                //                 else
                //                 {
                //                     fprintf(stderr, "\x1B[31mError\x1B[0m in %s line %i: Something very weird - We should find second edge for this edge of edges. \n", (char *)__FILE__, __LINE__);
                //                 }
            }
            freeEdgeOfEdge(e);
        }

        currentEdge = currentEdge->next;
    }
}

LinkedList *createSimplexList(PolygonList *edges, PointId *point)
{
    PolygonLinkedListNode *currentEdge = edges->first;
    LinkedList *simplexList = newLinkedList(freeSimplex);

    while (currentEdge != NULL)
    {
        Simplex *result = (Simplex *)malloc(sizeof(Simplex));
        // PointId points[NO_DIM + 1] = addPointToSortedArray(currentEdge->edge->points, point, NO_DIM + 1);
        // sortPointsArray(&points, NO_DIM + 1);
        PointId points[NO_DIM + 1]; // = addPointAsFirstToArray(currentEdge->edge->points, point, NO_DIM + 1);
        addPointAsFirstToArray(points, currentEdge->edge->points, point, NO_DIM + 1);
        createNewSimplex(result, points);

        result->neighbors[0] = currentEdge->edge->second;
        if (result->neighbors[0] != NULL)
        {
            //Tutaj trzeba naprawić wskaźnik do obecnego sympleksu, trzeba rozpoznać po drugiej stronie który to dokładnie jest. Może zapisywać to w edge? Jako i.
            result->neighbors[0]->neighbors[currentEdge->edge->secondIndex] = result;
        }

        currentEdge->edge->first = result;
        pushToLinkedList(simplexList, result);

#if DEBUG_TRIANGULATION == 1
        Simplex *simplex = result;
        printf("File %s, line %i: theMostNewInsertPoint function.\n", (char *)__FILE__, __LINE__);
        printf("Created Simplex: %14p, center: x: %10.4f, y: %10.4f, radius: %10.4f\n", simplex, simplex->circumcenter.x, simplex->circumcenter.y, simplex->circumradius);
        printf("Points: p1: x: %10.4f, y: %10.4f, p2: x: %10.4f, y: %10.4f, p3: x: %10.4f, y: %10.4f\n", simplex->vertices[0].point.x, simplex->vertices[0].point.y,
               simplex->vertices[1].point.x, simplex->vertices[1].point.y, simplex->vertices[2].point.x, simplex->vertices[2].point.y);
        printf("Neighbors: 0: %14p, 1: %14p, 2: %14p\n", simplex->neighbors[0], simplex->neighbors[1], simplex->neighbors[2]);
        printf("Current Edge: %14p, Points: p1: x: %10.4f, y: %10.4f, p2: x: %10.4f, y: %10.4f, first: %14p, second: %14p, secondIndex: %d, neighbors: n1: %14p, n2: %14p \n\n",
               currentEdge->edge, currentEdge->edge->points[0].point.x, currentEdge->edge->points[0].point.y,
               currentEdge->edge->points[1].point.x, currentEdge->edge->points[1].point.y, currentEdge->edge->first, currentEdge->edge->second,
               currentEdge->edge->secondIndex, currentEdge->edge->neighbors[0], currentEdge->edge->neighbors[1]);
#endif

        currentEdge = currentEdge->next;
    }

    return simplexList;
}

void updateAndAddSimplexes(PolygonList *edges, Partition *partition)
{
    PolygonLinkedListNode *currentEdge = edges->first;

    while (currentEdge != NULL)
    {

        Simplex *result = (Simplex *)currentEdge->edge->first;

        for (int i = 1; i < NO_DIM + 1; i++)
        {
            //result->neighbors[i] = currentEdge->edge->neighbors[i - 1]->first;
            result->neighbors[i] = currentEdge->edge->neighbors[i - 1]->first;
        }
        sortPointsInSimplex(result);
        insertIntoRedBlackTree(partition->triangles, result);

#if DEBUG_TRIANGULATION == 1
        Simplex *simplex = result;
        printf("File %s, line %i: theMostNewInsertPoint function.\n", (char *)__FILE__, __LINE__);
        printf("Created new simplex: %14p, center: x: %10.4f, y: %10.4f, radius: %10.4f\n", simplex, simplex->circumcenter.x, simplex->circumcenter.y, simplex->circumradius);
        printf("Points: p1: x: %10.4f, y: %10.4f, p2: x: %10.4f, y: %10.4f, p3: x: %10.4f, y: %10.4f\n", simplex->vertices[0].point.x, simplex->vertices[0].point.y,
               simplex->vertices[1].point.x, simplex->vertices[1].point.y, simplex->vertices[2].point.x, simplex->vertices[2].point.y);
        printf("Neighbors: 0: %14p, 1: %14p, 2: %14p\n", simplex->neighbors[0], simplex->neighbors[1], simplex->neighbors[2]);
        printf("Current Edge: %14p, Points: p1: x: %10.4f, y: %10.4f, p2: x: %10.4f, y: %10.4f, first: %14p, second: %14p, secondIndex: %d, neighbors: n1: %14p, n2: %14p \n\n",
               currentEdge->edge, currentEdge->edge->points[0].point.x, currentEdge->edge->points[0].point.y,
               currentEdge->edge->points[1].point.x, currentEdge->edge->points[1].point.y, currentEdge->edge->first, currentEdge->edge->second,
               currentEdge->edge->secondIndex, currentEdge->edge->neighbors[0], currentEdge->edge->neighbors[1]);
        printf("Triangles tree: \n");
        printRedBlackTreeTriangles(partition->triangles);
        // printf("Tadam\n");
        // sleep(2);
#endif
        currentEdge = currentEdge->next;
        //insertIntoDoubleLinkedList2(partition->triangles, result, comparePositionOfTwoTriangles);
        // printf("Triangle inserted: %10.4f, %10.4f, %10.4f, %10.4f, %10.4f, %10.4f, %10.4f, %10.4f, %10.4f \n", result->circumcenter.x, result->circumcenter.y, result->circumradius, result->vertices[0].point.x, result->vertices[0].point.y, result->vertices[1].point.x, result->vertices[1].point.y, result->vertices[2].point.x, result->vertices[2].point.y);
    }
}