#include "Helpers.hpp"


bool helpers::startsWith (std::string str, std::string substr)
{
    return str.rfind(substr, 0) == 0;
}


std::vector<std::string> helpers::split(std::string const &str, const char delimiter)
{
    std::vector<std::string> out;
    std::stringstream ss(str);
    std::string s;
    while (std::getline(ss, s, delimiter))
    {
        out.push_back(s);
    }
    return out;
}
