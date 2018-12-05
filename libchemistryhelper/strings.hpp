#pragma once

#include <string>
#include <vector>

namespace LibChemistryHelper
{

namespace Utils
{

    namespace Strings
    {
        std::string trim(std::string str);

        std::vector<std::string> split(std::string str, char delimiter);

        bool beginsWith(const std::string& str, const std::string& token);

        bool endsWith(const std::string& str, const std::string& token);
    }

} // Utils

} // LibChemistryHelper
