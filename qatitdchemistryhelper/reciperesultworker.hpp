#pragma once

#include "libchemistryhelper/essencerecipefinder.hpp"
#include "libchemistryhelper/iessencesdatagatherer.hpp"

#include <QObject>

class RecipeResultWorker : public QObject
{
    Q_OBJECT

public:
    using Recipe_t = LibChemistryHelper::EssenceRecipeFinder::Result_t;

    RecipeResultWorker(QString recipe, LibChemistryHelper::IEssencesDataGatherer::Container_t essences,
                       QObject* parent = nullptr);

    virtual ~RecipeResultWorker() = default;

public slots:
    void process();

signals:
    void finished();

    void recipeFound(Recipe_t recipe);

    // void error(QString err);

private:
    const QString m_recipe;
    const LibChemistryHelper::IEssencesDataGatherer::Container_t m_essences;
};
