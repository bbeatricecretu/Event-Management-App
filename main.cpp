#include <QApplication>
#include <QInputDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include "Repo.h"
#include "FileRepository.h"
#include "EventsListCSV.h"
#include "EventsListHTML.h"
#include "ServiceAdmin.h"
#include "ServiceUser.h"
#include "GuiUser.h"
#include "GUIAdmin.h" 

void InitMemoryRepo(Repository& repo) {
    repo.add_event_repo(Event("TechCrunch Disrupt", "Annual technology conference", "2024-07-28", "https://techcrunch.com/events/tc-disrupt-2024/", 2000));
    repo.add_event_repo(Event("Art Basel Miami Beach", "International art fair", "2024-07-06", "https://www.artbasel.com/miami-beach", 1500));
    repo.add_event_repo(Event("Taste of London", "Culinary festival", "2024-06-19", "https://london.tastefestivals.com/", 3000));
    repo.add_event_repo(Event("FIBA Basketball World Cup", "International basketball competition", "2024-08-25", "https://www.fiba.basketball/basketballworldcup/2023", 2500));
    repo.add_event_repo(Event("Cannes Film Festival", "Prestigious international film festival", "2024-05-14", "https://www.festival-cannes.com/en/", 4000));
    repo.add_event_repo(Event("London Book Fair", "Global marketplace for rights negotiation", "2024-03-12", "https://www.londonbookfair.co.uk/", 2500));
    repo.add_event_repo(Event("World of Dance Championship", "International dance competition", "2024-07-27", "https://www.worldofdance.com/", 1800));
    repo.add_event_repo(Event("Red Cross Gala", "Annual fundraising event", "2024-11-15", "https://www.visitmonaco.com/en/grand-rendez-vous/22124/monaco-red-cross-gala", 1200));
    repo.add_event_repo(Event("Glastonbury Festival", "Five-day performing arts festival", "2024-06-26", "https://www.glastonburyfestivals.co.uk/", 5000));
    repo.add_event_repo(Event("South by Southwest", "Media/music/film festival", "2024-03-08", "https://www.sxsw.com/", 3500));
}

Repository* getRepoGUI(QWidget* parent) {
    QStringList options = { "Memory", "File" };
    bool ok;
    QString choice = QInputDialog::getItem(parent, "Select Repository", "Repository type:", options, 0, false, &ok);
    if (!ok)
        return nullptr;

    if (choice == "Memory") {
        Repository* repo = new MemoryRepository();
        InitMemoryRepo(*repo);
        return repo;
    }
    else {
        QString filename = QInputDialog::getText(parent, "File Repo", "Enter events file name:", QLineEdit::Normal, "events.txt", &ok);
        if (!ok || filename.isEmpty()) return nullptr;

        try {
            return new FileRepository(filename.toStdString());
        }
        catch (const ApplicationException& e) {
            QMessageBox::critical(parent, "Error", e.what());
            return nullptr;
        }
    }
}

EventsList* getPlaylistGUI(QWidget* parent) {
    QStringList options = { "CSV", "HTML" };
    bool ok;
    QString choice = QInputDialog::getItem(parent, "Select Playlist Type", "Choose format:", options, 0, false, &ok);
    if (!ok) return nullptr;

    if (choice == "CSV") {
        return new EventsCSV("events.csv");
    }
    else {
        return new EventsListHTML("events.html");
    }
}

int main(int argc, char* argv[]) 
{
    QApplication app(argc, argv);

    //INIT_WINDOW--------------------------------------------------
    QWidget initWindow;
    initWindow.setWindowTitle("Event Manager");

    Repository* repo = getRepoGUI(&initWindow);
    if (!repo) 
    {
        QMessageBox::critical(nullptr, "Error", "Failed to initialize repository.");
        return 1;
    }

    EventsList* playlist = getPlaylistGUI(&initWindow);
    if (!playlist) 
    {
        QMessageBox::critical(nullptr, "Error", "Failed to initialize playlist."); //Error  // nullptr = no parent
        delete repo;
        return 1;
    }

    ServiceAdmin adminService(*repo, *playlist);
    ServiceUser userService(adminService, *playlist);

    //MAIN_WINDOW-------------------------------------------------
    QWidget mainMenu;
    mainMenu.setWindowTitle("Event Manager - Main Menu");

    QVBoxLayout* layout = new QVBoxLayout(&mainMenu);
    QPushButton* btnAdmin = new QPushButton("Admin Mode");
    QPushButton* btnUser = new QPushButton("User Mode");
    QPushButton* btnExit = new QPushButton("Exit");

    layout->addWidget(btnAdmin);
    layout->addWidget(btnUser);
    layout->addWidget(btnExit);

	QObject::connect(btnAdmin, &QPushButton::clicked, [&]() { //lambda function gets executed when the signal click is emitted
        auto* guiAdmin = new GUIAdmin(adminService);
        guiAdmin->setAttribute(Qt::WA_DeleteOnClose); //When this window is closed, automatically delete the guiAdmin object from memory
        guiAdmin->setWindowTitle("Admin Interface");
        guiAdmin->resize(600, 400);
        guiAdmin->show(); //visible on screen 
        });

    QObject::connect(btnUser, &QPushButton::clicked, [&]() {
        auto* guiUser = new GUIUser(userService);
        guiUser->setAttribute(Qt::WA_DeleteOnClose);
        guiUser->setWindowTitle("User Interface");
        guiUser->resize(600, 400);
        guiUser->show();
        });

    QObject::connect(btnExit, &QPushButton::clicked, [&]() {
        mainMenu.close();
        });

    mainMenu.resize(300, 150);
    mainMenu.show();

	return app.exec(); //keep alive my app until the user closes it
}
