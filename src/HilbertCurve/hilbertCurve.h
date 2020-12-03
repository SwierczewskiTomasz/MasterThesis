#ifndef HILBERTCURVE_H
#define HILBERTCURVE_H

int hilbertCurveXY2D (int n, int x, int y);
void hilbertCurveD2XY(int n, int d, int *x, int *y);
int hilbertCurveDoubleXY2D(int n, double x, double y, double xmin, double xmax, double ymin, double ymax);
void hilbertCurveD2DoubleXY(int n, int d, double *x, double *y, double xmin, double xmax, double ymin, double ymax);

#endif