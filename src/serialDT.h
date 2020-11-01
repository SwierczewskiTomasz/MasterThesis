#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "dataStructure.h"

#ifndef NO_DIM
#define NO_DIM 2
#endif

typedef struct Point
{
    double x;
    double y;
#if NO_DIM==3
    double z;
#endif
} Point;

typedef struct PointId
{
    unsigned long id;
    Point point;
} PointId;

typedef struct Triangle
{
    unsigned long id;
    //Center point of circumcircle
    Point circumcenter;
    double circumradius;
    PointId vertices[NO_DIM + 1];
} Triangle;

typedef struct Tetrahedron
{
    unsigned long id;
    //Center point of circumsphere
    Point circumcenter;
    double circumradius;
    PointId vertices[NO_DIM + 1];
} Tetrahedron;

typedef struct Simplex
{
#if NO_DIM==2
    Triangle object;
#else
    Tetrahedron object;
#endif
} Simplex;

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
void generateInitialMesh(Partition *partition);
double comparePositionOfTwoPoints(void *a, void *b);
void computeDelaunayTriangulation(Partition *partition);
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