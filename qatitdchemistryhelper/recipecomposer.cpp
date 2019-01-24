#include "recipecomposer.hpp"

#include <QHBoxLayout>
#include <QPushButton>

RecipeComposer::RecipeComposer(QWidget* parent)
    : QWidget(parent)
{
    setFixedHeight(100);
    auto* lay = new QHBoxLayout;

    auto* b = new QPushButton(tr("Clear"));
    lay->addWidget(b);

    lay->addStretch();

    b = new QPushButton(tr("Search"));
    lay->addWidget(b);

    setLayout(lay);
}
