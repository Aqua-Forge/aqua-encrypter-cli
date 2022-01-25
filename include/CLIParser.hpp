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
    void parse(int argc, const char *argv[]);

    /**
     * @brief Checks if the parameter exists
     *
     */
    bool hasParameter(std::string parameter, char mode = STR_FLAG_MODE);

    /**
     * @brief Set the minimum amount of Options
     *
     * @param min minimum amount of options
     * @param errMsg the error message displayed if the minimum number of options is not entered.
     */
    void setMinimumOptionsAmount(u_short min);

    /**
     * @brief Set the help option flag. Its useful in error messages.
     *
     */
    void setHelpFlag(char helpFlag);

    /**
     * @brief Executes the encrypter
     *
     */
    void execute();

private:
    u_short minimumOptionsAmount = 0;
    bool hasHelpFlag = false;
    char helpFlag;
    std::map<char, Parameter> *parameters;
};
