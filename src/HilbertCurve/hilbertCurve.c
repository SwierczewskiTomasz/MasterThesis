#include "hilbertCurve.h"
#include <math.h>

//rotate/flip a quadrant appropriately
void hilbertCurveRotation(int n, int *x, int *y, int rx, int ry)
{
    if (ry == 0)
    {
        if (rx == 1)
        {
            *x = n - 1 - *x;
            *y = n - 1 - *y;
        }

        //Swap x and y
        int t = *x;
        *x = *y;
        *y = t;
    }
}

int hilbertCurveXY2D(int n, int x, int y)
{
    int rx, ry, s, d = 0;
    for (s = n / 2; s > 0; s /= 2)
    {
        rx = (x & s) > 0;
        ry = (y & s) > 0;
        d += s * s * ((3 * rx) ^ ry);
        hilbertCurveRotation(n, &x, &y, rx, ry);
    }
    return d;
}

void hilbertCurveD2XY(int n, int d, int *x, int *y)
{
    int rx, ry, s, t = d;
    *x = *y = 0;
    for (s = 1; s < n; s *= 2)
    {
        rx = 1 & (t / 2);
        ry = 1 & (t ^ rx);
        hilbertCurveRotation(s, x, y, rx, ry);
        *x += s * rx;
        *y += s * ry;
        t /= 4;
    }
}

int hilbertCurveDoubleXY2D(int n, double x, double y, double xmin, double xmax, double ymin, double ymax)
{
    double rx = (x - xmin) / (xmax - xmin);
    double ry = (y - ymin) / (ymax - ymin);
    rx = (rx * 2 * n - 1) / 2;
    ry = (ry * 2 * n - 1) / 2;
    rx = round(rx);
    ry = round(ry);
    return hilbertCurveXY2D(n, x, y);
}

void hilbertCurveD2DoubleXY(int n, int d, double *x, double *y, double xmin, double xmax, double ymin, double ymax)
{
    int ix, iy;
    hilbertCurveD2XY(n, d, &ix, &iy);
    double rx = (ix * 2 + 1) / (2.0 * n);
    double ry = (iy * 2 + 1) / (2.0 * n);
    rx = rx * (xmax - xmin) + xmin;
    ry = ry * (ymax - ymin) + ymin;
    
    *x = rx;
    *y = ry;
}