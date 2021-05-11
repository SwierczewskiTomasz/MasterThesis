#ifndef COMPARE_H
#define COMPARE_H

// #include "../oneHeaderToRuleThemAll.h"
#include "../DataStructures/points.h"

double comparePoints(Point p1, Point p2);
double comparePointsVoids(void *p1, void *p2);
double comparePositionOfTwoTrianglesZCurve(void *a, void *b);

double comparePositionOfTwoTrianglesBox(void *a, void *b);
double comparePointers(void *a, void *b);

#endif