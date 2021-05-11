#ifndef IO_H
#define IO_H

#include "../DT/standardDT/serialDT.h"

int asciiLoad(char *filename, Partition *partition);
int asciiLoad2(char *filename, Partition *partition, UserOptions *options);
int asciiLoad3(char *filename, Partition *partition, UserOptions *options);

int loadDT(UserOptions *options, Partition *partition);
int saveDT(UserOptions *options, Partition *partition);
void saveDTFEToTextFile(UserOptions *options, Partition *partition);
void saveDTFEToBinaryFile(UserOptions *options, Partition *partition);

#endif