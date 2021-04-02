#include "../supertriangles.h"

#ifndef SERIALDT_H
#define SERIALDT_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "../polygon.h"
#include "../DataStructures/dataStructure.h"
#include "../DataStructures/redBlackTree.h"
#include "../DataStructures/redBlackTreeDLL.h"
#include "../myMath.h"
#include "../simplex.h"
#include "../constants.h"
#include "../edgeOfEdge.h"
#include "../HilbertCurve/hilbertCurve.h"
#include "../Logs/Log.h"


typedef struct Set
{
    //It can be for example LinkedList, DoubleLinkedList or Binary Tree and other
    void *set;
} Set;

typedef struct Partition
{
    Point minCoordinates;
    Point maxCoordinates;
    // DoubleLinkedList *vertices;
    // DoubleLinkedList *triangles;

    redBlackTree *vertices;
    redBlackTree *globalVertices;
#if REDBLACKTREEDLL == 1
    redBlackTreeDLL *triangles;
#else
    redBlackTree *triangles;
#endif

    int hilbertDimension;

    PointWithDensity densityMatrix[256][256][256];
} Partition;

typedef struct DelaunayTriangulation
{
    Partition *partitions;
} DelaunayTriangulation;

// long long serialDT(int k, int n, int hilbertDimension, bool onlyCompute);
long long serialDT(UserOptions *options);
void generateInitialMesh(Partition *partition, int nParticles, UserOptions *options);
double comparePositionOfTwoPoints(void *a, void *b);
void computeDelaunayTriangulation(Partition *partition, UserOptions *options);
void insertPoint(PointId *point, Partition *partition);
// double pointInsideCircumcircle(Point point, PointId points[NO_DIM + 1]);
void calculateCircumcircle(Simplex *simplex);
double squareOfDistanceFromPointToLine(Point point, Point point1, Point point2);
#if NO_DIM == 3
// double squareOfDistanceFromPointToPlane(Point point, Point point1, Point point2, Point point3);
#endif
double squareOfDistanceFromPointToPoint(Point point1, Point point2);

double comparePositionOfTwoTriangles(void *a, void *b);
double comparePositionOfTwoTrianglesHilbert(void *a, void *b);
double comparePositionOfTwoTrianglesBox(void *a, void *b);
void changePointsInSimplex(PointId *points, void *pointer);
double comparePointers(void *a, void *b);

// void newInsertPoint(PointId *point, Partition *partition);
void theMostNewInsertPoint(PointId *point, Partition *partition, UserOptions *options);
PointId **combination(PointId *data, int n);
void printRedBlackTree(redBlackTree *tree);
void printRedBlackTreeString(redBlackTree *tree, char *(*printData)(void *));
void printRedBlackTreeDLLString(redBlackTreeDLL *tree, char *(*printData)(void *));
// void printRedBlackTreeTriangles(redBlackTree *tree);
void initializePartition(Partition *partition);
void freePartition(Partition *partition);

Simplex *findFirstSimplexToModify(PointId *point, Partition *partition, UserOptions *options);
Simplex *findFirstSimplexToModifyPoint(Point *point, Partition *partition, UserOptions *options);
// Simplex *findFirstSimplexToModifyBoxId(PointId *point, Partition *partition, int hilbertDimension);
// Simplex *findFirstSimplexToModifyBoxId2(PointId *point, Partition *partition, int hilbertDimension);
LinkedList *findTrianglesToModify(Simplex *simplex, PointId *point);
LinkedList *findTrianglesToModifyPoint(Simplex *simplex, Point *point);
PolygonList *findPolygon(PointId *point, Partition *partition, LinkedList *trianglesToModify);
redBlackTree *createTreeOfEdgeOfEdges(PolygonList *edges);
void uploadInformationsAboutNeighborsInEdges(PolygonList *edges, redBlackTree *treeEdgeOfEdges);
LinkedList *createSimplexList(PolygonList *edges, PointId *point, UserOptions *options);
void updateAndAddSimplexes(PolygonList *edges, Partition *partition);

#endif