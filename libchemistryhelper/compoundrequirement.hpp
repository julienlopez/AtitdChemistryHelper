#pragma once

#include "property.hpp"

#include <functional>
#include <vector>

namespace LibChemistryHelper
{

struct CompoundRequirement
{
    using TestCallback_t = std::function<bool(int)>;

    Property prop;
    TestCallback_t test;

    static CompoundRequirement fromString(std::string str);
};

using CompoundRequirementContainer_t = std::vector<CompoundRequirement>;

} // LibChemistryHelper
