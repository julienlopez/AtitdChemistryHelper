#include "reciperesulttab.hpp"

#include "reciperesultmodel.hpp"
#include "reciperesultworker.hpp"

#include <QLabel>
#include <QTableView>
#include <QThread>
#include <QVBoxLayout>

RecipeResultTab::RecipeResultTab(QString recipe, LibChemistryHelper::IEssencesDataGatherer::Container_t essences,
                                 QWidget* parent)
    : QWidget(parent)
{
    auto* l = new QVBoxLayout;

    m_details_label = new QLabel;
    l->addWidget(m_details_label);

    m_recipe_model = new RecipeResultModel(this);
    m_recipe_grid = new QTableView;
    m_recipe_grid->setModel(m_recipe_model);
    l->addWidget(m_recipe_grid);

    startSearch(recipe, std::move(essences));

    setLayout(l);
}

void RecipeResultTab::startSearch(QString recipe, LibChemistryHelper::IEssencesDataGatherer::Container_t essences)
{
    m_thread = new QThread;
    auto* worker = new RecipeResultWorker(recipe, std::move(essences));
    worker->moveToThread(m_thread);
    connect(worker, &RecipeResultWorker::recipeFound, [this](RecipeResultWorker::Recipe_t recipe) {
        RecipeResultModel::Recipe_t text_recipe;
        std::transform(begin(recipe), end(recipe), begin(text_recipe),
                       [](const LibChemistryHelper::Essence& e) { return QString::fromStdString(e.material); });
        m_recipe_model->addResult(text_recipe);
        updateDetailsLabel();
    });
    connect(m_thread, &QThread::started, worker, &RecipeResultWorker::process);
    connect(worker, &RecipeResultWorker::finished, m_thread, &QThread::quit);
    connect(worker, &RecipeResultWorker::finished, worker, &RecipeResultWorker::deleteLater);
    connect(m_thread, &QThread::finished, m_thread, &QThread::deleteLater);
    connect(m_thread, &QThread::finished, this, &RecipeResultTab::updateDetailsLabel);
    m_thread->start();
    updateDetailsLabel();
}

void RecipeResultTab::updateDetailsLabel()
{
    m_details_label->setText(tr("Found: %1\nStatus: ").arg(QString::number(m_recipe_model->rowCount()))
                             + (m_thread->isRunning() ? tr("Running") : tr("Done")));
}
