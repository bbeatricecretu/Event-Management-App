// UiAdmin.cpp (updated version)
#include "UiAdmin.h"
#include "Exception.h"
#include <limits>
#include <iostream>
#include <algorithm>

UiAdmin::UiAdmin(ServiceAdmin& serv) : service(serv) {}

UiAdmin::~UiAdmin() {}

void UiAdmin::print_menu_admin()
{
    std::cout << "\n";
    std::cout << "----------MENU------------\n";
    std::cout << "1. Add an event.\n";
    std::cout << "2. Delete an event.\n";
    std::cout << "3. Update an event.\n";
    std::cout << "4. Print all events.\n";
    std::cout << "5. Filter events by number of people.\n";
    std::cout << "0. Exit.\n\n";
}

int UiAdmin::get_valid_integer(const std::string& prompt)
{
    int value;
    while (true)
    {
        std::cout << prompt;
        std::cin >> value;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number.\n";
        }
        else
        {
            std::cin.ignore();
            return value;
        }
    }
}

void UiAdmin::choice_1()
{
    std::string title, description, date, link;
    int nrpeople;

    std::cout << "Enter the title: ";
    std::getline(std::cin, title);
    std::cout << "Enter the description: ";
    std::getline(std::cin, description);
    std::cout << "Enter the date (YYYY-MM-DD): ";
    std::getline(std::cin, date);
    std::cout << "Enter the link: ";
    std::getline(std::cin, link);
    nrpeople = get_valid_integer("Enter the number of people: ");

    std::cout << "\n";

    try {
        service.add_event_to_service(title, description, date, link, nrpeople);
        std::cout << "Event added successfully!\n";
    }
    catch (const ApplicationException& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void UiAdmin::choice_2()
{
    std::string title, date;

    std::cout << "Enter the title of the event to delete: ";
    std::getline(std::cin, title);
    std::cout << "Enter the date of the event to delete (YYYY-MM-DD): ";
    std::getline(std::cin, date);
    std::cout << "\n";
    try {
        service.delete_event_from_service(title, date);
        std::cout << "Event deleted successfully!\n";
    }
    catch (const ApplicationException& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void UiAdmin::choice_3()
{
    std::string title, date, new_title, new_description, new_date, new_link;
    int new_nrpeople;

    std::cout << "Enter the title of the event to update: ";
    std::getline(std::cin, title);
    std::cout << "Enter the date of the event to update (YYYY-MM-DD): ";
    std::getline(std::cin, date);

    std::cout << "Enter the new title: ";
    std::getline(std::cin, new_title);
    std::cout << "Enter the new description: ";
    std::getline(std::cin, new_description);
    std::cout << "Enter the new date (YYYY-MM-DD): ";
    std::getline(std::cin, new_date);
    std::cout << "Enter the new link: ";
    std::getline(std::cin, new_link);
    new_nrpeople = get_valid_integer("Enter the new number of people: ");
    std::cout << "\n";
    try {
        service.update_event_in_service(title, date, new_title, new_description, new_date, new_link, new_nrpeople);
        std::cout << "Event updated successfully!\n";
    }
    catch (const ApplicationException& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void UiAdmin::choice_4()
{
    std::vector<Event> events = this->service.get_all_events();
    if (events.empty())
    {
        std::cout << "There are no events.\n";
        return;
    }
    std::cout << "\n";
    std::cout << "All events:\n";
    for (const Event& event : events)
        std::cout << event.toString() << "\n\n";
}

void UiAdmin::choice_5()
{
    int people_count = get_valid_integer("Enter number of people to filter by: ");
    std::cout << "\n";
    try {
        const auto filtered_events = service.get_events_by_people_count(people_count);

        if (filtered_events.empty())
            std::cout << "No events found with " << people_count << " people." << std::endl;
        else {
            std::cout << "Events with " << people_count << " people:" << std::endl;
            for (const auto& event : filtered_events) {
                std::cout << "\n" << event.toString() << "\n";
                std::cout << "------------------------" << std::endl;
            }
        }
    }
    catch (const ApplicationException& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void UiAdmin::choice_6() 
{
	const auto& all_events = service.get_all_events();
	for (const auto& event : all_events) {
		service.add_event_to_eventslist(event);
	}
	std::cout << "All events added to the events list successfully!\n";
}

void UiAdmin::choice_7()
{
	service.display_eventslist();
}

void UiAdmin::choice_0() {
    std::cout << "Exiting...\n";
}

void UiAdmin::start_admin() {
    int choice;
    bool ok = true;

    while (ok) {
        print_menu_admin();
        choice = get_valid_integer("Enter your choice: ");

        switch (choice) {
        case 1:
            choice_1();
            break;
        case 2:
            choice_2();
            break;
        case 3:
            choice_3();
            break;
        case 4:
            choice_4();
            break;
        case 5:
            choice_5();
            break;
        case 6:
            choice_6();
            break;
		case 7:
			choice_7();
			break;
        case 0:
            choice_0();
            ok = false;
            break;
        default:
            std::cout << "Invalid choice!\n";
            break;
        }
    }
}