#include "Encrypter.hpp"

Encrypter::Encrypter()
{
    this->options['d'] = (Parameter){
        "decrypt",
        "Uses the decrypt mode. The INPUT_FILENAME must be the ciphertext.",
        false,
        "",
        "",
        false,
        [this](std::string value = "")
        {
            this->mode = DECRYPT_MODE;
            if (this->outputFile == "encrypted")
                this->outputFile = "decrypted";
        },
    };

    this->options['h'] = (Parameter){
        "help",
        "Display this help.",
        false,
        "",
        "",
        false,
        [this](std::string value = "")
        {
            this->printHeader();
            this->printHelp();
        },
    };

    this->options['l'] = (Parameter){
        "levels",
        "The number 'num' (integer) of password layers for encryption/decryption.",
        true,
        "num",
        "",
        false,
        [this](std::string value = "")
        {
            try
            {
                this->encryptionLevels = std::stoi(value);
            }
            catch (std::invalid_argument err)
            {
                throw "Invalid input \"" + value + "\": encryption levels must be a integer.";
            }
            if (this->encryptionLevels < 1)
                throw std::string("Invalid input: encryption levels must be greater than 1.");
        },
    };

    this->options['o'] = (Parameter){
        "out",
        "Output filename. (Default is crytped or decrypted)",
        true,
        "filename",
        "",
        false,
        [this](std::string value = "")
        {
            this->outputFile = value;
        },
    };
}

Encrypter::~Encrypter() {}

std::map<char, Parameter> &Encrypter::getOptions()
{
    return this->options;
}

void Encrypter::printHeader()
{
    std::cout << "Copyright (c) 2021 Aqua Forge" << std::endl;
    std::cout << "Aqua-Encrypter-CLI - Command line file encrypter v1.0" << std::endl;
    std::cout << "=====================================================" << std::endl;
    std::cout << "How it works:\n"
              << std::endl;
    std::cout << "The encryption algorithm uses a variation of the" << std::endl;
    std::cout << "Vignère cipher, where the key (password) is repeated" << std::endl;
    std::cout << "untill a text-sized key is obtained. Then, their" << std::endl;
    std::cout << "position matched characters are added, as long with" << std::endl;
    std::cout << "a salt, in order to generate the ciphertext. And" << std::endl;
    std::cout << "this process is repeated if more than one key is" << std::endl;
    std::cout << "provided.\n"
              << std::endl;
    std::cout << "Safety tips:\n"
              << std::endl;
    std::cout << "Your ciphertext will be more secure if you user more" << std::endl;
    std::cout << "than one password layer. As well, a dictionary-" << std::endl;
    std::cout << "assisted bruteforce attack can be frustrated if" << std::endl;
    std::cout << "random characters are inserted in the middle of your" << std::endl;
    std::cout << "plaintext. Lastly, the longer your key(s), the more" << std::endl;
    std::cout << "secure your cipher will be." << std::endl;
    std::cout << "=====================================================" << std::endl;
}

void Encrypter::printHelp()
{
    std::cout << "Usage:" << std::endl;
    std::cout << "\taqua-encrypter [-o | --option=value] INPUT_FILENAME\n"
              << std::endl;

    std::cout << "If no option is submitted, the encryption function is considered.\n"
              << std::endl;

    std::cout << "Options:" << std::endl;
    std::map<char, Parameter>::iterator it = this->options.begin();
    for (; it != this->options.end(); ++it)
    {
        std::cout << "\t-" << it->first << " ";
        if (it->second.hasValue)
            std::cout << it->second.valueInfo << " ";
        std::cout << "| --" << it->second.flagName;
        if (it->second.hasValue)
            std::cout << "=" << it->second.valueInfo;
        std::cout << "\n\n\t\t" << it->second.description << "\n\n";
    }
}
