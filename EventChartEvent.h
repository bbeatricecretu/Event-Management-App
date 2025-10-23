
#ifndef EVENTCHARTWIDGET_H
#define EVENTCHARTWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QColor>
#include <vector>
#include "Event.h"

class EventChartWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EventChartWidget(QWidget* parent = nullptr);
    void setEvents(const std::vector<Event>& events);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    std::vector<Event> events;
    std::vector<QColor> colors;
    std::vector<std::pair<QString, QColor>> eventColorList;
    void initColors();
};

#endif // EVENTCHARTWIDGET_H