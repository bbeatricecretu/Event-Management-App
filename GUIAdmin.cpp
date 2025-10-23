#include "GUIAdmin.h"
#include "ChartDialog.h"
#include <QMessageBox>
#include <QShortcut>


GUIAdmin::GUIAdmin(ServiceAdmin& serv, QWidget* parent)
    : QWidget(parent), service(serv) {
    setup_ui(); // sets up all the user interface components: layout, widgets, buttons, etc.
    load_events(); //loads the existing events from the service
}

void GUIAdmin::setup_ui() 
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);  //The this pointer means the layout will be set inside the current widget (GUIAdmin).

    QFormLayout* formLayout = new QFormLayout();  //arranges widgets in a "label-edit" style
    titleEdit = new QLineEdit();  //input fields 
    descriptionEdit = new QLineEdit();
    dateEdit = new QLineEdit();
    linkEdit = new QLineEdit();
    peopleEdit = new QLineEdit();

    formLayout->addRow("Title:", titleEdit); //adds a label and a corresponding widget (here, QLineEdit) to the formLayout.
    formLayout->addRow("Description:", descriptionEdit);
    formLayout->addRow("Date (YYYY-MM-DD):", dateEdit);
    formLayout->addRow("Link:", linkEdit);
    formLayout->addRow("People:", peopleEdit);

    mainLayout->addLayout(formLayout); //formLayout will be insert first in mainLayout

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    addButton = new QPushButton("Add");  //Each button is labeled accordingly
    deleteButton = new QPushButton("Delete");
    updateButton = new QPushButton("Update");
    refreshButton = new QPushButton("Refresh");
    chartButton = new QPushButton("Show Chart");

    buttonLayout->addWidget(addButton);  //adds each button to the buttonLayout
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(updateButton);
    buttonLayout->addWidget(refreshButton);
    buttonLayout->addWidget(chartButton);
    mainLayout->addLayout(buttonLayout);

    table = new QTableWidget(); //table widget that displays data in a grid.
    table->setColumnCount(5); //5 columns
    QStringList headers{ "Title", "Description", "Date", "Link", "People" };
    table->setHorizontalHeaderLabels(headers);
    mainLayout->addWidget(table);

    undoButton = new QPushButton("Undo");
    redoButton = new QPushButton("Redo");
    // Ctrl+Z → Undo
    new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_Z), this, SLOT(undoAction()));

    // Ctrl+Y → Redo
    new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_Y), this, SLOT(redoAction()));

    buttonLayout->addWidget(undoButton);
    buttonLayout->addWidget(redoButton);
 

    //CONNECT is used to link user actions (like button clicks) to the corresponding functions (slots).
    // addButton: the button the user clicks.
    // &QPushButton::clicked: a pointer to the signal emitted when the button is clicked.
    // this = the receiver object that will handle the signal
    // &GUIAdmin::add_event: a pointer to the slot function

    connect(addButton, &QPushButton::clicked, this, &GUIAdmin::add_event);
    connect(deleteButton, &QPushButton::clicked, this, &GUIAdmin::delete_event);
    connect(updateButton, &QPushButton::clicked, this, &GUIAdmin::update_event);
    connect(refreshButton, &QPushButton::clicked, this, &GUIAdmin::load_events);
    connect(chartButton, &QPushButton::clicked, this, &GUIAdmin::show_chart);
    connect(undoButton, &QPushButton::clicked, this, &GUIAdmin::undoAction);
    connect(redoButton, &QPushButton::clicked, this, &GUIAdmin::redoAction);
}

void GUIAdmin::load_events() //function is used to populate a Qt table widget 
{
    table->setRowCount(0);
    auto events = service.get_all_events();

    int row = 0;
    for (const auto& ev : events) 
    {
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(ev.getTitle())));
        table->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(ev.getDescription())));
        table->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(ev.getDate())));
        table->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(ev.getLink())));
        table->setItem(row, 4, new QTableWidgetItem(QString::number(ev.getNrpeople())));
        row++;
    }
}
// QTableWidgetItem is the object that represents a single cell in a QTableWidget.
// fromStdString =  Converts a C++ std::string to a Qt-compatible QString.

void GUIAdmin::add_event() {
    try {
        service.add_event_to_service(
            titleEdit->text().toStdString(),
            descriptionEdit->text().toStdString(),
            dateEdit->text().toStdString(),
            linkEdit->text().toStdString(),
            peopleEdit->text().toInt()
        );
        load_events();
    }
    catch (const ApplicationException& e) {
        QMessageBox::warning(this, "Error", e.what());  //QMessageBox::warning(...)  This function displays a warning dialog to the user.
    }
}

void GUIAdmin::delete_event() {
    try {
        service.delete_event_from_service(
            titleEdit->text().toStdString(),
            dateEdit->text().toStdString()
        );
        load_events();
    }
    catch (const ApplicationException& e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}

void GUIAdmin::update_event() {
    try {
        service.update_event_in_service(
            titleEdit->text().toStdString(),
            dateEdit->text().toStdString(),
            titleEdit->text().toStdString(),
            descriptionEdit->text().toStdString(),
            dateEdit->text().toStdString(),
            linkEdit->text().toStdString(),
            peopleEdit->text().toInt()
        );
        load_events();
    }
    catch (const ApplicationException& e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}


void GUIAdmin::show_chart() {
    ChartDialog* chartDialog = new ChartDialog(service, this);
    chartDialog->setAttribute(Qt::WA_DeleteOnClose);
    chartDialog->exec();
}

void GUIAdmin::undoAction() {
    try {
        service.undo();
        load_events();
    }
    catch (std::exception& e) {
        QMessageBox::warning(this, "Undo Failed", e.what());
    }
}

void GUIAdmin::redoAction() {
    try {
        service.redo();
        load_events();
    }
    catch (std::exception& e) {
        QMessageBox::warning(this, "Redo Failed", e.what());
    }
}
