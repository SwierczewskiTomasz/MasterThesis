#ifndef LUTDT_H
#define LUTDT_H

#include <stdarg.h>
#include "../standardDT/serialDT.h"
#include "../../DataStructures/LookUpTables/ZCurveLUT.h"
#include "../../DataStructures/LookUpTables/blockSizeArray.h"

BLOCK_TYPE calculateZCurveId(ZCurveLUT *LUT, Point *point, UserOptions *options);
Simplex *findFirstSimplexToModifyLUT(PointId *point, Partition *partition, UserOptions *options);
Simplex *findFirstSimplexToModifyLUTPoint(Point *point, Partition *partition, UserOptions *options);

#endif