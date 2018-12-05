#include "strings.hpp"

#include <cctype>

#include <boost/algorithm/string.hpp>

namespace LibChemistryHelper
{

namespace Utils
{


    std::string Strings::trim(std::string str)
    {
        while(!str.empty() && std::isspace(str.front()))
            str.erase(str.begin());
        while(!str.empty() && std::isspace(str.back()))
            str.erase(--str.end());
        return str;
    }

    std::vector<std::string> Strings::split(std::string str, char delimiter)
    {
        std::vector<std::string> res;
        boost::algorithm::split(res, str, boost::is_any_of(std::string(1, delimiter)));
        return res;
    }

    bool Strings::beginsWith(const std::string& str, const std::string& token)
    {
        if(token.size() > str.size()) return false;
        return std::equal(token.begin(), token.end(), str.begin());
    }

    bool Strings::endsWith(const std::string& str, const std::string& token)
    {
        if(token.size() > str.size()) return false;
        return std::equal(token.rbegin(), token.rend(), str.rbegin());
    }

} // Utils

} // LibChemistryHelper
