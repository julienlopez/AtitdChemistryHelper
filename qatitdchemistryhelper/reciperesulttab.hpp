#pragma once

#include "libchemistryhelper/iessencesdatagatherer.hpp"

#include <QWidget>

class RecipeResultModel;

class QLabel;
class QTableView;

class RecipeResultTab : public QWidget
{
    Q_OBJECT

public:
    explicit RecipeResultTab(QString recipe, LibChemistryHelper::IEssencesDataGatherer::Container_t essences,
                             QWidget* parent = nullptr);

    virtual ~RecipeResultTab() = default;

private:
    QTableView* m_recipe_grid;
    RecipeResultModel* m_recipe_model;
    QLabel* m_details_label;
    QThread* m_thread;

    void startSearch(QString recipe, LibChemistryHelper::IEssencesDataGatherer::Container_t essences);

    void updateDetailsLabel();
};