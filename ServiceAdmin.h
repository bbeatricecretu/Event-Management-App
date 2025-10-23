// ServiceAdmin.h
#pragma once
#include "Repo.h"
#include "Event.h"
#include "Action.h"
#include "ActionManager.h"
#include <string>
#include <vector>
#include "EventsList.h"

class EventValidator;

class ServiceAdmin {
private:
private:
    ActionManager actionManager;
    Repository& repo;
    EventValidator* validator;
    EventsList& eventslist;

public:
    ServiceAdmin(Repository& repo, EventsList &eventslist);
    ~ServiceAdmin();

    void add_event_to_service(const std::string& title, const std::string& description,
        const std::string& date, const std::string& link, int nrpeople);

    void add_event_to_eventslist(const Event& e);

	void display_eventslist() const;

    void update_event_in_service(const std::string& title, const std::string& date,
        const std::string& new_title, const std::string& new_description,
        const std::string& new_date, const std::string& new_link, int new_nrpeople);

    void delete_event_from_service(const std::string& title, const std::string& date);

    const std::vector<Event>& get_all_events() const;

    int find_event_position_in_service(const Event& event);

    int get_number_of_events() const;

    Event* get_event_by_position(int pos);

    void undo();
    void redo();


    std::vector<Event> get_events_by_people_count(int people_count) const;

};