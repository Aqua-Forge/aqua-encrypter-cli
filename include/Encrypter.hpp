#include "Parameter.hpp"
#include <map>
#include <iostream>

#define ENCRYPT_MODE 'e'
#define DECRYPT_MODE 'd'

class Encrypter
{
public:
    Encrypter();
    ~Encrypter();

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
     * @brief Return the CLI options
     *
     */
    std::map<char, Parameter> &getOptions();

private:
    std::map<char, Parameter> options;

    char mode = ENCRYPT_MODE;
    int encryptionLevels = 1;
    std::string inputFile = "";
    std::string outputFile = "encrypted";
};
