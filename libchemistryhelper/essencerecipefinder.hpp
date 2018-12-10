#pragma once

#include "essence.hpp"

#include <array>
#include <vector>

namespace LibChemistryHelper
{

class EssenceRecipeFinder
{
public:
    struct Requirement
    {
        using TestCallback_t = std::function<bool(int)>;
        Property prop;
        TestCallback_t test;
    };

    using RequirementContainer_t = std::vector<Requirement>;
    using EssenceContainer_t = Essence::Container_t;
    using Result_t = std::array<Essence, 5>;
    using ResultContainer_t = std::vector<Result_t>;

    EssenceRecipeFinder(EssenceContainer_t essences);

    ResultContainer_t findRecipes(const RequirementContainer_t& requirements) const;

private:
    const EssenceContainer_t m_essences;

    EssenceContainer_t findValidEssences(const RequirementContainer_t& requirements) const;
};

} // LibChemistryHelper
