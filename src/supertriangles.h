#ifndef SUPERTRIANGLES_H
#define SUPERTRIANGLES_H

#include "constants.h"
#include "serialDT.h"


void supertriangles(Partition *partition, int hilbertDimension);
void supertriangles2D(Partition *partition, int hilbertDimension);
void supertriangles3D(Partition *partition, int hilbertDimension);
void supertriangles4DAndMore(Partition *partition, int hilbertDimension);

#endif