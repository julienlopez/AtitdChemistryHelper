#include "essencetab.hpp"

#include "essencemodel.hpp"

#include <QTableView>
#include <QVBoxLayout>

EssenceTab::EssenceTab(EssenceContainer_t essences_, QWidget* parent)
    : QWidget(parent)
{
    auto* l = new QVBoxLayout;

    m_essence_model = new EssenceModel(std::move(essences_), this);
    m_essence_grid = new QTableView;
    m_essence_grid->setModel(m_essence_model);
    l->addWidget(m_essence_grid);

    setLayout(l);
}

auto EssenceTab::essences() const -> const EssenceContainer_t&
{
    return m_essence_model->essences();
}
