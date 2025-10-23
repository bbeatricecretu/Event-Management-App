// Repo.cpp (updated version)
#include "Repo.h"
#include "Event.h"
#include "Exception.h"
#include <iostream>
#include <algorithm>

// ADD
void MemoryRepository::add_event_repo(const Event& e)
{
    // Check if event already exists
    if (find_event_position(e) != -1) {
        throw RepositoryException("Event with same title and date already exists");
    }

    this->events.push_back(e);
}

// UPDATE
void MemoryRepository::update_event_repo(const Event& e, int position)
{
    if (position < 0 || position >= this->get_number_of_events()) {
        throw RepositoryException("Invalid event for update");
    }

    this->events[position] = e;
}

// DELETE
void MemoryRepository::delete_event_repo(const Event& e, int position)
{
    if (position < 0 || position >= this->get_number_of_events()) {
        throw RepositoryException("Invalid event for delete");
    }

    this->events.erase(this->events.begin() + position);
}

// GET ALL
const std::vector<Event>& MemoryRepository::get_all() const
{
    return this->events;
}

// GET NUMBER OF EVENTS
int MemoryRepository::get_number_of_events() const
{
    return static_cast<int>(this->events.size());
}

// GET EVENT BY INDEX
Event* MemoryRepository::get_event_by_index(int pos)
{
    if (pos < 0 || pos >= this->get_number_of_events()) {
        throw RepositoryException("Invalid event");
    }

    return &this->events[pos];
}

// FIND EVENT POSITION
int MemoryRepository::find_event_position(const Event& event)
{
    auto it = std::find_if(this->events.begin(), this->events.end(),
        [&event](const Event& e) { return e == event; });

    if (it != this->events.end()) {
        return static_cast<int>(std::distance(this->events.begin(), it));
    }
    return -1;
}

// GET EVENTS BY PEOPLE COUNT
std::vector<Event> MemoryRepository::get_events_by_people_count(int people_count) const
{
    if (people_count < 0) {
        throw RepositoryException("People count cannot be negative");
    }

    std::vector<Event> filtered_events;

    for (const auto& event : this->events) {
        if (event.getNrpeople() == people_count) {
            filtered_events.push_back(event);
        }
    }

    return filtered_events;
}