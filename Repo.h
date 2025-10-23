#ifndef REPO_H
#define REPO_H

#include <vector>
#include "Event.h"
#include "Exception.h"

class Repository {
public:
    virtual void add_event_repo(const Event& e) = 0;
    virtual void update_event_repo(const Event& e, int pos) = 0;
    virtual void delete_event_repo(const Event& e, int pos) = 0;
    virtual const std::vector<Event>& get_all() const = 0;
    virtual int get_number_of_events() const = 0;
    virtual Event* get_event_by_index(int pos) = 0;
    virtual int find_event_position(const Event& event) = 0;
    virtual std::vector<Event> get_events_by_people_count(int people_count) const = 0;
    virtual ~Repository() = default;
};

/**
 * @brief Repository class for managing events
 *
 * This class provides functionality to store, retrieve, and manage events.
 * It uses a vector to store the events.
 */
class MemoryRepository : public Repository {
private:
    std::vector<Event> events;  ///< Vector storing the events

public:
    MemoryRepository() = default;
    ~MemoryRepository() = default;

    void add_event_repo(const Event& e) override;
    void update_event_repo(const Event& e, int pos) override;
    void delete_event_repo(const Event& e, int pos) override;
    const std::vector<Event>& get_all() const override;
    int get_number_of_events() const override;
    Event* get_event_by_index(int pos) override;
    int find_event_position(const Event& event) override;
    std::vector<Event> get_events_by_people_count(int people_count) const override;
};

#endif // REPO_H