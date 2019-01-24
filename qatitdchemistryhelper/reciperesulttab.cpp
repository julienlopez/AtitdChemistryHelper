#include "reciperesulttab.hpp"

#include <QTableView>
#include <QVBoxLayout>

RecipeResultTab::RecipeResultTab(QString recipe, QWidget* parent)
    : QWidget(parent)
{
    auto* l = new QVBoxLayout;

    // m_essence_model = new EssenceModel(std::move(essences_), this);
    m_recipe_grid = new QTableView;
    // m_essence_grid->setModel(m_essence_model);
    l->addWidget(m_recipe_grid);
    //
    // connect(recipe_composer, &RecipeComposer::newRecipe, this, &EssenceTab::newRecipe);

    setLayout(l);
}
