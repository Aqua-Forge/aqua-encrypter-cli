#pragma once

#include <iostream>
#include <string>

/**
 * @brief Hello World Class
 * 
 */
class HelloWorld
{
public:
    HelloWorld();
    ~HelloWorld();

    /**
     * @brief Prints Hello World!
     * 
     */
    void print();

private:
    std::string text;
};
