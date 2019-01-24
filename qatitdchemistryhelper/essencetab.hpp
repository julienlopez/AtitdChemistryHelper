#pragma once

#include "libchemistryhelper/iessencesdatagatherer.hpp"

#include <QWidget>

class EssenceModel;

class QTableView;

class EssenceTab : public QWidget
{
    Q_OBJECT

    using EssenceContainer_t = LibChemistryHelper::IEssencesDataGatherer::Container_t;

public:
    explicit EssenceTab(EssenceContainer_t essences_, QWidget* parent = nullptr);

    virtual ~EssenceTab() = default;

    EssenceContainer_t essences() const;

private:
    QTableView* m_essence_grid;
    EssenceModel* m_essence_model;
};