#ifndef DATA_STRUCTURE_H
#define DATA_STRUCTURE_H

#include "../constants.h"

/**
 * Point - contains only coordinates of the point. 
 * To modify floating point precision of coords or number of dimensions, see constants.h file.
 */
typedef struct Point
{
    FLOATING_POINT_PRECISION coords[NO_DIM];
} Point;

typedef struct PointWithDensity
{
    FLOATING_POINT_PRECISION coords[NO_DIM];
    FLOATING_POINT_PRECISION density;

    // Below variables for counting statistics for Monte-Carlo method.
    // int onList;
    // int onListNoneZero;
} PointWithDensity;

typedef struct PointId
{
#if ID == 1
    ID_TYPE id;
#endif
    Point point;
    int count;
    double density;
    double mass;
    FLOATING_POINT_PRECISION velocity[NO_DIM];
} PointId;

PointId* newPointId2D(FLOATING_POINT_PRECISION x, FLOATING_POINT_PRECISION y);
PointId* newPointId3D(FLOATING_POINT_PRECISION x, FLOATING_POINT_PRECISION y, FLOATING_POINT_PRECISION z);
PointId* newPointId(FLOATING_POINT_PRECISION coords[NO_DIM]);
PointId *newEmptyPointId();

#endif