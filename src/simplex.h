#ifndef SIMPLEX_H
#define SIMPLEX_H

#ifndef NO_DIM
#define NO_DIM 2
#endif


#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "DataStructures/dataStructure.h"

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
    unsigned long id;
    //Center point of circumsphere
    Point circumcenter;
    double circumradius;
    PointId vertices[NO_DIM + 1];
} Simplex;

#endif