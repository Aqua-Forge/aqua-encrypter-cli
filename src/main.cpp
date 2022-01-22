#include "CLIParser.hpp"


int main(int argc, char const *argv[])
{
    CLIParser parser(argc, argv);
    parser.printHeader();
    parser.printHelp();

    return 0;
}
