#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include "Helpers.hpp"

#define CHAR_FLAG_MODE 'c'
#define STR_FLAG_MODE 's'
#define ENCRYPT_MODE 'e'
#define DECRYPT_MODE 'd'


/**
 * @brief ADT of a command line parameter
 */
struct Parameter {
    const char *flagName;
    const char *description;
    bool hasValue;
    std::string valueInfo = "";
    std::string value = "";
    bool wasCalled = false;
    std::function<void(std::string value)> action;
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

    /**
     * @brief Parses the input arguments.
     * 
     */
    void parse();

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
    int argc;
    std::vector<std::string> argv;
    std::map<char, Parameter> parameters;
    
    char mode = ENCRYPT_MODE;
    int encryptionLevels = 1;
    std::string inputFile = "";
    std::string outputFile = "encrypted";
};
