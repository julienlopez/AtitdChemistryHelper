#pragma once

#include <string>

namespace LibChemistryHelper
{

enum class Property
{
    Ar,
    As,
    Bi,
    Sa,
    So,
    Sp,
    Sw,
    To
};

Property stringToProperty(const std::string& str);

std::string propertyToString(const Property);

} // LibChemistryHelper