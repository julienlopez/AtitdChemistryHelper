#include "essencerecipefinder.hpp"

namespace LibChemistryHelper
{

namespace
{
    auto essencesHaveNamesLowerThan()
    {
        return [](const Essence& e1, const Essence& e2) { return e1.material < e2.material; };
    }

    auto essencesHaveTheSameName()
    {
        return [](const Essence& e1, const Essence& e2) { return e1.material == e2.material; };
    }
}

EssenceRecipeFinder::EssenceRecipeFinder(EssenceContainer_t essences)
    : m_essences(std::move(essences))
{
}

auto EssenceRecipeFinder::findRecipes(const RequirementContainer_t& requirements) const -> ResultContainer_t
{
    const auto valid_essences = findValidEssences(requirements);
    return {};
}

auto EssenceRecipeFinder::findValidEssences(const RequirementContainer_t& requirements) const -> EssenceContainer_t
{
    EssenceContainer_t valid_essences;
    for(const auto& req : requirements)
    {
        std::copy_if(begin(m_essences), end(m_essences), std::back_inserter(valid_essences),
                     [&req](const Essence& e) { return e.properties.at(req.prop).is_initialized(); });
    }
    std::sort(begin(valid_essences), end(valid_essences), essencesHaveNamesLowerThan());
    const auto it = std::unique(begin(valid_essences), end(valid_essences), essencesHaveTheSameName());
    valid_essences.erase(it, end(valid_essences));
    return valid_essences;
}

} // namespace LibChemistryHelper
