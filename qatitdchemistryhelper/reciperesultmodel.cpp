#include "reciperesultmodel.hpp"

#include "utils.hpp"

#include <numeric_range.hpp>

#include <array>

#include <gsl/gsl_util>

RecipeResultModel::RecipeResultModel(QObject* parent)
    : QAbstractTableModel(parent)
{
}

int RecipeResultModel::rowCount(const QModelIndex& parent) const
{
    return m_recipes.size();
}

int RecipeResultModel::columnCount(const QModelIndex& parent) const
{
    return 5;
}

QVariant RecipeResultModel::data(const QModelIndex& index, int role) const
{
    if(role != Qt::DisplayRole || index.row() >= rowCount() || index.column() >= columnCount()) return QVariant();
    return m_recipes[index.row()][index.column()];
}

// QVariant RecipeResultModel::headerData(int section, Qt::Orientation orientation, int role) const
// {
//     static const QStringList headers = QStringList{tr("Material"), tr("disabled"), tr("Temperature"), tr("Spirits")}
//                                        << Utils::propertyNames();
//     if(role != Qt::DisplayRole) return QVariant();
//     if(orientation == Qt::Vertical)
//         return section;
//     else
//         return headers[section];
// }

void RecipeResultModel::addResult(std::array<QString, 5> recipe)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_recipes << recipe;
    endInsertRows();
}
