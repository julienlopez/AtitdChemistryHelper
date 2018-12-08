#include "property.hpp"

#include <algorithm>
#include <map>

namespace LibChemistryHelper
{

namespace
{
    using PropertyLabels = std::map<Property, std::string>;

    PropertyLabels labels()
    {
        return {{Property::Ar, "Ar"}, {Property::As, "As"}, {Property::Bi, "Bi"}, {Property::Sa, "Sa"},
                {Property::So, "So"}, {Property::Sp, "Sp"}, {Property::Sw, "Sw"}, {Property::To, "To"}};
    }
}

Property stringToProperty(const std::string& str)
{
    const auto lab = labels();
    const auto it
        = std::find_if(begin(lab), end(lab), [&str](const PropertyLabels::value_type& p) { return p.second == str; });
    return it->first;
}

std::string propertyToString(const Property prop)
{
    return labels().at(prop);
}

} // LibChemistryHelper
