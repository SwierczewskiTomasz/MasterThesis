#ifndef SUPERTRIANGLES_H
#define SUPERTRIANGLES_H

#include "../constants.h"
#include "../DT/standardDT/serialDT.h"


void supertriangles(Partition *partition, UserOptions *options);
void supertriangles2D(Partition *partition, UserOptions *options);
void supertriangles3D(Partition *partition, UserOptions *options);
void supertriangles4DAndMore(Partition *partition, UserOptions *options);

#endif