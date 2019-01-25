#pragma once

#include <QAbstractTableModel>

class RecipeResultModel : public QAbstractTableModel
{
public:
    using Recipe_t = std::array<QString, 5>;

    explicit RecipeResultModel(QObject* parent = nullptr);

    virtual ~RecipeResultModel() = default;

    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    virtual int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    // virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

public slots:
    void addResult(Recipe_t recipe);

private:
    QVector<Recipe_t> m_recipes;
};