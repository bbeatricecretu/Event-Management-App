#pragma once

#include <QWidget>       //base class for all UI elements 
#include <QPushButton>   //button widget -add/remove...
#include <QLineEdit>     //text input field
#include <QTableWidget>  //table for displaying events
#include <QVBoxLayout>   //vertical layout manager
#include <QFormLayout>   //form layout manager
#include <QHBoxLayout>   //horizontal layout manager
#include <QLabel>        //label widget
#include "ServiceAdmin.h"

class GUIAdmin : public QWidget {
    Q_OBJECT;                // macro to enable Qt's signal and slot mechanism 

private:
    ServiceAdmin& service;

    QLineEdit* titleEdit;
    QLineEdit* descriptionEdit;
    QLineEdit* dateEdit;
    QLineEdit* linkEdit;
    QLineEdit* peopleEdit;
    QTableWidget* table;

    QPushButton* addButton;
    QPushButton* deleteButton;
    QPushButton* updateButton;
    QPushButton* refreshButton;
    QPushButton* chartButton;

    QPushButton* undoButton;
    QPushButton* redoButton;

    void setup_ui();
    void load_events();

private slots: // only accessible within the class itself
    void add_event();
    void delete_event();
    void update_event();
	void show_chart();
    void undoAction();
    void redoAction();

public:
    GUIAdmin(ServiceAdmin& serv, QWidget* parent = nullptr); //teh default parent is nullptr
};
