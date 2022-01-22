#include "CLIParser.hpp"


CLIParser::CLIParser(int argc, const char* argv[])
{
    this->argc = argc;

    for (int i = 0; i < argc; i++)
        this->argv.push_back(argv[i]);

    this->parameters['d'] = (Parameter) {
        'd',
        "decrypt",
        "Activate decrypt mode.",
        false,
        "",
    };
    this->parameters['h'] = (Parameter) {
        'h',
        "help",
        "Display this help.",
        false,
        "",
    };
    this->parameters['l'] = (Parameter) {
        'l',
        "levels",
        "The number 'n' (integer) of password layers for encryption.",
        true,
        "n"
    };
    this->parameters['o'] = (Parameter) {
        'o',
        "out",
        "Output filename. (Default is crytped or decrypted)",
        true,
        "filename"
    };
}


CLIParser::~CLIParser() {}


void CLIParser::printArgs()
{
    std::cout << "Arg Count: " << this->argc << std::endl;
    std::cout << "Args: " << std::endl;

    for (int i = 0; i < this->argc; i++)
        std::cout << "    " << this->argv[i] << std::endl;
}


void CLIParser::printHeader()
{
    std::cout << "Copyright (c) 2021 Aqua Forge" << std::endl;
    std::cout << "Aqua-Encrypter-CLI - Command line file encrypter v1.0" << std::endl;
    std::cout << "=====================================================" << std::endl;
    std::cout << "How it works:\n" << std::endl;
    std::cout << "The encryption algorithm uses the Vignère cipher," << std::endl;
    std::cout << "where the key (password) is repeated untill a text-" << std::endl;
    std::cout << "sized key is obtained. Then, their position matched" << std::endl;
    std::cout << "characters are added, as long with a salt, in order" << std::endl;
    std::cout << "to generate the ciphertext." << std::endl;
    std::cout << "=====================================================" << std::endl;
}


void CLIParser::printHelp()
{
    std::cout << "Usage:" << std::endl;
    std::cout << "\taqua-encrypter [-o | --option=value] INPUT_FILENAME\n" << std::endl;

    std::cout << "If no option is submitted, the encryption function is considered.\n" << std::endl;

    std::cout << "Options:" << std::endl;
    std::map<char, Parameter>::iterator it = this->parameters.begin();
    for (; it != this->parameters.end(); ++it) {
        std::cout << "\t-" << it->second.flag << " ";
        if (it->second.hasValue)
            std::cout << it->second.value << " ";
        std::cout << "| --" << it->second.flagName;
        if (it->second.hasValue)
            std::cout << "=" << it->second.value;
        std::cout << " : " << it->second.description << std::endl;
    }
}
