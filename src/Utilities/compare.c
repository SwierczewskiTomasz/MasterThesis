#include "compare.h"
#include "../oneHeaderToRuleThemAll.h"

double comparePositionOfTwoTrianglesBox(void *a, void *b)
{
    Simplex *s1 = (Simplex *)a;
    Simplex *s2 = (Simplex *)b;

    double result = 0.0;

    for (int i = 0; i < NO_DIM; i++)
    {
        result = s1->boxId[i] - s2->boxId[i];
        if (result != 0)
            return result;
    }

    result = s1->circumcenter.coords[0] + s1->circumradius - (s2->circumcenter.coords[0] + s2->circumradius);

    if (result == 0)
        return pointsArrayEquals(s1->vertices, s2->vertices, NO_DIM + 1);
    return result;
}

double comparePositionOfTwoTrianglesBox2(void *a, void *b)
{

    Simplex *s1 = (Simplex *)a;
    Simplex *s2 = (Simplex *)b;

    double result;

    for (int i = 0; i < NO_DIM; i++)
    {
        result = s1->boxId[i] - s2->boxId[i];
        if (result != 0)
            return result;
    }

    return result;
}

double comparePointers(void *a, void *b)
{
    return (double)((long *)a - (long *)b);
}

double comparePoints(Point p1, Point p2)
{
    for (int i = 0; i < NO_DIM; i++)
    {
        double result = p1.coords[i] - p2.coords[i];
        if (result != 0)
            return result;
    }

    return 0;
}

double comparePointsVoids(void *p1, void *p2)
{
    PointId *point1 = (PointId *)p1;
    PointId *point2 = (PointId *)p2;
    int id1 = point1->id % 1024;
    int id2 = point2->id % 1024;
    if(id1 - id2 == 0)
        return comparePoints(point1->point, point2->point);
    return (double)(id1-id2);
}

double comparePositionOfTwoTrianglesZCurve(void *a, void *b)
{
    Simplex *s1 = (Simplex *)a;
    Simplex *s2 = (Simplex *)b;

    double result = 0.0;

    result = s1->ZCurveId - s2->ZCurveId;

    if (result != 0)
        return result;

    // result = s1->circumcenter.coords[0] + s1->circumradius - (s2->circumcenter.coords[0] + s2->circumradius);

    result = comparePoints(s1->centroid, s2->centroid);

    if (result == 0)
        result = comparePoints(s1->circumcenter, s2->circumcenter);

    if (result == 0)
        return pointsArrayEquals(s1->vertices, s2->vertices, NO_DIM + 1);
    return result;
}

