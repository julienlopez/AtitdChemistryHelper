#pragma once

#include <QWidget>

class RecipeComposer : public QWidget
{
    Q_OBJECT

public:
    explicit RecipeComposer(QWidget* parent = nullptr);

    virtual ~RecipeComposer() = default;

signals:
    void newRecipe(const QString& recipe);
};
