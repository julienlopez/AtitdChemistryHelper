#include "reciperesulttab.hpp"

#include "reciperesultworker.hpp"

#include <QTableView>
#include <QThread>
#include <QVBoxLayout>

#include <iostream>

RecipeResultTab::RecipeResultTab(QString recipe, LibChemistryHelper::IEssencesDataGatherer::Container_t essences,
                                 QWidget* parent)
    : QWidget(parent)
{
    auto* l = new QVBoxLayout;

    // m_essence_model = new EssenceModel(std::move(essences_), this);
    m_recipe_grid = new QTableView;
    // m_essence_grid->setModel(m_essence_model);
    l->addWidget(m_recipe_grid);

    startSearch(recipe, std::move(essences));

    setLayout(l);
}

void RecipeResultTab::startSearch(QString recipe, LibChemistryHelper::IEssencesDataGatherer::Container_t essences)
{
    QThread* thread = new QThread;
    auto* worker = new RecipeResultWorker(recipe, std::move(essences));
    worker->moveToThread(thread);
    connect(worker, &RecipeResultWorker::recipeFound, [this](RecipeResultWorker::Recipe_t recipe) {
        std::cout << recipe[0].material << ", " << recipe[1].material << ", " << recipe[2].material << ", "
                  << recipe[3].material << ", " << recipe[4].material << std::endl;
    });
    connect(thread, &QThread::started, worker, &RecipeResultWorker::process);
    connect(worker, &RecipeResultWorker::finished, thread, &QThread::quit);
    connect(worker, &RecipeResultWorker::finished, worker, &RecipeResultWorker::deleteLater);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);
    thread->start();
}
