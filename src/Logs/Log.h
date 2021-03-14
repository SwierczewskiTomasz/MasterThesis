#ifndef LOG_H
#define LOG_H

#include "../DT/serialDT.h"
#include <stdio.h>

char *printLongPoint(void *data);
char* printLongPointId(void *data);

char* printLongEdge(void *data);
char* printShortEdge(void *data);

char* printLongEdgeOfEdge(void *data);
char* printShortEdgeOfEdge(void *data);

char* printLongSimplex(void *data);
char* printShortSimplex(void *data);

void saveToLogs(char* file, int line, char* additionalInformation, char* (*printData)(void *), void* data);
void saveToLogsWithFormat(char *file, int line, const char *additionalInformationFormat, ...);
void saveToLogsWithFormatWithData(char *file, int line, char *(*printData)(void *), void *data, const char *additionalInformationFormat, ...);
#endif