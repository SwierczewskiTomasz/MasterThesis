#ifndef SIMPLEX_H
#define SIMPLEX_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "DataStructures/dataStructure.h"
#include "HilbertCurve/hilbertCurve.h"
#include "myMath.h"

typedef struct Simplex
{
#if ID == 1
    ID_TYPE id;
#endif
    //Center point of circumcircle of circumsphere (or other things in other dimensions)
    Point circumcenter;
    double circumradius;
    PointId *vertices[NO_DIM + 1];
    int hilbertId;
    int hilbertDimension;
    // Edge edges[NO_DIM + 1];

    int boxId[NO_DIM];

    struct Simplex *neighbors[NO_DIM + 1];
} Simplex;

// PointId cw(Simplex *simplex, PointId vertex);
// PointId ccw(Simplex *simplex, PointId vertex);
// PointId cw_i(Simplex *simplex, int i);
// PointId ccw_i(Simplex *simplex, int i);
// Edge neighbor(Simplex *simplex, PointId vertex);
// Edge neighbor_i(Simplex *simplex, int i);

Simplex *neighborOfSimplex(Simplex *simplex, int i);

void createNewSimplex(Simplex *simplex, PointId *points[NO_DIM + 1], int hilbertDimension);
void freeSimplex(void *s);

void calculateCircumcircle(Simplex *simplex);
void sortPointsInSimplex(Simplex *simplex);
double comparePoints(Point p1, Point p2);
double comparePointsVoids(void *p1, void *p2);

void calculateBoxId(Simplex *result);

char* printLongSimplex(Simplex *simplex);
#if ID == 1
char* printShortSimplex(Simplex *simplex);
#endif 

#endif