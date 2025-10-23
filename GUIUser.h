#pragma once

#include <QWidget>
#include <QPushButton>
#include <QListWidget>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include "ServiceUser.h"
#include "UserListWindow.h"
/**
 * @brief GUI-based user interface for user operations
 *
 * This class provides a graphical interface for users to browse and manage events.
 */
class GUIUser : public QWidget {
    Q_OBJECT

private:
    ServiceUser& service; ///< Reference to the user service

    // UI Components
    QVBoxLayout* mainLayout;
    QPushButton* browseButton;
    QPushButton* viewListButton;
    QPushButton* removeButton;
    QPushButton* addAllButton;
    QPushButton* exitButton;
    QPushButton* openFileButton;
    QPushButton* displayFormatButton;
    QListWidget* eventListWidget;
    QLineEdit* monthInput;


    QPushButton* showTableButton;
    UserListWindow* tableWindow = nullptr;


    /**
     * @brief Sets up the UI components
     */
    void setupUI();

    /**
     * @brief Populates the event list widget with events
     * @param events The list of events to display
     */
    void populateEventList(const std::vector<Event>& events);

private slots:
    void browseEvents();
    void viewMyList();
    void removeFromMyList();
    void addAllEventsToList();
    void exitApp();
    void displayMyListInFormat();
    void openUserListTable();


public:
    /**
     * @brief Constructor
     * @param service Reference to the user service
     */
    GUIUser(ServiceUser& service, QWidget* parent = nullptr);

    /**
     * @brief Destructor
     */
    ~GUIUser();
};