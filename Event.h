#pragma once
#include <string>
#include <istream>
#include <ostream>

/**
 * @brief Represents an event with title, description, date, link, and number of people
 */
class Event
{
private:
	std::string title;      ///< The title of the event
	std::string description;///< A description of the event
	std::string date;       ///< The date of the event in YYYY-MM-DD format
	std::string link;       ///< A link to the event
	int nrpeople;          ///< The number of people attending the event

public:
	/**
	 * @brief Default constructor
	 * @post Creates an empty event with default values
	 */
	Event();

	/**
	 * @brief Constructor with parameters
	 * @param title The title of the event
	 * @param description A description of the event
	 * @param date The date of the event in YYYY-MM-DD format
	 * @param link A link to the event
	 * @param nrpeople The number of people attending the event
	 * @post Creates an event with the specified values
	 */
	Event(const std::string& title, const std::string& description, const std::string& date, const std::string& link, const int nrpeople);

	/**
	 * @brief Gets the title of the event
	 * @return The title of the event
	 */
	std::string getTitle() const;

	/**
	 * @brief Gets the description of the event
	 * @return The description of the event
	 */
	std::string getDescription() const;

	/**
	 * @brief Gets the date of the event
	 * @return The date of the event in YYYY-MM-DD format
	 */
	std::string getDate() const;

	/**
	 * @brief Gets the link to the event
	 * @return The link to the event
	 */
	std::string getLink() const;

	/**
	 * @brief Gets the number of people attending the event
	 * @return The number of people attending the event
	 */
	int getNrpeople() const;

	/**
	 * @brief Sets the title of the event
	 * @param title The new title
	 * @post The title is set to the new value
	 */
	void setTitle(const std::string& title);

	/**
	 * @brief Sets the description of the event
	 * @param description The new description
	 * @post The description is set to the new value
	 */
	void setDescription(const std::string& description);

	/**
	 * @brief Sets the date of the event
	 * @param date The new date in YYYY-MM-DD format
	 * @post The date is set to the new value
	 */
	void setDate(const std::string& date);

	/**
	 * @brief Sets the link to the event
	 * @param link The new link
	 * @post The link is set to the new value
	 */
	void setLink(const std::string& link);

	/**
	 * @brief Sets the number of people attending the event
	 * @param nrpeople The new number of people
	 * @post The number of people is set to the new value
	 */
	void setNrpeople(const int nrpeople);

	/**
	 * @brief Destructor
	 * @post The event is destroyed
	 */
	~Event();

	/**
	 * @brief Assignment operator
	 * @param e The event to copy from
	 * @return Reference to this event
	 * @post This event is a copy of e
	 */
	Event& operator=(const Event& e);

	/**
	 * @brief Equality operator
	 * @param e The event to compare with
	 * @return true if the events have the same title and date, false otherwise
	 */
	bool operator==(const Event& e) const;

	/**
	 * @brief Creates a string representation of the event
	 * @return A string containing all event details
	 */
	std::string toString() const;

	/**
	 * @brief Validates the event
	 * @param e The event to validate
	 * @return true if the event is valid, false otherwise
	 * @pre An event is valid if:
	 *      - title is not empty
	 *      - description is not empty
	 *      - date is in YYYY-MM-DD format
	 *      - link is not empty
	 *      - nrpeople is non-negative
	 */
	bool validate(const Event& e);

	friend std::istream& operator >> (std::istream& is, Event& event);
	friend std::ostream& operator << (std::ostream& os, const Event& event);
};