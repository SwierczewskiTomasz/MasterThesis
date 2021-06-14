#ifndef USEROPTIONS_H
#define USEROPTIONS_H

#include "../constants.h"
#include "stdbool.h"

typedef struct UserOptions
{
    char *inputFilename;
    char *outputFilename;
    char *DTinputFilename;
    char *DToutputFilename;

    int inputFormat;
    int outputFormat;
    int DTinputFormat;
    int DToutputFormat;

    int gridSize;
    int PHgridSize;

    double minMaxCoords[NO_DIM][2];

    bool onlyDT;
    bool onlyDTFE;

    double massInSuperpoints;
    int nMonteCarlo;
    bool MonteCarlo;

    int points;
    bool printSizeOfStructures;

    // When 0 - binary, when 1 - text
    int saveFileType;

    double diameterOfGrid;
} UserOptions;

UserOptions *readUserOptions(int argc, char **argv);
void printHelp();
void printUserOptions(UserOptions *options);

#endif