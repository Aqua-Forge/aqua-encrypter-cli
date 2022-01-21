#include "HelloWorld.hpp"


HelloWorld::HelloWorld()
{
    this->text = "Hello World!";
}

HelloWorld::~HelloWorld() {}

void HelloWorld::print()
{
    std::cout << this->text << std::endl;
}
