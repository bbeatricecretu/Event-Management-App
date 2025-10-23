#include "UiUser.h"
#include "ServiceUser.h"
#include <limits>
#include <cstdlib>
#include <algorithm>
#define NOMINMAX
#include <windows.h>

UiUser::UiUser(ServiceUser& serv) : service(serv) {}

UiUser::~UiUser() {}

void UiUser::print_menu_user() {
    std::cout << "\n";
    std::cout << "----------USER MENU------------\n";
    std::cout << "1. Browse events\n";
    std::cout << "2. View my events list\n";
    std::cout << "3. Remove an event from my list\n";
	std::cout << "4. Add all events to events list\n";
	std::cout << "5. Open events list in browser\n";
    std::cout << "0. Exit\n\n";
}

int UiUser::get_valid_integer(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number.\n";
        }
        else {
            std::cin.ignore();
            return value;
        }
    }
}

std::string UiUser::get_valid_string(const std::string& prompt) {
    std::string value;
    std::cout << prompt;
    std::getline(std::cin, value);
    return value;
}

void UiUser::open_in_browser(const std::string& link) {
    ShellExecuteA(NULL, "open", link.c_str(), NULL, NULL, SW_SHOWNORMAL);
}

void UiUser::browse_events() {
    std::string month = get_valid_string("Enter month (format: MM) or press Enter for all events chronologically: ");

    auto events = service.get_events_by_month(month);

    if (events.empty()) {
        std::cout << "No events found for the specified criteria.\n";
        return;
    }

    int currentPos = 0;
    bool browsing = true;

    while (browsing) {
        // Get current event (with circular navigation)
        const Event* currentEvent = service.get_current_event(events, currentPos);

        if (currentEvent == nullptr) {
            std::cout << "Error accessing event.\n";
            break;
        }

        // Display event details
        std::cout << "\n------ EVENT DETAILS ------\n";
        std::cout << currentEvent->toString() << "\n";
        std::cout << "---------------------------\n";

        // Open in browser
        std::cout << "Opening event in browser...\n";
        open_in_browser(currentEvent->getLink());

        // User options
        std::cout << "\nOptions:\n";
        std::cout << "1. Add to my list \n";
        std::cout << "2. Next event\n";
        std::cout << "3. Return to menu\n";

        int choice = get_valid_integer("Enter your choice: ");

        switch (choice) {
        case 1: 
        {
            bool success = service.add_event_to_user_list(*currentEvent);
            if (success) 
                std::cout << "Event added to your list successfully! Participant count increased.\n";
            
            else 
                std::cout << "Event is already in your list or couldn't be added.\n";
            
            currentPos++;
            break;
        }
        case 2:
            currentPos++;
            break;
        case 3:
            browsing = false;
            break;
        default:
            std::cout << "Invalid choice!\n";
            break;
        }
    }
}

void UiUser::view_my_list() 
{
    const auto& myList = service.get_user_list();

    if (myList.empty())
    {
        std::cout << "Your events list is empty.\n";
        return;
    }

    std::cout << "\n------ MY EVENTS LIST ------\n";
    int index = 1;
    for (const auto& event : myList) {
        std::cout << "\n" << index++ << ". " << event.toString() << "\n";
        std::cout << "---------------------------\n";
    }
}

void UiUser::remove_from_my_list() 
{
    const auto& myList = service.get_user_list();

    if (myList.empty()) {
        std::cout << "Your events list is empty.\n";
        return;
    }

    // Display list with numbers
    std::cout << "\n------ MY EVENTS LIST ------\n";
    int index = 1;
    for (const auto& event : myList) {
        std::cout << index++ << ". " << event.getTitle() << " - " << event.getDate() << "\n";
    }

    int choice = get_valid_integer("Enter the number of the event to remove (0 to cancel): ");

    if (choice == 0) {
        std::cout << "Operation cancelled.\n";
        return;
    }

    if (choice < 1 || choice > static_cast<int>(myList.size())) {
        std::cout << "Invalid event number!\n";
        return;
    }

    const Event& eventToRemove = myList[choice - 1];
    bool success = service.remove_event_from_user_list(eventToRemove);

    if (success) {
        std::cout << "Event removed from your list successfully!\n";
    }
    else {
        std::cout << "Failed to remove the event from your list.\n";
    }
}

void UiUser::exit_app() 
{
    std::cout << "Exiting user mode...\n";
}

void UiUser::add_all_events_to_eventslist() {
    const auto& userEvents = service.get_user_list();

    if (userEvents.empty()) {
        std::cout << "Your user list is empty. No events to add.\n";
        return;
    }

    for (const auto& event : userEvents) {
        service.add_event_to_eventslist(event);
    }

    std::cout << "All events from your user list have been added to the events list.\n";
}

void UiUser::start_user()
{
    int choice;
    bool running = true;

    while (running) 
    {
        print_menu_user();
        choice = get_valid_integer("Enter your choice: ");

        switch (choice) 
        {
            case 1:
                browse_events();
                break;
            case 2:
                view_my_list();
                break;
            case 3:
                remove_from_my_list();
                break;
			case 4:
				add_all_events_to_eventslist();
				break;
			case 5:
				service.display_eventslist();
				break;
            case 0:
                exit_app();
                running = false;
                break;
            default:
                std::cout << "Invalid choice!\n";
                break;
        }
    }
}