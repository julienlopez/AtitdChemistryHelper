#pragma once

#include <map>
#include <string>

#include <boost/optional.hpp>

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

    Essence(std::string material_, boost::optional<uint8_t> temperature_, std::string recipe_,
            boost::optional<int8_t> ar, boost::optional<int8_t> as, boost::optional<int8_t> bi,
            boost::optional<int8_t> sa, boost::optional<int8_t> so, boost::optional<int8_t> sp,
            boost::optional<int8_t> sw, boost::optional<int8_t> to);

    std::string material;
    boost::optional<uint8_t> temperature;
    std::string recipe;
    std::map<Property, boost::optional<int8_t>> properties;
};

Essence::Property stringToProperty(const std::string& str);

std::string propertyToString(const Essence::Property);

} // LibChemistryHelper
