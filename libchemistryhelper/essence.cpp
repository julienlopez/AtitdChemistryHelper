#include "essence.hpp"

namespace LibChemistryHelper
{

Essence::Essence(std::string material_, boost::optional<uint8_t> temperature_, std::string recipe_,
                 boost::optional<int8_t> ar, boost::optional<int8_t> as, boost::optional<int8_t> bi,
                 boost::optional<int8_t> sa, boost::optional<int8_t> so, boost::optional<int8_t> sp,
                 boost::optional<int8_t> sw, boost::optional<int8_t> to)
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

} // LibChemistryHelper
