#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_A67_QT.h"

class A67_QT : public QMainWindow
{
    Q_OBJECT

public:
    A67_QT(QWidget *parent = nullptr);
    ~A67_QT();

private:
    Ui::A67_QTClass ui;
};
