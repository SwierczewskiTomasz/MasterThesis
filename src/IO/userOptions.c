#include "userOptions.h"
#include "string.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

UserOptions *readUserOptions(int argc, char **argv)
{
    bool printed = false;

    UserOptions *result = (UserOptions *)malloc(sizeof(UserOptions));

    result->inputFilename = "";
    result->onlyDT = false;
    result->onlyDTFE = false;
    result->MonteCarlo = false;
    result->printSizeOfStructures = false;
    result->nMonteCarlo = 100;
    result->gridSize = 64;
    result->PHgridSize = 64;
    result->massInSuperpoints = 0;
    result->points = -1;
    result->saveFileType = 0;

    for(int i = 0; i < NO_DIM; i++)
    {
        result->minMaxCoords[i][0] = 0;
        result->minMaxCoords[i][1] = 1;
    }

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
        else if (!strcmp(argv[i], "--help"))
        {
            printHelp();
            printed = true;
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
        else if (!strcmp(argv[i], "--points"))
        {
            i++;
            result->points = atoi(argv[i]);
        }
        else if (!strcmp(argv[i], "--printSizeOfStructures"))
        {
            result->printSizeOfStructures = true;
        }
        else if (!strcmp(argv[i], "--saveFileType"))
        {
            i++;
            result->saveFileType = atoi(argv[i]);
        }
        else
        {
            printf("Argument not recognized, please read help (use --help). Argument: %s \n\n", argv[i]);
            if(!printed)
            {
                printHelp();
                printed = true;
            }
        }
    }

    if(strcmp(result->inputFilename, "") == 0)
    {
        result->points = 100000;
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

    printf("Help page of program to caculate Delaunay Triangulation and DTFE\n");
    printf("Author: inż. Tomasz Świerczewski, ICM UW\n");
    printf("Supervisor: dr hab., prof. CFT PAN Wojciech Andrzej Hellwing, CFT PAN\n");
    printf("Date: June 2021\n\n");

    printf("User options available in this program: \n\n");
    printf("--input arg - name of input file, which one store cosmological data. Currently only reading from text file. If no input name will be given, data will be randomly selected.\n");
    printf("--output arg - name of output file, where should be stored calculations from DTFE\n");
    printf("--DTinput arg - DT input filename - name of input file with triangulation. Loading should be corrected to preserve information about neighbors. For --onlyDTFE option only.\n");
    printf("--DToutput arg - DT output filename, where should be stored triangulation, for --onlyDT options only.\n");
    printf("--saveFileType arg - save file type. 0 - binary file, 1 - text file.\n\n");
    printf("--grid arg - size of grid for DTFE. Default 64.\n");
    printf("--PHgrid arg - size of grid for DT, to help faster location of points. Default 64.\n");
    printf("--monteCarlo - option to choose Monte-Carlo method to calculate DTFE. Default false.\n");
    printf("--nMonteCarlo arg - number of samples in Monte-Carlo method. Default 100.\n");
    printf("--points arg - number of points, which one should be calculated in Delaunay triangulation. Default all of points from input file, if input file is given, otherwise 100000. It can\
            be used to reduce number of calculated data from file or to rand specific number of data.\n");
    printf("--massInSuperpoints arg - mass in artifical points added to triangulation. Default 0. \n");
    printf("--onlyDT - option to force calculating only Delaunay Triangulation.\n");
    printf("--onlyDTFE - option to force calculating only DTFE, but generate errors due to lack of neighbours information in simplexes.\n\n");
    printf("--help - prints this help\n");
    printf("--printSizeOfStructures - print size of structures used in this implementation.\n");
    printf("\nOther informations: each data readed from file currently are divided by 1024000, to normalize data to range 0-1.\n");
}

void printUserOptions(UserOptions *options)
{
    printf("\nUser options: \n");
    printf("Input filename: %s \n", options->inputFilename);
    printf("Output filename: %s \n", options->outputFilename);
    printf("DT input filename: %s \n", options->DTinputFilename);
    printf("DT output filename: %s \n", options->DToutputFilename);
    printf("Output file type: %s \n\n", options->saveFileType == 0 ? "Binary" : "Text");
    printf("grid size: %d \n", options->gridSize);
    printf("PH grid size: %d \n", options->PHgridSize);

    // printf("MinMax Coords: ");
    // for (int i = 0; i < NO_DIM; i++)
    // {
    //     printf("[%i]: %f, %f  ", i, options->minMaxCoords[i][0], options->minMaxCoords[i][1]);
    // }
    // printf("\n");
    printf("Monte Carlo: %s \n", options->MonteCarlo ? "True" : "False");
    printf("n samples in Monte Carlo: %i \n", options->nMonteCarlo);
    printf("Number of points, which one should be calculated in DT: ");
    if(options->points == -1)
        printf("All of points from input\n");
    else
        printf("%i\n", options->points);
    printf("Mass in superpoints: %f\n", options->massInSuperpoints);
    printf("Only DT: %s \n", options->onlyDT ? "True" : "False");
    printf("Only DTFE: %s \n\n", options->onlyDTFE ? "True" : "False");
    // printf("Diameter of grid: %f\n", options->diameterOfGrid);

    printf("Print size of structures: %s \n", options->printSizeOfStructures ? "True" : "False");
    printf("\n");
}