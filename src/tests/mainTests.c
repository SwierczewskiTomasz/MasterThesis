#include "mainTests.h"

int main(int argc, char **argv)
{
    // TIPP();

    // int n = 0;
    // for (int i = 0; i < 100; i++)
    // {
    //     printf("i: %d, n: %d\n", i, n);
    //     n = generateNextTestNumberOfPoints(n);
    // }

    // printf("%d \n", -1 % 4);

    // testRedBlackTree();
    // testDoubleLinkedList();
    // printInformationsAboutSizeOfStructures();

    int testsCounter = 1;
    testRedBlackTree(&testsCounter);
    return 0;
}