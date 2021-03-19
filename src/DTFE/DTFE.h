#ifndef DTFE_H
#define DTFE_H

#include "../DT/serialDT.h"

long long DTFE(Partition *partition);
void calculateDensityInEachVertex(Partition *partition);
void calculateVolumeInEachSimplex(Partition *partition);
void addVolumeToEachVertexInSimplex(Simplex *simplex);
double CayleyMengerDeterminant(Simplex *simplex);
double CayleyMengerDeterminant2(Simplex *simplex);

#endif