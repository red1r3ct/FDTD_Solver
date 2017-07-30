
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "Parser.h"
#include "../Updaters/UpdaterTE.h"
#include "../Grids/GridTE.h"
#include "../Routines/HzOutputRoutineTE.h"

#include <ctime>
#include <cmath>

int main(int argc, char **argv)
{
    Parser parser;
    parser.runFile(argv[1]);

    return 0;
}
