#pragma once

#include <string>
#include <functional>

#define CHAR_FLAG_MODE 'c'
#define STR_FLAG_MODE 's'

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
