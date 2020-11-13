#include <math.h>

int generateNextTestNumberOfPoints(int n)
{
    if (n == 0)
        return 2;
    if (n == 2)
        return 4;
    if (n == 4)
        return 6;
    if (n == 6)
        return 8;
    return n + pow(2, (int)floor(log2((double)n)) - 2);
}