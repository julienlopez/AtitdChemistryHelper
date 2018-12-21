#pragma once

#include "libchemistryhelper/iessencesdatagatherer.hpp"

#include <QAbstractTableModel>

class EssenceModel : public QAbstractTableModel
{
    Q_OBJECT

    using EssenceContainer_t = LibChemistryHelper::IEssencesDataGatherer::Container_t;

public:
    explicit EssenceModel(EssenceContainer_t essences_, QObject* parent = nullptr);

    virtual ~EssenceModel() = default;

    const EssenceContainer_t& essences() const;

    virtual int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    virtual int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    virtual QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

private:
    EssenceContainer_t m_essences;
};