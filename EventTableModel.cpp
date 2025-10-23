#include "EventTableModel.h"

EventTableModel::EventTableModel(const std::vector<Event>& events, QObject* parent)
    : QAbstractTableModel(parent), events(events) {
}

int EventTableModel::rowCount(const QModelIndex&) const {
    return static_cast<int>(events.size());
}

int EventTableModel::columnCount(const QModelIndex&) const {
    return 5; // title, desc, date, link, people
}

QVariant EventTableModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || role != Qt::DisplayRole)
        return {};

    const Event& e = events[index.row()];
    switch (index.column()) {
    case 0: return QString::fromStdString(e.getTitle());
    case 1: return QString::fromStdString(e.getDescription());
    case 2: return QString::fromStdString(e.getDate());
    case 3: return QString::fromStdString(e.getLink());
    case 4: return e.getNrpeople();
    default: return {};
    }
}

QVariant EventTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole) return {};
    if (orientation == Qt::Horizontal) {
        switch (section) {
        case 0: return "Title";
        case 1: return "Description";
        case 2: return "Date";
        case 3: return "Link";
        case 4: return "People";
        }
    }
    return {};
}

void EventTableModel::updateData(const std::vector<Event>& newEvents) {
    beginResetModel();
    events = newEvents;
    endResetModel();
}
