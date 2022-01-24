#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "Helpers.hpp"
#include "Parameter.hpp"


/**
 * @brief Parses the command line arguments and returns a valid configuration for encryption
 *
 */
class CLIParser
{
public:
    CLIParser(std::map<char, Parameter> &parameters);
    ~CLIParser();

    /**
     * @brief Parses the input arguments.
     * 
     */
    void parse(int argc, const char* argv[]);

    /**
     * @brief Checks if the parameter exists
     * 
     */
    bool hasParameter(std::string parameter, char mode=STR_FLAG_MODE);


    /**
     * @brief Executes the encrypter
     * 
     */
    void execute();

private:
    std::map<char, Parameter> *parameters;
};
