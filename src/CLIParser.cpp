#include "CLIParser.hpp"


CLIParser::CLIParser(int argc, const char *argv[])
{
    this->argc = argc;

    for (int i = 0; i < argc; i++)
        this->argv.push_back(argv[i]);

    this->parameters['d'] = (Parameter){
        "decrypt",
        "Uses the decrypt mode. The INPUT_FILENAME must be the ciphertext.",
        false,
        "",
        "",
        false,
        [this](std::string value = "") {
            this->mode = DECRYPT_MODE;
            if (this->outputFile == "encrypted")
                this->outputFile = "decrypted";
        },
    };

    this->parameters['h'] = (Parameter){
        "help",
        "Display this help.",
        false,
        "",
        "",
        false,
        [this](std::string value = "") {
            this->printHeader();
            this->printHelp();
        },
    };

    this->parameters['l'] = (Parameter){
        "levels",
        "The number 'num' (integer) of password layers for encryption/decryption.",
        true,
        "num",
        "",
        false,
        [this](std::string value = "") {
            try {
                this->encryptionLevels = std::stoi(value);
            } catch (std::invalid_argument err) {
                throw "Invalid input \"" + value + "\": encryption levels must be a integer.";
            }
            if (this->encryptionLevels < 1)
                throw std::string("Invalid input: encryption levels must be greater than 1.");
        },
    };

    this->parameters['o'] = (Parameter){
        "out",
        "Output filename. (Default is crytped or decrypted)",
        true,
        "filename",
        "",
        false,
        [this](std::string value = "") {
            this->outputFile = value;
        },
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


void CLIParser::printHelp()
{
    std::cout << "Usage:" << std::endl;
    std::cout << "\taqua-encrypter [-o | --option=value] INPUT_FILENAME\n"
              << std::endl;

    std::cout << "If no option is submitted, the encryption function is considered.\n"
              << std::endl;

    std::cout << "Options:" << std::endl;
    std::map<char, Parameter>::iterator it = this->parameters.begin();
    for (; it != this->parameters.end(); ++it)
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


bool CLIParser::hasParameter(std::string parameter, char mode)
{
    std::map<char, Parameter>::iterator it = this->parameters.begin();

    if (mode == STR_FLAG_MODE) {
        for (; it != this->parameters.end(); ++it)
        {
            if (std::string(it->second.flagName) == parameter)
                return true;
        }
    }
    else {
        for (; it != this->parameters.end(); ++it)
        {
            if (it->first == (char)parameter[0])
                return true;
        }
    }

    return false;
}


void CLIParser::parse()
{
    if (this->argc <= 1) {
        throw std::string("Invalid syntax: Please enter the input file. Use the -h flag for help.");
    }

    for (int i = 1; i < argc; ++i)
    {
        if (helpers::startsWith(this->argv[i], std::string("--"))) {
            std::string raw_opt = this->argv[i].substr(2);
            std::vector option_and_value = helpers::split(raw_opt, '=');
            std::string option = option_and_value[0];

            if (this->hasParameter(option)) {
                this->parameters[option[0]].wasCalled = true;

                if (this->parameters[option[0]].hasValue) {
                    if (option_and_value.size() == 1)
                        throw "Invalid syntax: the option \"" + option + "\" must have a valid value. Use the -h flag for help.";

                    this->parameters[option[0]].value = option_and_value[1];
                }
            }
            else
                throw "Invalid option: \"" + option + "\"";
        }

        else if (helpers::startsWith(this->argv[i], std::string("-"))) {
            std::string arg = this->argv[i].substr(1);

            if (this->hasParameter(arg, CHAR_FLAG_MODE)) {
                this->parameters[arg[0]].wasCalled = true;

                if (this->parameters[arg[0]].hasValue) {
                    if (i + 1 == this->argc)
                        throw "Invalid syntax: the option \"" + arg + "\" must have a valid value. Use the -h flag for help.";

                    this->parameters[arg[0]].value = this->argv[++i];
                }
            }
            else
                throw "Invalid flag: \"" + arg + "\"";
        }

        else {
            this->inputFile = this->argv[i];
        }
    }
}


void CLIParser::execute()
{    
    std::map<char, Parameter>::iterator it = this->parameters.begin();
    for (; it != this->parameters.end(); ++it)
    {
        if (it->second.wasCalled)
            it->second.action(it->second.value);
    }
}
