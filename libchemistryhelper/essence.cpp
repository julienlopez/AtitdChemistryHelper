#include "essence.hpp"

#include <algorithm>

namespace LibChemistryHelper
{

namespace
{
    using PropertyLabels = std::map<Essence::Property, std::string>;

    PropertyLabels labels()
    {
        return {{Essence::Property::Ar, "Ar"}, {Essence::Property::As, "As"}, {Essence::Property::Bi, "Bi"},
                {Essence::Property::Sa, "Sa"}, {Essence::Property::So, "So"}, {Essence::Property::Sp, "Sp"},
                {Essence::Property::Sw, "Sw"}, {Essence::Property::To, "To"}};
    }
}

Essence::Essence(std::string material_, uint8_t temperature_, std::string recipe_, int8_t ar, int8_t as, int8_t bi,
                 int8_t sa, int8_t so, int8_t sp, int8_t sw, int8_t to)
    : material(std::move(material_))
    , temperature(temperature_)
    , recipe(std::move(recipe_))
    , properties({{Property::Ar, ar},
                  {Property::As, as},
                  {Property::Bi, bi},
                  {Property::Sa, sa},
                  {Property::So, so},
                  {Property::Sp, sp},
                  {Property::Sw, sw},
                  {Property::To, to}})
{
}

Essence::Property stringToProperty(const std::string& str)
{
    const auto lab = labels();
    const auto it
        = std::find_if(begin(lab), end(lab), [&str](const PropertyLabels::value_type& p) { return p.second == str; });
    return it->first;
}

std::string propertyToString(const Essence::Property prop)
{
    return labels().at(prop);
}

} // namespace LibChemistryHelper