#pragma once

#include "libchemistryhelper/iessencesdatagatherer.hpp"

#include <QFutureWatcher>
#include <QMainWindow>

class EssenceTab;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    using EssenceContainer_t = LibChemistryHelper::IEssencesDataGatherer::Container_t;

public:
    explicit MainWindow();

    virtual ~MainWindow() = default;

public slots:
    void loadEssences();

private:
    QFutureWatcher<EssenceContainer_t> m_essence_watcher;
    QTabWidget* m_tab_widget;
    EssenceTab* m_essence_tab;

    void startNewRecipeSearch(const QString new_recipe);
};