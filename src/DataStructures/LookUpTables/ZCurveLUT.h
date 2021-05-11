#ifndef ZCURVELUT_H
#define ZCURVELUT_H

#include "blockSizeArray.h"

typedef struct ZCurveLUT
{
    BLOCK_TYPE** data;
} ZCurveLUT;

ZCurveLUT *generateZCurveLUT(int size);
void printZCurveLUT(ZCurveLUT *LUT, int size);
BLOCK_TYPE getZCurveKey(ZCurveLUT *LUT, int argc, ...);

#endif