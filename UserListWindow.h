#pragma once
#include <QWidget>
#include <QTableView>
#include <QVBoxLayout>
#include "ServiceUser.h"
#include "EventTableModel.h"

class UserListWindow : public QWidget {
    Q_OBJECT

private:
    QTableView* tableView;
    EventTableModel* model;

public:
    UserListWindow(const std::vector<Event>& events, QWidget* parent = nullptr);
    void updateModel(const std::vector<Event>& updatedEvents);
};
