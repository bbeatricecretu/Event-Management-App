#include "GUIUser.h"
#include "ServiceUser.h"
#include "UserListWindow.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QDesktopServices>
#include <QUrl>

GUIUser::GUIUser(ServiceUser& serv, QWidget* parent)
    : QWidget(parent), service(serv) {
    setupUI();
}

GUIUser::~GUIUser() {}

void GUIUser::setupUI() {
    mainLayout = new QVBoxLayout(this);

    QLabel* titleLabel = new QLabel("User Menu", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titleLabel);

    browseButton = new QPushButton("Browse Events", this);
    viewListButton = new QPushButton("View My Events List", this);
    removeButton = new QPushButton("Remove Event from My List", this);
    addAllButton = new QPushButton("Add All Events to Events List", this);
    openFileButton = new QPushButton("Open Events List File", this); 
    exitButton = new QPushButton("Exit", this);
    showTableButton = new QPushButton("Show Events Table");
    

    mainLayout->addWidget(browseButton);
    mainLayout->addWidget(viewListButton);
    mainLayout->addWidget(removeButton);
    mainLayout->addWidget(addAllButton);
    mainLayout->addWidget(openFileButton); 
    mainLayout->addWidget(exitButton);
    mainLayout->addWidget(showTableButton);

    eventListWidget = new QListWidget(this);
    mainLayout->addWidget(eventListWidget);

    monthInput = new QLineEdit(this);
    monthInput->setPlaceholderText("Enter month (MM) or leave empty for all events");
    mainLayout->addWidget(monthInput);


    connect(browseButton, &QPushButton::clicked, this, &GUIUser::browseEvents);
    connect(viewListButton, &QPushButton::clicked, this, &GUIUser::viewMyList);
    connect(removeButton, &QPushButton::clicked, this, &GUIUser::removeFromMyList);
    connect(addAllButton, &QPushButton::clicked, this, &GUIUser::addAllEventsToList);
    connect(openFileButton, &QPushButton::clicked, this, &GUIUser::displayMyListInFormat); 
    connect(exitButton, &QPushButton::clicked, this, &GUIUser::exitApp);

    connect(showTableButton, &QPushButton::clicked, this, &GUIUser::openUserListTable);
}

void GUIUser::populateEventList(const std::vector<Event>& events) 
{
    eventListWidget->clear();
    for (const auto& event : events) 
        eventListWidget->addItem(QString::fromStdString(event.toString()));
    
}
// Updated browseEvents method to ensure table refreshes
void GUIUser::browseEvents()
{
    QString month = monthInput->text();
    auto events = service.get_events_by_month(month.toStdString());

    if (events.empty()) {
        QMessageBox::information(this, "No Events", "No events found for the specified criteria.");
        return;
    }

    int currentIndex = 0;
    while (currentIndex < static_cast<int>(events.size()))
    {
        const Event& currentEvent = events[currentIndex];

        // Display event details
        QString eventDetails = QString::fromStdString(currentEvent.toString());
        QMessageBox::information(this, "Event Details", eventDetails);

        // Open the event's URL in the default browser
        QDesktopServices::openUrl(QUrl(QString::fromStdString(currentEvent.getLink())));

        // Ask the user if they want to add the event to their list or move to the next event
        QMessageBox::StandardButton choice = QMessageBox::question(
            this,
            "Add Event",
            "Do you want to add this event to your list?",
            QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel
        );

        if (choice == QMessageBox::Yes) {
            if (service.add_event_to_user_list(currentEvent)) {
                // Refresh table if it's open
                if (tableWindow) {
                    tableWindow->updateModel(service.get_user_list());
                }
                QMessageBox::information(this, "Success", "Event added to your list.");
            }
            else {
                QMessageBox::warning(this, "Failure", "Event is already in your list.");
            }
        }
        else if (choice == QMessageBox::Cancel) {
            break; // Exit browsing
        }

        // Move to the next event
        currentIndex++;
    }
}

void GUIUser::viewMyList() {
    const auto& myList = service.get_user_list();

    if (myList.empty()) {
        QMessageBox::information(this, "My Events List", "Your events list is empty.");
        return;
    }

    populateEventList(myList);
}


// Updated removeFromMyList method to ensure table refreshes
void GUIUser::removeFromMyList() {
    const auto& myList = service.get_user_list();

    if (myList.empty()) {
        QMessageBox::information(this, "Remove Event", "Your events list is empty.");
        return;
    }

    QStringList eventDescriptions;
    for (const auto& event : myList) {
        eventDescriptions << QString::fromStdString(event.toString());
    }

    bool ok;
    QString selectedEvent = QInputDialog::getItem(this, "Remove Event",
        "Select the event to remove:", eventDescriptions, 0, false, &ok);

    if (ok && !selectedEvent.isEmpty()) {
        int index = eventDescriptions.indexOf(selectedEvent);
        const Event& eventToRemove = myList[index];

        if (service.remove_event_from_user_list(eventToRemove)) {
            // Refresh table if it's open
            if (tableWindow) {
                tableWindow->updateModel(service.get_user_list());
            }
            QMessageBox::information(this, "Success", "Event removed successfully.");
        }
        else {
            QMessageBox::warning(this, "Failure", "Failed to remove the event.");
        }
    }
}

void GUIUser::addAllEventsToList() {
    const auto& userEvents = service.get_user_list();

    if (userEvents.empty()) {
        QMessageBox::information(this, "Add All Events", "Your user list is empty. No events to add.");
        return;
    }

    for (const auto& event : userEvents) {
        service.add_event_to_eventslist(event);
    }

    QMessageBox::information(this, "Success", "All events have been added to the events list.");
}



void GUIUser::exitApp() 
{
    QMessageBox::information(this, "Exit", "Exiting user mode...");
    close();
}

void GUIUser::displayMyListInFormat()
{
    service.display_eventslist();
}
void GUIUser::openUserListTable() {
    std::vector<Event> events = service.get_user_list();
    if (!tableWindow) {
        tableWindow = new UserListWindow(events);
        tableWindow->setAttribute(Qt::WA_DeleteOnClose);
        connect(tableWindow, &QObject::destroyed, this, [this]() { tableWindow = nullptr; });
        tableWindow->show();
    }
    else {
        tableWindow->raise();
        tableWindow->activateWindow();
        tableWindow->updateModel(events);
    }
}
