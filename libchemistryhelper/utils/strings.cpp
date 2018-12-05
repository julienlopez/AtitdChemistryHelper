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

    std::vector<std::string> Strings::split(const std::string& str, char delimiter)
    {
        std::vector<std::string> res;
        boost::algorithm::split(res, str, boost::is_any_of(std::string(1, delimiter)));
        return res;
    }

    std::vector<std::string> Strings::split(boost::string_view str, const std::string& delimiter)
    {
        std::vector<std::string> res;
        while(!str.empty())
        {
            const auto pos = str.find(delimiter);
            if(pos == std::string::npos)
            {
                res.push_back(str.to_string());
                str.clear();
            }
            else
            {
                res.push_back(str.substr(0, pos).to_string());
                str = str.substr(pos + delimiter.size());
                if(str.empty()) res.push_back("");
            }
        }
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
