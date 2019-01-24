#include "essencetab.hpp"

#include "essencemodel.hpp"
#include "recipecomposer.hpp"

#include <QTableView>
#include <QVBoxLayout>

EssenceTab::EssenceTab(EssenceContainer_t essences_, QWidget* parent)
    : QWidget(parent)
{
    auto* l = new QVBoxLayout;

    auto* recipe_composer = new RecipeComposer;
    l->addWidget(recipe_composer);

    m_essence_model = new EssenceModel(std::move(essences_), this);
    m_essence_grid = new QTableView;
    m_essence_grid->setModel(m_essence_model);
    l->addWidget(m_essence_grid);

    setLayout(l);
}

auto EssenceTab::essences() const -> EssenceContainer_t
{
    return m_essence_model->essences();
}
