#pragma once

#include <string>
#include <vector>

#include <boost/utility/string_view.hpp>

namespace LibChemistryHelper
{

namespace Utils
{

    namespace Strings
    {
        std::string trim(std::string str);

        std::vector<std::string> split(const std::string& str, char delimiter);

        std::vector<std::string> split(boost::string_view str, const std::string& delimiter);

        bool beginsWith(const std::string& str, const std::string& token);

        bool endsWith(const std::string& str, const std::string& token);
    }

} // Utils

} // LibChemistryHelper
