#include "compoundrequirement.hpp"

#include <algorithm>

#include <gsl/gsl_assert>
#include <gsl/gsl_util>

namespace LibChemistryHelper
{

Property extractProp(std::string str)
{
    Expects(str.size() >= 2);
    str[0] = toupper(str[0]);
    str[1] = tolower(str[1]);
    return stringToProperty(str);
}

bool isValidTestString(const std::string& str)
{
    if(str.front() != '(' || str.back() != ')') return false;
    return std::all_of(begin(str) + 1, end(str) - 1, [](char c) { return c == '+'; })
           || std::all_of(begin(str) + 1, end(str) - 1, [](char c) { return c == '-'; });
}

CompoundRequirement::TestCallback_t extractTest(std::string str)
{
    Expects(isValidTestString(str));
    str = str.substr(1, str.size() - 2);
    const int treshold_value = gsl::narrow<int>(3 * (str.size() - 2) + 4);
    if(str.front() == '+')
        return [treshold_value](int v) { return v >= treshold_value; };
    else
        return [treshold_value](int v) { return v <= -treshold_value; };
}

CompoundRequirement CompoundRequirement::fromString(std::string str)
{
    str.erase(std::remove_if(begin(str), end(str), isspace), end(str));
    const auto pos = str.find('(');
    if(pos == std::string::npos) throw std::runtime_error("Unable to parse Compoud Requirement : " + str);
    auto prop_str = str.substr(0, pos).substr(0, 2);
    if(prop_str.size() < 2) throw std::runtime_error("Unable to parse Compoud Requirement : " + str);
    auto value_str = str.substr(pos);
    if(!isValidTestString(value_str)) throw std::runtime_error("Unable to parse Compoud Requirement : " + str);
    return {extractProp(prop_str), extractTest(value_str)};
}

} // LibChemistryHelper
