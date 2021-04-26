#include "userOptions.h"
#include "string.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

UserOptions *readUserOptions(int argc, char **argv)
{
    UserOptions *result = (UserOptions *)malloc(sizeof(UserOptions));

    result->onlyDT = false;
    result->onlyDTFE = false;
    result->MonteCarlo = false;
    result->nMonteCarlo = 100;
    result->gridSize = 0;
    result->PHgridSize = 0;
    result->massInSuperpoints = 1;

    for (int i = 1; i < argc; i++)
    {
        if (!strcmp(argv[i], "--input"))
        {
            i++;
            result->inputFilename = argv[i];
        }
        else if (!strcmp(argv[i], "--output"))
        {
            i++;
            result->outputFilename = argv[i];
        }
        else if (!strcmp(argv[i], "--DTinput"))
        {
            i++;
            result->DTinputFilename = argv[i];
        }
        else if (!strcmp(argv[i], "--DToutput"))
        {
            i++;
            result->DToutputFilename = argv[i];
        }
        else if (!strcmp(argv[i], "--onlyDT"))
        {
            result->onlyDT = true;
        }
        else if (!strcmp(argv[i], "--onlyDTFE"))
        {
            result->onlyDTFE = true;
        }
        else if (!strcmp(argv[i], "--grid"))
        {
            i++;
            result->gridSize = atoi(argv[i]);
        }
        else if (!strcmp(argv[i], "--PHgrid"))
        {
            i++;
            result->PHgridSize = atoi(argv[i]);
        }
        else if (!strcmp(argv[i], "--region"))
        {
            i++;
            for (int j = 0; j < NO_DIM; j++)
            {
                result->minMaxCoords[j][0] = atof(argv[i]);
                result->minMaxCoords[j][1] = atof(argv[i + 1]);
                i += 2;
            }
            i--;
        }
        else if (!strcmp(argv[i], "--regionMpc"))
        {
            i++;
            for (int j = 0; j < NO_DIM; j++)
            {
                result->minMaxCoords[j][0] = atof(argv[i]);
                result->minMaxCoords[j][1] = atof(argv[i + 1]);
                i += 2;
            }
            i--;
        }
        else if (!strcmp(argv[i], "--regionkpc"))
        {
            i++;
            for (int j = 0; j < NO_DIM; j++)
            {
                result->minMaxCoords[j][0] = atof(argv[i]);
                result->minMaxCoords[j][1] = atof(argv[i + 1]);
                i += 2;
            }
            i--;
        }
        else if (!strcmp(argv[i], "--help"))
        {
            printHelp();
            free(result);
            return NULL;
        }
        else if (!strcmp(argv[i], "--massInSuperpoints"))
        {
            i++;
            result->massInSuperpoints = atof(argv[i]);
        }
        else if (!strcmp(argv[i], "--monteCarlo"))
        {
            result->MonteCarlo = true;
        }
        else if (!strcmp(argv[i], "--nMonteCarlo"))
        {
            i++;
            result->nMonteCarlo = atoi(argv[i]);
        }
        else
        {
            printf("Argument not recognized, please read help (use --help). Argument: %s \n", argv[i]);
        }
    }

    result->diameterOfGrid = 0;

    for (int i = 0; i < NO_DIM; i++)
    {
        double temp = (result->minMaxCoords[i][1] - result->minMaxCoords[i][0]) / result->gridSize / 2;
        result->diameterOfGrid += temp * temp;
    }

    result->diameterOfGrid = pow(result->diameterOfGrid, 0.5);

    return result;
}

void printHelp()
{
    // DTFE --input inputFileName --output outputFileName --grid 256 --regionKpc 0 1000000 0 1000000 0 1000000

    // Opcje do zaprogramowania:
    // --input inputFileName
    // --output outputFileName
    // --DToutput
    // --DTinput
    // --onlyDT - domyślnie false
    // --onlyDTFE - domyślnie false
    // --grid 256
    // --PHgrid 256
    // --region x_min x_max y_min y_max z_min z_max
    // --regionkpc x_min x_max y_min y_max z_min z_max
    // --regionMpc x_min x_max y_min y_max z_min z_max

    // Reguły:
    // Jeśli --onlyTesselation, to powinno być użyte co najmniej --input oraz --DToutput.
    // Jeśli --onlyDTFE, to powinno być podane co najmniej --DTinput oraz --output
    // Jeśli nie ma żadnych tych dodatkowych opcji, to musi być co najmniej --input i --output. Jeśli jest podany też --DToutput, to zostanie zapisany wynik triangulacji.
}

void printUserOptions(UserOptions *options)
{
    printf("Options: \n");
    printf("Input filename: %s \n", options->inputFilename);
    printf("Output filename: %s \n", options->outputFilename);
    printf("DT input filename: %s \n", options->DTinputFilename);
    printf("DT output filename: %s \n", options->DToutputFilename);
    printf("grid size: %d \n", options->gridSize);
    printf("PH grid size: %d \n", options->PHgridSize);
    printf("Only DT: %s \n", options->onlyDT ? "True" : "False");
    printf("Only DTFE: %s \n", options->onlyDTFE ? "True" : "False");
    printf("MinMax Coords: ");
    for (int i = 0; i < NO_DIM; i++)
    {
        printf("[%i]: %f, %f  ", i, options->minMaxCoords[i][0], options->minMaxCoords[i][1]);
    }
    printf("\n");
    printf("Mass in superpoints: %f\n", options->massInSuperpoints);
    printf("Monte Carlo: %s \n", options->MonteCarlo ? "True" : "False");
    printf("n samples in Monte Carlo: %i \n", options->nMonteCarlo);
    printf("Diameter of grid: %f\n", options->diameterOfGrid);
}