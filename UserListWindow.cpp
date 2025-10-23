#include "UserListWindow.h"

UserListWindow::UserListWindow(const std::vector<Event>& events, QWidget* parent)
    : QWidget(parent) {
    QVBoxLayout* layout = new QVBoxLayout(this);
    model = new EventTableModel(events, this);
    tableView = new QTableView(this);
    tableView->setModel(model);
    tableView->resizeColumnsToContents();

    layout->addWidget(tableView);
    setLayout(layout);
    setWindowTitle("User Events List");
    resize(600, 300);
}

void UserListWindow::updateModel(const std::vector<Event>& updatedEvents) {
    model->updateData(updatedEvents);
}
