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

    using OnResultCallback_t = std::function<void(Result_t)>;

    EssenceRecipeFinder(EssenceContainer_t essences,
                        boost::optional<OnResultCallback_t> on_result_callback = boost::none);

    ResultContainer_t findRecipes(const CompoundRequirementContainer_t& requirements) const;

    TemplateContainer_t findTemplates(const CompoundRequirementContainer_t& requirements) const;

private:
    const EssenceContainer_t m_essences;
    boost::optional<OnResultCallback_t> m_on_result_callback;

    EssenceContainer_t findValidEssences(const CompoundRequirementContainer_t& requirements) const;
};

} // LibChemistryHelper
