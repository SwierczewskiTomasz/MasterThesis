#include "supertriangles.h"

#ifndef SERIALDT_H
#define SERIALDT_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "polygon.h"
#include "DataStructures/dataStructure.h"
#include "DataStructures/redBlackTree.h"
#include "myMath.h"
#include "simplex.h"
#include "constants.h"
#include "edgeOfEdge.h"
#include "HilbertCurve/hilbertCurve.h"



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
    redBlackTree *triangles;
    redBlackTree *globalVertices;
} Partition;

typedef struct DelaunayTriangulation
{
    Partition *partitions;
} DelaunayTriangulation;

void TIPP(int k, int n, int hilbertDimension);
void generateInitialMesh(Partition *partition, int nParticles, int hilbertDimension);
double comparePositionOfTwoPoints(void *a, void *b);
void computeDelaunayTriangulation(Partition *partition, int stopAtStep, int hilbertDimension);
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
void changePointsInSimplex(PointId *points, void *pointer);
double comparePointers(void *a, void *b);


// void newInsertPoint(PointId *point, Partition *partition);
void theMostNewInsertPoint(PointId *point, Partition *partition, int hilbertDimension);
PointId** combination(PointId* data, int n);
void printRedBlackTree(redBlackTree *tree);
void printRedBlackTreeString(redBlackTree *tree, char* (*printData)(void *));
void printRedBlackTreeTriangles(redBlackTree *tree);
void initializePartition(Partition *partition);
void freePartition(Partition *partition);

Simplex *findFirstSimplexToModify(PointId *point, Partition *partition, int hilbertDimension);
LinkedList *findTrianglesToModify(Simplex *simplex, PointId *point);
PolygonList *findPolygon(PointId *point, Partition *partition, LinkedList *trianglesToModify);
redBlackTree *createTreeOfEdgeOfEdges(PolygonList *edges);
void uploadInformationsAboutNeighborsInEdges(PolygonList *edges, redBlackTree *treeEdgeOfEdges);
LinkedList *createSimplexList(PolygonList *edges, PointId* point, int hilbertDimension);
void updateAndAddSimplexes(PolygonList *edges, Partition *partition);

#endif