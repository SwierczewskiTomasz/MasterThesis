#ifndef SERIALDT_H
#define SERIALDT_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "../../constants.h"
#include "../../IO/userOptions.h"
#include "../../DataStructures/points.h"
#include "../../DataStructures/Lists/linkedList.h"
#include "../../DataStructures/Trees/redBlackTree.h"
#include "../../DataStructures/Trees/redBlackTreeDLL.h"
#include "../../DataStructures/simplex.h"
#include "../../DataStructures/polygon.h"
#include "../../DataStructures/LookUpTables/LUTRBTDLL.h"
#include "../../Utilities/utilities.h"



typedef struct Partition
{
    Point minCoordinates;
    Point maxCoordinates;

    redBlackTree *vertices;
    redBlackTree *globalVertices;
#if REDBLACKTREEDLL == 1
    redBlackTreeDLL *triangles;
#elif REDBLACKTREEDLL == 2
    LUTRBTDLL *triangles;
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


long long serialDT(UserOptions *options);
void computeDelaunayTriangulation(Partition *partition, UserOptions *options);

void generateInitialMesh(Partition *partition, int nParticles, UserOptions *options);


void insertPoint(PointId *point, Partition *partition);

void calculateCircumcircle(Simplex *simplex);

double squareOfDistanceFromPointToLine(Point point, Point point1, Point point2);
double squareOfDistanceFromPointToPoint(Point point1, Point point2);

void changePointsInSimplex(PointId *points, void *pointer);


void theMostNewInsertPoint(PointId *point, Partition *partition, UserOptions *options);
PointId **combination(PointId *data, int n);
void printRedBlackTree(redBlackTree *tree);
void printRedBlackTreeString(redBlackTree *tree, char *(*printData)(void *));
void printRedBlackTreeDLLString(redBlackTreeDLL *tree, char *(*printData)(void *));

void initializePartition(Partition *partition, UserOptions *options);
void freePartition(Partition *partition);

Simplex *findFirstSimplexToModify(PointId *point, Partition *partition, UserOptions *options);
Simplex *findFirstSimplexToModifyPoint(Point *point, Partition *partition, UserOptions *options);
// Simplex *findFirstSimplexToModifyBoxId(PointId *point, Partition *partition, int hilbertDimension);
// Simplex *findFirstSimplexToModifyBoxId2(PointId *point, Partition *partition, int hilbertDimension);
LinkedList *findTrianglesToModify(Simplex *simplex, PointId *point);
LinkedList *findTrianglesToModifyPoint(Simplex *simplex, Point *point);
LinkedList *findTrianglesToModifyPointMonteCarlo(Simplex *simplex, Point *point, UserOptions *options);
LinkedList *findTrianglesToModifyPointMonteCarlo2(Simplex *simplex, Point *point, UserOptions *options);
PolygonList *findPolygon(PointId *point, Partition *partition, LinkedList *trianglesToModify);
redBlackTree *createTreeOfEdgeOfEdges(PolygonList *edges);
void uploadInformationsAboutNeighborsInEdges(PolygonList *edges, redBlackTree *treeEdgeOfEdges);
LinkedList *createSimplexList(PolygonList *edges, PointId *point, UserOptions *options, Partition *partition);
void updateAndAddSimplexes(PolygonList *edges, Partition *partition);

#endif