#include "ChartDialog.h"

// Constructor for ChartDialog, takes a reference to ServiceAdmin and an optional parent widget
ChartDialog::ChartDialog(ServiceAdmin& serv, QWidget* parent)
    : QDialog(parent), service(serv)  // Initialize base QDialog and store reference to service
{
    setWindowTitle("Event Attendance Chart");
    setMinimumSize(700, 500);

    mainLayout = new QVBoxLayout(this);

    // Create the custom chart widget that will display the event data
    chartWidget = new EventChartWidget(this);
    mainLayout->addWidget(chartWidget);
    chartWidget->setEvents(service.get_all_events());

    closeButton = new QPushButton("Close", this);
    mainLayout->addWidget(closeButton);
    connect(closeButton, &QPushButton::clicked, this, &ChartDialog::accept);
}
