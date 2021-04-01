#include "userOptions.h"
#include "string.h"
#include <stdlib.h>
#include <stdio.h>

UserOptions *readUserOptions(int argc, char **argv)
{
    UserOptions *result = (UserOptions *)malloc(sizeof(UserOptions));

    result->onlyDT = false;
    result->onlyDTFE = false;

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
        }
        else if (!strcmp(argv[i], "--help"))
        {
            printHelp();
            free(result);
            return NULL;
        }
        else
        {
            printf("Argument not recognized, please read help (use --help). \n");
        }
    }

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
    printf("DT onput filename: %s \n", options->DToutputFilename);
    printf("grid size: %d \n", options->gridSize);
    printf("PH grid size: %d \n", options->PHgridSize);
    printf("Input filename: %s \n", options->onlyDT ? "True" : "False");
    printf("Input filename: %s \n", options->onlyDTFE ? "True" : "False");
    printf("MinMax Coords: ");
    for(int i = 0; i < NO_DIM; i++)
    {
        printf("[%i]: %f, %f  ", i, options->minMaxCoords[i][0], options->minMaxCoords[i][1]);
    }
    printf("\n");
}