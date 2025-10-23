#include "ServiceUser.h"
#include <regex>
#include <algorithm>

ServiceUser::ServiceUser(ServiceAdmin& service, EventsList& eventslist)
    : adminService(service), eventslist(eventslist), currentEventIndex(0) {
}


const std::vector<Event>& ServiceUser::get_all_events() const {
    return adminService.get_all_events();
}

// Comparison function for event dates
bool compareDates(const Event& e1, const Event& e2) {
    return e1.getDate() < e2.getDate();
}

std::vector<Event> ServiceUser::get_events_by_month(const std::string& month) const 
{
    std::vector<Event> filteredEvents;
    const auto& allEvents = adminService.get_all_events();

    if (month.empty()) {
        // Return all events if no month specified
        filteredEvents = allEvents;
    }
    else {
        // Filter events by month
        std::copy_if(allEvents.begin(), allEvents.end(), std::back_inserter(filteredEvents),
            [this, &month](const Event& event) {
                return extract_month(event.getDate()) == month;
            });
    }

    // Sort events chronologically by date
    std::sort(filteredEvents.begin(), filteredEvents.end(), compareDates);
    return filteredEvents;
}

int ServiceUser::get_number_of_events() const 
{
    return adminService.get_number_of_events();
}

const Event* ServiceUser::get_current_event(const std::vector<Event>& events, int& position) const {
    if (events.empty()) 
        return nullptr;
    
    // Ensure position is in range using modulo (circular navigation)
    position = position % events.size();
    return &events[position];
}

bool ServiceUser::add_event_to_user_list(const Event& event) 
{
    // Check if event already exists in user list
    if (std::find_if(userEvents.begin(), userEvents.end(),
        [&event](const Event& e) { return e == event; }) != userEvents.end()) {
        return false;
    }

    // Find and update the event in the admin repository
    const auto& allEvents = adminService.get_all_events();
    auto it = std::find_if(allEvents.begin(), allEvents.end(),
        [&event](const Event& e) { return e == event; });

    if (it != allEvents.end()) {
        // Create a new event with incremented people count
        Event updatedEvent = *it;
        int oldPeopleCount = it->getNrpeople();
        int newPeopleCount = oldPeopleCount + 1;
        updatedEvent.setNrpeople(newPeopleCount);

        // Update the event in the repository
        adminService.update_event_in_service(
            it->getTitle(), it->getDate(),
            it->getTitle(), it->getDescription(), it->getDate(), it->getLink(), newPeopleCount
        );

        // Add the updated event to user's list
        userEvents.push_back(updatedEvent);
        return true;
    }

    return false;
}

bool ServiceUser::remove_event_from_user_list(const Event& event) {
    auto userIt = std::find_if(userEvents.begin(), userEvents.end(),
        [&event](const Event& e) { return e == event; });

    if (userIt != userEvents.end()) {
        // Find and update the event in the admin repository
        const auto& allEvents = adminService.get_all_events();
        auto adminIt = std::find_if(allEvents.begin(), allEvents.end(),
            [&event](const Event& e) { return e == event; });

        if (adminIt != allEvents.end()) {
            // Create a new event with decremented people count
            int oldPeopleCount = adminIt->getNrpeople();
            int newPeopleCount = oldPeopleCount - 1;

            // Update the event in the repository
            adminService.update_event_in_service(
                adminIt->getTitle(), adminIt->getDate(),
                adminIt->getTitle(), adminIt->getDescription(), adminIt->getDate(), adminIt->getLink(), newPeopleCount
            );
        }

        userEvents.erase(userIt);
        return true;
    }
    return false;
}

const std::vector<Event>& ServiceUser::get_user_list() const 
{
    return userEvents;
}

std::string ServiceUser::extract_month(const std::string& date) {
    // Extract month from yyyy-mm-dd format
    std::regex datePattern("^(\\d{4})-(\\d{2})-(\\d{2})$");
    std::smatch matches;

    if (std::regex_match(date, matches, datePattern) && matches.size() > 2) {
        return matches[2].str(); // Return the month part
    }

    return "";
}

// Add an event to the events list
void ServiceUser::add_event_to_eventslist(const Event& event) {
    // Add the event to the events list
    eventslist.add(event);
}

// Display the events list
void ServiceUser::display_eventslist() const {
    // Display the events list
    eventslist.display();
}