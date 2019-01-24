#include "essencemodel.hpp"

#include <array>

#include <gsl/gsl_util>

EssenceModel::EssenceModel(EssenceContainer_t essences_, QObject* parent)
    : QAbstractTableModel(parent)
    , m_essences(std::move(essences_))
{
}

auto EssenceModel::essences() const -> const EssenceContainer_t&
{
    return m_essences;
}

int EssenceModel::rowCount(const QModelIndex& parent) const
{
    return gsl::narrow<int>(m_essences.size());
}

int EssenceModel::columnCount(const QModelIndex& parent) const
{
    return 11;
}

QVariant EssenceModel::data(const QModelIndex& index, int role) const
{
    if(role != Qt::DisplayRole || index.row() >= rowCount() || index.column() >= columnCount()) return QVariant();
    const auto& essence = m_essences[index.row()];
    using LibChemistryHelper::Property;
    static const std::array<Property, 8> properties{Property::Ar, Property::As, Property::Bi, Property::Sa,
                                                    Property::So, Property::Sp, Property::Sw, Property::To};
    if(index.column() == 0) return QString::fromStdString(essence.material);
    if(index.column() == 2) return essence.temperature ? QString::number(*essence.temperature) : QString();
    if(index.column() == 1) return QString::fromStdString(essence.recipe);
    const auto prop = essence.properties.at(properties[index.column() - 3]);
    return prop ? QString::number(*prop) : QString();
}

QVariant EssenceModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    static const QStringList headers{
        tr("Material"), tr("Temperature"), tr("Spirits"), "Ar", "As", "Bi", "Sa", "So", "Sp", "Sw", "To"};
    if(role != Qt::DisplayRole) return QVariant();
    if(orientation == Qt::Vertical)
        return section;
    else
        return headers[section];
}
