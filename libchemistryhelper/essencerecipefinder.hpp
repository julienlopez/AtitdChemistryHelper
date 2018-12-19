#pragma once

#include "compoundrequirement.hpp"
#include "essence.hpp"

#include <array>
#include <vector>

namespace LibChemistryHelper
{

class EssenceRecipeFinder
{
public:
    using EssenceContainer_t = Essence::Container_t;
    using Result_t = std::array<Essence, 5>;
    using ResultContainer_t = std::vector<Result_t>;
    using Template_t = std::array<Essence, 4>;
    using TemplateContainer_t = std::vector<Template_t>;

    EssenceRecipeFinder(EssenceContainer_t essences);

    ResultContainer_t findRecipes(const CompoundRequirementContainer_t& requirements) const;

    TemplateContainer_t findTemplates(const CompoundRequirementContainer_t& requirements) const;

private:
    const EssenceContainer_t m_essences;

    EssenceContainer_t findValidEssences(const CompoundRequirementContainer_t& requirements) const;
};

} // LibChemistryHelper
