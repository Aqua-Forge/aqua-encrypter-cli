#include "CLIParser.hpp"


CLIParser::CLIParser(std::map<char, Parameter> &parameters)
{
    this->parameters = &parameters;
}


CLIParser::~CLIParser() {}


bool CLIParser::hasParameter(std::string parameter, char mode)
{
    std::map<char, Parameter>::iterator it = this->parameters->begin();

    if (mode == STR_FLAG_MODE) {
        for (; it != this->parameters->end(); ++it)
        {
            if (std::string(it->second.flagName) == parameter)
                return true;
        }
    }
    else {
        for (; it != this->parameters->end(); ++it)
        {
            if (it->first == (char)parameter[0])
                return true;
        }
    }

    return false;
}


void CLIParser::parse(int argc, const char* argv[])
{
    if (argc <= 1) {
        throw std::string("Invalid syntax: Please enter the input file. Use the -h flag for help.");
    }

    for (int i = 1; i < argc; ++i)
    {
        if (helpers::startsWith(argv[i], std::string("--"))) {
            std::string raw_opt = std::string(argv[i]).substr(2);
            std::vector option_and_value = helpers::split(raw_opt, '=');
            std::string option = option_and_value[0];

            if (this->hasParameter(option)) {
                (*this->parameters)[option[0]].wasCalled = true;

                if ((*this->parameters)[option[0]].hasValue) {
                    if (option_and_value.size() == 1)
                        throw "Invalid syntax: the option \"" + option + "\" must have a valid value.";

                    (*this->parameters)[option[0]].value = option_and_value[1];
                }
            }
            else
                throw "Invalid option: \"" + option + "\"";
        }

        else if (helpers::startsWith(argv[i], std::string("-"))) {
            std::string arg = std::string(argv[i]).substr(1);

            if (this->hasParameter(arg, CHAR_FLAG_MODE)) {
                (*this->parameters)[arg[0]].wasCalled = true;

                if ((*this->parameters)[arg[0]].hasValue) {
                    if (i + 1 == argc)
                        throw "Invalid syntax: the option \"" + arg + "\" must have a valid value.";

                    (*this->parameters)[arg[0]].value = argv[++i];
                }
            }
            else
                throw "Invalid flag: \"" + arg + "\"";
        }
    }
}


void CLIParser::execute()
{    
    std::map<char, Parameter>::iterator it = this->parameters->begin();
    for (; it != this->parameters->end(); ++it)
    {
        if (it->second.wasCalled)
            it->second.action(it->second.value);
    }
}
