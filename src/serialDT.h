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


typedef struct Set
{
    //It can be for example LinkedList, DoubleLinkedList or Binary Tree and other
    void *set;
} Set;

typedef struct Partition
{
    Point minCoordinates;
    Point maxCoordinates;
    DoubleLinkedList *vertices;
    DoubleLinkedList *triangles;
} Partition;

typedef struct DelaunayTriangulation
{
    Partition *partitions;
} DelaunayTriangulation;

void TIPP();
void generateInitialMesh(Partition *partition, int nParticles);
double comparePositionOfTwoPoints(void *a, void *b);
void computeDelaunayTriangulation(Partition *partition, int stopAtStep);
void insertPoint(PointId *point, Partition *partition);
void createNewSimplex(Simplex *simplex, PointId points[NO_DIM + 1]);
double pointInsideCircumcircle(Point point, PointId points[NO_DIM + 1]);
void calculateCircumcircle(Simplex *simplex);
double squareOfDistanceFromPointToLine(Point point, Point point1, Point point2);
#if NO_DIM == 3
double squareOfDistanceFromPointToPlane(Point point, Point point1, Point point2, Point point3);
#endif
double squareOfDistanceFromPointToPoint(Point point1, Point point2);


double comparePositionOfTwoTriangles(void *a, void *b);
void changePointsInSimplex(PointId *points, void *pointer);


void newInsertPoint(PointId *point, Partition *partition);
PointId** combination(PointId* data, int n);
void printRedBlackTree(redBlackTree *tree);

#endif