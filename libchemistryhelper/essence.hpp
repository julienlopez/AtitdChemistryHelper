#pragma once

#include <map>
#include <string>

namespace LibChemistryHelper
{

struct Essence
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

    Essence(std::string material_, uint8_t temperature_, std::string recipe_, int8_t ar, int8_t as, int8_t bi,
            int8_t sa, int8_t so, int8_t sp, int8_t sw, int8_t to);

    std::string material;
    uint8_t temperature;
    std::string recipe;
    std::map<Property, int8_t> properties;
};

Essence::Property stringToProperty(const std::string& str);

std::string propertyToString(const Essence::Property);

} // LibChemistryHelper
