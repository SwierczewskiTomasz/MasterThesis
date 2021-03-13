#ifndef LOG_H
#define LOG_H

#include "../DT/serialDT.h"
#include <stdio.h>

char *printLongPoint(Point point);
char* printLongPointId(PointId *point);

char* printLongEdge(Edge *edge);
char* printShortEdge(Edge *edge);

char* printLongEdgeOfEdge(EdgeOfEdge *edge);
char* printShortEdgeOfEdge(EdgeOfEdge *edge);

char* printLongSimplex(Simplex *simplex);
char* printShortSimplex(Simplex *simplex);

void saveToLogs(char* file, int line, char* additionalInformation, char* (*printData)(void *), void* data);
#endif