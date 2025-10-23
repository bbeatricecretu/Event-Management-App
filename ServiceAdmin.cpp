// ServiceAdmin.cpp (updated version)
#include "ServiceAdmin.h"
#include "Validator.h"
#include "Exception.h"
#include "EventsList.h"
#include <algorithm>
#include <qforeach.h>
#include <qhash.h>

ServiceAdmin::ServiceAdmin(Repository& repo, EventsList& eventslist) : repo(repo), eventslist(eventslist) {
	this->validator = new EventValidator();
}

ServiceAdmin::~ServiceAdmin() {
    delete validator;
}

//ADD
void ServiceAdmin::add_event_to_service(const std::string& title, const std::string& description,
    const std::string& date, const std::string& link, int nrpeople)
{
    Event event(title, description, date, link, nrpeople);
    validator->validate(event);
  
    // Check if event already exists
    if (this->repo.find_event_position(event) != -1) {
        throw ServiceException("Event with same title and date already exists");
    }

    // Add event to repository
    auto action = std::make_unique<AddAction>(repo, event);
    actionManager.executeAction(std::move(action));

}

void ServiceAdmin::add_event_to_eventslist(const Event& e)
{
	this->eventslist.add(e);
}

void ServiceAdmin::display_eventslist() const
{
	this->eventslist.display();
}

//UPDATE
void ServiceAdmin::update_event_in_service(const std::string& title, const std::string& date,
    const std::string& new_title, const std::string& new_description,
    const std::string& new_date, const std::string& new_link, int new_nrpeople)
{
    // Find full old event
    int position = this->repo.find_event_position(Event(title, "", date, "", 0));
    if (position == -1)
        throw ServiceException("Event not found");

    Event old_event = *this->repo.get_event_by_index(position);
    Event new_event(new_title, new_description, new_date, new_link, new_nrpeople);
    validator->validate(new_event);

    if ((new_title != title || new_date != date) &&
        this->repo.find_event_position(new_event) != -1)
        throw ServiceException("An event with the new title and date already exists");

    auto action = std::make_unique<UpdateAction>(repo, old_event, new_event);
    actionManager.executeAction(std::move(action));
}


//DELETE
void ServiceAdmin::delete_event_from_service(const std::string& title, const std::string& date)
{
    int pos = this->repo.find_event_position(Event(title, "", date, "", 0));
    if (pos == -1)
        throw ServiceException("Event not found");

    Event full_event = *this->repo.get_event_by_index(pos);

    auto action = std::make_unique<DeleteAction>(repo, full_event);
    actionManager.executeAction(std::move(action));
}


const std::vector<Event>& ServiceAdmin::get_all_events() const
{
    return this->repo.get_all();
}

int ServiceAdmin::find_event_position_in_service(const Event& event)
{
    return this->repo.find_event_position(event);
}

int ServiceAdmin::get_number_of_events() const
{
    return this->repo.get_number_of_events();
}

Event* ServiceAdmin::get_event_by_position(int pos)
{
     return this->repo.get_event_by_index(pos);
}

std::vector<Event> ServiceAdmin::get_events_by_people_count(int people_count) const
{
       return this->repo.get_events_by_people_count(people_count);   
}

void ServiceAdmin::undo() {
    actionManager.undo();
}

void ServiceAdmin::redo() {
    actionManager.redo();
}