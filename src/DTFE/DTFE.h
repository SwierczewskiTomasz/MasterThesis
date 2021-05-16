#ifndef DTFE_H
#define DTFE_H

// #include "../DT/standardDT/serialDT.h"
#include "../DT/DTUsingLUT/LUTDT.h"

typedef struct BarycentricCoordinates
{
    FLOATING_POINT_PRECISION coords[NO_DIM + 1];
} BarycentricCoordinates;

long long DTFE(Partition *partition, UserOptions *options);
void calculateDensityInEachVertex(Partition *partition);
void calculateVolumeInEachSimplex(Partition *partition);
void addVolumeToEachVertexInSimplex(Simplex *simplex);
double CayleyMengerDeterminant(Simplex *simplex);
double CayleyMengerDeterminant2(Simplex *simplex);
double interpolation(Simplex *simplex, BarycentricCoordinates *barycentric);
bool checkIfInsideSimplex(BarycentricCoordinates *barycentric);
BarycentricCoordinates* calculateBarycentricCoordinates(Simplex *simplex, PointWithDensity *point);
bool calculatePointDensity(Partition *partition, PointWithDensity *point, UserOptions *options);
bool calculatePointDensityMonteCarlo(Partition *partition, PointWithDensity *point, UserOptions *options);

Simplex *findFirstSimplexToModifyLUTPointTest(Point *point, Partition *partition, UserOptions *options);
bool calculatePointDensityTest(Partition *partition, PointWithDensity *point, UserOptions *options);

#endif