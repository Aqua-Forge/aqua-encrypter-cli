#include "CLIParser.hpp"


int main(int argc, char const *argv[])
{
    CLIParser parser(argc, argv);

    try {
        parser.parse();
        parser.execute();
    }
    catch (std::string err) {
        std::cerr << err << std::endl;
        exit(1);
    }

    return 0;
}
