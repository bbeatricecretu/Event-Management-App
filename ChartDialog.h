#ifndef CHARTDIALOG_H
#define CHARTDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QPushButton>
#include "EventChartEvent.h"
#include "ServiceAdmin.h"

class ChartDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChartDialog(ServiceAdmin& service, QWidget* parent = nullptr);

private:
    EventChartWidget* chartWidget;
    QPushButton* closeButton;
    QVBoxLayout* mainLayout;
    ServiceAdmin& service;
};

#endif // CHARTDIALOG_H