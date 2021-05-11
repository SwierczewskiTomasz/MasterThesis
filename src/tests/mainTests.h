#ifndef MAINTESTS_H
#define MAINTESTS_H

#include "testRedBlackTree.h"

int main(int argc, char **argv);

inline static void printTestName(char* text, int test_counter) {
  printf("Test %3i: %s\n", test_counter, text);
}

#endif