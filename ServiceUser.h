#ifndef SERVICE_USER_H
#define SERVICE_USER_H

#include "ServiceAdmin.h"
#include "Event.h"
#include <vector>
#include <string>
#include "EventsList.h"

/**
 * @brief Service class for user operations
 *
 * This class provides functionality for users to browse and manage events,
 * including viewing events by month and maintaining a personal event list.
 */
class ServiceUser {
private:
    ServiceAdmin& adminService;    ///< Reference to the admin service
    std::vector<Event> userEvents; ///< User's personal list of events
    int currentEventIndex;         ///< Current position in the event list
    EventsList& eventslist;

public:
    /**
     * @brief Constructor
     * @param service Reference to the admin service
     * @post Creates a new user service with an empty event list
     */
    explicit ServiceUser(ServiceAdmin& service, EventsList& eventslist);

    /**
     * @brief Destructor
     */
    ~ServiceUser() = default;

    /**
     * @brief Gets all events from the admin service
     * @return Reference to the vector of events
     */
    const std::vector<Event>& get_all_events() const;

    /**
     * @brief Gets events for a specific month
     * @param month The month to filter by (format: "MM"), or empty string for all months
     * @return Vector containing the filtered events
     * @post If month is empty, events are ordered chronologically
     */
    std::vector<Event> get_events_by_month(const std::string& month) const;

    /**
     * @brief Gets the number of events in the admin service
     * @return The number of events
     */
    int get_number_of_events() const;

    /**
     * @brief Gets the current event from a filtered list
     * @param events The filtered list of events
     * @param position The current position in the list
     * @return Pointer to the current event, or nullptr if the list is empty
     * @post If position is out of bounds, it wraps around to the beginning
     */
    const Event* get_current_event(const std::vector<Event>& events, int& position) const;

    /**
     * @brief Adds an event to the user's list
     * @param event The event to add
     * @return true if successful, false if the event is already in the list
     * @post If successful, the event is added to the user's list
     */
    bool add_event_to_user_list(const Event& event);

    /**
     * @brief Removes an event from the user's list
     * @param event The event to remove
     * @return true if successful, false if the event is not in the list
     * @post If successful, the event is removed from the user's list
     */
    bool remove_event_from_user_list(const Event& event);

    /**
     * @brief Gets all events in the user's list
     * @return Reference to the user's event list
     */
    const std::vector<Event>& get_user_list() const;

    /**
     * @brief Extracts the month from a date string
     * @param date The date string in YYYY-MM-DD format
     * @return The month as a string (MM), or empty string if date is invalid
     */

    static std::string extract_month(const std::string& date);
    void add_event_to_eventslist(const Event& event);
    void display_eventslist() const;
};
#endif