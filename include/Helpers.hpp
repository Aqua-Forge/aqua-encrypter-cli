#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <filesystem>

namespace fs = std::filesystem;


namespace helpers 
{

    /**
     * @brief Verifies if str starts with subst
     * 
     * @param str String to be verified
     * @param substr Substring to be matched
     * @return true 
     * @return false 
     */
    bool startsWith (std::string str, std::string substr);

    /**
     * @brief Split str into a vector, using delimiter as separator
     * 
     * @param str Text to be splitted
     * @param delimiter Delimiter character
     * @return std::vector< std::string> 
     */
    std::vector<std::string> split(std::string const &str, const char delimiter);

}
