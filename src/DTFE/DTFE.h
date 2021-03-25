#ifndef DTFE_H
#define DTFE_H

#include "../DT/serialDT.h"

typedef struct BarycentricCoordinates
{
    FLOATING_POINT_PRECISION coords[NO_DIM + 1];
} BarycentricCoordinates;

long long DTFE(Partition *partition);
void calculateDensityInEachVertex(Partition *partition);
void calculateVolumeInEachSimplex(Partition *partition);
void addVolumeToEachVertexInSimplex(Simplex *simplex);
double CayleyMengerDeterminant(Simplex *simplex);
double CayleyMengerDeterminant2(Simplex *simplex);
double interpolation(Simplex *simplex, BarycentricCoordinates *barycentric);
bool checkIfInsideSimplex(BarycentricCoordinates *barycentric);
BarycentricCoordinates* calculateBarycentricCoordinates(Simplex *simplex, PointWithDensity *point);
bool calculatePointDensity(Partition *partition, PointWithDensity *point);

#endif