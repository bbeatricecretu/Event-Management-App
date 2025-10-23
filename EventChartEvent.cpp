#include "EventChartEvent.h"
#include <QFontMetrics>
#include <QPainterPath>
#include <QToolTip>
#include <QMouseEvent>
#include <algorithm>

EventChartWidget::EventChartWidget(QWidget* parent)
    : QWidget(parent)
{
    setMinimumSize(750, 450); // Increased width to accommodate legend
    setMouseTracking(true); // Enable mouse tracking for tooltips
    initColors();
}

void EventChartWidget::initColors()
{
    colors = {
        QColor(192, 57, 43),    // Dark Red
        QColor(142, 68, 173),   // Deep Purple
        QColor(243, 156, 18),   // Amber
        QColor(22, 160, 133),   // Sea Green
        QColor(127, 140, 141),  // Gray
        QColor(149, 165, 166),  // Light Gray
        QColor(44, 62, 80),     // Navy
        QColor(52, 73, 94),     // Charcoal
        QColor(189, 195, 199),  // Silver
        QColor(127, 255, 0),    // Chartreuse
        QColor(255, 105, 180),  // Hot Pink
        QColor(255, 140, 0),    // Dark Orange 2
        QColor(70, 130, 180),   // Steel Blue
        QColor(100, 149, 237),  // Cornflower Blue
        QColor(0, 206, 209),    // Dark Turquoise
        QColor(124, 252, 0),    // Lawn Green
        QColor(255, 215, 0),    // Gold
        QColor(255, 69, 0)      // Orange Red
    };
}

void EventChartWidget::setEvents(const std::vector<Event>& newEvents)
{
    events = newEvents;
    eventColorList.clear();

    for (size_t i = 0; i < events.size(); ++i) 
    {
        QString title = QString::fromStdString(events[i].getTitle());
        QColor color = colors[i % colors.size()];
        eventColorList.emplace_back(title, color);
    }

    update(); // Request repaint
}
void EventChartWidget::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);
    if (events.empty()) return;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QFont font = painter.font();
    font.setPointSize(10);
    painter.setFont(font);
    QFontMetrics fm(font);

    int margin = 50;
    int chartWidth = width() - 2 * margin - 150;
    int chartHeight = height() - 2 * margin;
    int barSpace = chartWidth / events.size();
    int barWidth = std::min(40, barSpace - 10);

    // Find max people count
    int maxPeople = 1;
    for (const auto& e : events)
        maxPeople = std::max(maxPeople, e.getNrpeople());

    // Draw Y-axis and labels
    painter.drawLine(margin, margin, margin, margin + chartHeight);
    painter.drawLine(margin, margin + chartHeight, margin + chartWidth, margin + chartHeight);

    for (int i = 0; i <= 5; ++i) {
        int y = margin + chartHeight - (i * chartHeight / 5);
        int val = i * maxPeople / 5;
        painter.drawText(margin - 30, y + 5, QString::number(val));
        painter.setPen(QPen(Qt::lightGray, 1, Qt::DashLine));
        painter.drawLine(margin, y, margin + chartWidth, y);
        painter.setPen(Qt::black);
    }

    // Draw bars
    for (size_t i = 0; i < events.size(); ++i) {
        const auto& e = events[i];
        int x = margin + i * barSpace + 5;
        int h = (e.getNrpeople() * chartHeight) / maxPeople;
        int y = margin + chartHeight - h;

        QColor color = colors[i % colors.size()];
        painter.setBrush(color);
        painter.drawRect(x, y, barWidth, h);

        // Draw number label below bar
        painter.drawText(x + barWidth / 4, margin + chartHeight + 15, QString::number(i + 1));
    }

    // Draw simple legend
    int lx = margin + chartWidth + 20;
    int ly = margin;
    painter.setFont(QFont("Arial", 9));
    for (size_t i = 0; i < eventColorList.size(); ++i) {
        QString label = QString::number(i + 1) + ": " + eventColorList[i].first;
        painter.setPen(Qt::black);
        painter.drawText(lx, ly + i * 20, label);
    }

    // Chart title
    QFont titleFont = font;
    titleFont.setPointSize(14);
    titleFont.setBold(true);
    painter.setFont(titleFont);
    painter.drawText((width() - fm.horizontalAdvance("Event Chart")) / 2, margin - 20, "Event Chart");
}
