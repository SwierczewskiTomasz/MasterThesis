#ifndef SIMPLEX_H
#define SIMPLEX_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "points.h"
#include "../HilbertCurve/hilbertCurve.h"
#include "LookUpTables/blockSizeArray.h"
#include "../IO/userOptions.h"
#include "LookUpTables/ZCurveLUT.h"

typedef struct Simplex
{
#if ID == 1
    ID_TYPE id;
#endif
    /**
     * Center point of circumcircle of circumsphere (or other things in other dimensions)
     */
    Point circumcenter;
    double circumradius;
    Point centroid;
    PointId *vertices[NO_DIM + 1];
    int hilbertId;
    int hilbertDimension;

    int boxId[NO_DIM];
    BLOCK_TYPE ZCurveId;

    struct Simplex *neighbors[NO_DIM + 1];
} Simplex;


Simplex *neighborOfSimplex(Simplex *simplex, int i);

#if REDBLACKTREEDLL == 2
void createNewSimplex(Simplex *result, PointId *points[NO_DIM + 1], UserOptions *options, ZCurveLUT *LUT);
#else
void createNewSimplex(Simplex *result, PointId *points[NO_DIM + 1], UserOptions *options);
#endif
void createNewSimplexToSearch(Simplex *simplex, Point *point, UserOptions *options);
void freeSimplex(void *s);

void calculateCircumcircle(Simplex *simplex);
void calculateCircumcircleGSL(Simplex *simplex);
void sortPointsInSimplex(Simplex *simplex);
void sortPointsInSimplex1(Simplex *simplex);

void calculateBoxId(Simplex *result, UserOptions *options);

#endif