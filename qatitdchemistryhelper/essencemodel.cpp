#include "essencemodel.hpp"

#include "utils.hpp"

#include <numeric_range.hpp>

#include <array>

#include <gsl/gsl_util>

#include <QColor>

EssenceModel::EssenceModel(EssenceContainer_t essences_, QObject* parent)
    : QAbstractTableModel(parent)
    , m_essences(std::move(essences_))
    , m_disabled_essences(m_essences.size(), false)
{
}

auto EssenceModel::essences() const -> EssenceContainer_t
{
    EssenceContainer_t essences;
    for(const auto i : range(m_essences.size()))
    {
        if(!m_disabled_essences[i]) essences.push_back(m_essences[i]);
    }
    return essences;
}

int EssenceModel::rowCount(const QModelIndex& parent) const
{
    return gsl::narrow<int>(m_essences.size());
}

int EssenceModel::columnCount(const QModelIndex& parent) const
{
    return 12;
}

QVariant EssenceModel::data(const QModelIndex& index, int role) const
{
    if((role != Qt::DisplayRole && role != Qt::CheckStateRole && role != Qt::ForegroundRole)
       || index.row() >= rowCount() || index.column() >= columnCount())
        return QVariant();
    if(role == Qt::ForegroundRole)
    {
        if(m_disabled_essences[index.row()]) return QColor(Qt::lightGray);
        return QColor(Qt::black);
    }
    if(index.column() == 1)
    {
        if(role == Qt::CheckStateRole)
            return m_disabled_essences[index.row()];
        else
            return {};
    }
    if(role != Qt::DisplayRole) return {};
    return essenceValue(index);
}

QVariant EssenceModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    static const QStringList headers = QStringList{tr("Material"), tr("disabled"), tr("Temperature"), tr("Spirits")}
                                       << Utils::propertyNames();
    if(role != Qt::DisplayRole) return QVariant();
    if(orientation == Qt::Vertical)
        return section;
    else
        return headers[section];
}

bool EssenceModel::setData(const QModelIndex& i, const QVariant& value, int role)
{
    if(i.column() != 1 || role != Qt::CheckStateRole) return false;
    m_disabled_essences[i.row()] = !m_disabled_essences[i.row()];
    emit dataChanged(index(i.row(), 0), index(i.row(), columnCount()), {role});
    return true;
}

Qt::ItemFlags EssenceModel::flags(const QModelIndex& index) const
{
    const auto parent_flags = QAbstractItemModel::flags(index);
    if(index.column() == 1) return parent_flags | Qt::ItemIsEditable | Qt::ItemIsUserCheckable;
    return parent_flags;
}

QVariant EssenceModel::essenceValue(const QModelIndex& index) const
{
    using LibChemistryHelper::Property;
    static const std::array<Property, 8> properties{Property::Ar, Property::As, Property::Bi, Property::Sa,
                                                    Property::So, Property::Sp, Property::Sw, Property::To};
    const auto& essence = m_essences[index.row()];
    if(index.column() == 0) return QString::fromStdString(essence.material);
    if(index.column() == 3) return essence.temperature ? QString::number(*essence.temperature) : QString();
    if(index.column() == 2) return QString::fromStdString(essence.recipe);
    const auto prop = essence.properties.at(properties[index.column() - 4]);
    return prop ? QString::number(*prop) : QString();
}
