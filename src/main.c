#include <stdio.h>
#include "oneHeaderToRuleThemAll.h"
#include "IO/userOptions.h"

int main(int argc, char **argv)
{
    UserOptions *options = readUserOptions(argc, argv);
    printUserOptions(options);

    testTIPP(options);

    if(options->printSizeOfStructures)
        printInformationsAboutSizeOfStructures();

    return 0;
}
