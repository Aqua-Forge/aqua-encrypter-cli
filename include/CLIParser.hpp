#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>


/**
 * @brief ADT of a command line parameter
 */
struct Parameter {
    char flag;
    const char *flagName;
    const char *description;
    bool hasValue;
    std::string value = "";
};


/**
 * @brief Parses the command line arguments and returns a valid configuration for encryption
 *
 */
class CLIParser
{
public:
    CLIParser(int argc, const char *argv[]);
    ~CLIParser();

    /**
     * @brief Prints the loaded CLI args.
     *
     */
    void printArgs();

    /**
     * @brief Prints CLI auxiliary/help information.
     *
     */
    void printHeader();

    /**
     * @brief Prints CLI auxiliary/help information.
     *
     */
    void printHelp();

private:
    int argc;
    std::vector<std::string> argv;
    std::map<char, Parameter> parameters;
};
