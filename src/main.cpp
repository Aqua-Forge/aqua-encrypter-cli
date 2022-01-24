#include "CLIParser.hpp"
#include "Encrypter.hpp"


int main(int argc, char const *argv[])
{
    Encrypter encrypter;
    CLIParser parser(encrypter.getOptions());

    try {
        parser.parse(argc, argv);
        parser.execute();
    }
    catch (std::string err) {
        std::cerr << err << std::endl;
        exit(1);
    }

    return 0;
}
