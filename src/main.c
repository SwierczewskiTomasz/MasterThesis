#include "DT/serialDT.h"
#include <stdio.h>
#include "IO/userOptions.h"

void podziel2pliki()
{
    FILE *fp, *fp2, *fps;
    fp = fopen("../wyniki/ccg_dtfe_256.a_den", "r");
    fp2 = fopen("../data/Topolski/test_dtfe256.a_den", "r");
    fps = fopen("../wyniki/porownanie.a_den", "w+");

    int result = 1;
    while (result != EOF)
    {
        double d1;
        double d2;
        result = fscanf(fp, "%lf", &d1);
        result = fscanf(fp2, "%lf", &d2);

        fprintf(fps, "%e\n", d2/d1);
    }
    fclose(fp);
    fclose(fp2);
    fclose(fps);
}

void porownaj2pliki()
{
    FILE *fp, *fp2;
    fp = fopen("out/DT_output_3.txt", "r");
    fp2 = fopen("out/CGAL_DT_output_2.txt", "r");

    char* result1 = " ", result2 = " ";

    int count = 1;
    int errors = 0;

    while(result1 != NULL && result2 != NULL)
    {
        count++;

        char c[1000], c2[1000];

        result1 = fgets(c, 1000, fp);
        result2 = fgets(c2, 1000, fp2);
        
        if(strcmp(c, c2) != 0)
        {
            if(errors == 0)
            {
                result2 = fgets(c2, 1000, fp2);
                result2 = fgets(c2, 1000, fp2);
            }
            else if(errors == 1)
            {
                result1 = fgets(c, 1000, fp);
            }
            else if(errors == 2)
            {
                result2 = fgets(c2, 1000, fp2);
            }
            else if(errors <= 4)
            {
                result1 = fgets(c, 1000, fp);
            }
            else if(errors == 5)
            {
                result2 = fgets(c2, 1000, fp2);
            }
            else if(errors == 6)
            {
                result1 = fgets(c, 1000, fp);
            }
            else if(errors < 100)
            {
                printf("Pliki różne w %i linijce. \n%s\n%s\n", count, c, c2);
            }
            else if(errors == 100)
            {
                printf("Kolejne błędy nie będą wypisywane. \n");
            }
            errors++;
        }
    }

    if(result1 != NULL || result2 != NULL)
    {
        printf("Nie wczytano wszystkich linijek z któregoś pliku. \n");
    }

    printf("Sprawdzono %i linijek, znaleziono %i błędów. \n", count, errors);
    fclose(fp);
    fclose(fp2);
}

int main(int argc, char **argv)
{
    UserOptions *options = readUserOptions(argc, argv);
    printUserOptions(options);

    porownaj2pliki();

    // testTIPP(options);
    // podziel2pliki();

    // serialDT();

    // printInformationsAboutSizeOfStructures();

    // readInputFile();

    // int n = 0;
    // for (int i = 0; i < 100; i++)
    // {
    //     printf("i: %d, n: %d\n", i, n);
    //     n = generateNextTestNumberOfPoints(n);
    // }

    // printf("%d \n", -1 % 4);

    // testRedBlackTree();
    // testDoubleLinkedList();

    // printf("int: %i\n", sizeof(int));
    // printf("long: %i\n", sizeof(long));
    // printf("double: %i\n", sizeof(double));
    // printf("float: %i\n", sizeof(float));
    // printf("void*: %i\n", sizeof(void*));
    // printf("Point: %i\n", sizeof(Point));
    // printf("int[3]: %i\n", sizeof(int[3]));
    // printf("Simplex*[3]: %i\n", sizeof(struct Simplex*[3]));

    // printHilbertCurve(1, "./out/Hilbert_1.txt");
    // printHilbertCurve(2, "./out/Hilbert_2.txt");
    // printHilbertCurve(4, "./out/Hilbert_3.txt");
    // printHilbertCurve(8, "./out/Hilbert_4.txt");
    // printHilbertCurve(16, "./out/Hilbert_5.txt");
    // printHilbertCurve(32, "./out/Hilbert_6.txt");
    // printHilbertCurve(64, "./out/Hilbert_7.txt");

    return 0;
}

