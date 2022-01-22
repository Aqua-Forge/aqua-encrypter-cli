#include "CLIParser.hpp"


CLIParser::CLIParser(int argc, const char* argv[])
{
    this->argc = argc;

    for (int i = 0; i < argc; i++)
        this->argv.push_back(argv[i]);

    this->parameters['d'] = (Parameter) {
        'd',
        "decrypt",
        "Uses the decrypt mode. The INPUT_FILENAME must be the ciphertext.",
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
    std::cout << "The encryption algorithm uses a variation of the" << std::endl;
    std::cout << "Vignère cipher, where the key (password) is repeated" << std::endl;
    std::cout << "untill a text-sized key is obtained. Then, their" << std::endl;
    std::cout << "position matched characters are added, as long with" << std::endl;
    std::cout << "a salt, in order to generate the ciphertext. And" << std::endl;
    std::cout << "this process is repeated if more than one key is" << std::endl;
    std::cout << "provided.\n" << std::endl;
    std::cout << "Safety tips:\n" << std::endl;
    std::cout << "Your ciphertext will be more secure if you user more" << std::endl;
    std::cout << "than one password layer. As well, a dictionary-" << std::endl;
    std::cout << "assisted bruteforce attack can be frustrated if" << std::endl;
    std::cout << "random characters are inserted in the middle of your" << std::endl;
    std::cout << "plaintext. Lastly, the longer your key(s), the more" << std::endl;
    std::cout << "secure your cipher will be." << std::endl;
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
        std::cout << "\n\n\t\t" << it->second.description << "\n\n";
    }
}
