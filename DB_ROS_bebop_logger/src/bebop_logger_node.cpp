#include "logger.h"
#include <iostream>


int main(int argc, char** argv)
{
    Logger logger = Logger(argc, argv, "bebop");
    logger.init();

    return 0;
}