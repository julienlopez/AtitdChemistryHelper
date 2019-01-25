#include "reciperesultworker.hpp"

#include "libchemistryhelper/utils/strings.hpp"

#include <iostream>

RecipeResultWorker::RecipeResultWorker(QString recipe, LibChemistryHelper::IEssencesDataGatherer::Container_t essences,
                                       QObject* parent)
    : QObject(parent)
    , m_recipe(recipe)
    , m_essences(std::move(essences))
{
}

void RecipeResultWorker::process()
{
    using LibChemistryHelper::EssenceRecipeFinder;
    const auto reqs = LibChemistryHelper::Utils::Strings::split(m_recipe.toStdString(), ' ');
    std::vector<LibChemistryHelper::CompoundRequirement> requirements;
    std::transform(begin(reqs), end(reqs), std::back_inserter(requirements),
                   &LibChemistryHelper::CompoundRequirement::fromString);
    auto lbd = [this](Recipe_t recipe) { emit recipeFound(recipe); };
    EssenceRecipeFinder finder(m_essences, boost::optional<EssenceRecipeFinder::OnResultCallback_t>(lbd));
    const auto recipes = finder.findRecipes(requirements);
    std::cout << "done!" << std::endl; // TODO remove
    emit finished();
}
