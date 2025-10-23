#pragma once
#include <QAbstractTableModel>
#include "Event.h"
#include <vector>

class EventTableModel : public QAbstractTableModel {
    Q_OBJECT

private:
    std::vector<Event> events;

public:
    EventTableModel(const std::vector<Event>& events, QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    void updateData(const std::vector<Event>& newEvents);
};
