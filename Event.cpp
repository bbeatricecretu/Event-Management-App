#include "Event.h"
#include <regex>
#include <ostream>
#include <istream>
#include <sstream>
#include <string>

// Default constructor
Event::Event()
{
	this->title = "";
	this->description = "";
	this->date = "";
	this->link = "";
	this->nrpeople = 0;
}

// Constructor with parameters
Event::Event(const std::string& title, const std::string& description, const std::string& date, const std::string& link, const int nrpeople)
{
	this->title = title;
	this->description = description;
	this->date = date;
	this->link = link;
	this->nrpeople = nrpeople;
}

// Getters
std::string Event::getTitle() const
{
	return this->title;
}

std::string Event::getDescription() const
{
	return this->description;
}

std::string Event::getDate() const
{
	return this->date;
}

std::string Event::getLink() const
{
	return this->link;
}

int Event::getNrpeople() const
{
	return this->nrpeople;
}

// Setters
void Event::setTitle(const std::string& title)
{
	this->title = title;
}

void Event::setDescription(const std::string& description)
{
	this->description = description;
}

void Event::setDate(const std::string& date)
{
	this->date = date;
}

void Event::setLink(const std::string& link)
{
	this->link = link;
}

void Event::setNrpeople(const int nrpeople)
{
	this->nrpeople = nrpeople;
}

// Destructor
Event::~Event() {}

// Assignment operator
Event& Event::operator=(const Event& e)
{
	if (this == &e)
		return *this;
	this->title = e.title;
	this->description = e.description;
	this->date = e.date;
	this->link = e.link;
	this->nrpeople = e.nrpeople;
	return *this;
}

// Equality operator
bool Event::operator==(const Event& other) const
{
	return (this->title == other.title && this->date == other.date);
}

// String representation of the event
std::string Event::toString() const
{
	return "Title: " + title + "\nDescription: " + description + "\nDate: " + date + "\nLink: " + link + "\nNumber of people: " + std::to_string(nrpeople);
}

//Validate the event
bool Event::validate(const Event& e)
{
	if (e.title.size() == 0)
		return false;
	if (e.description.size() == 0)
		return false;

	// Regex for date format yyyy-mm-dd
	std::regex date_pattern(R"(^\d{4}-\d{2}-\d{2}$)");
	if (!std::regex_match(e.date, date_pattern))
		return false;

	if (e.link.size() == 0)
		return false;
	if (e.nrpeople < 0)
		return false;
	return true;
}


/*
	Tokenizes a string.
	Input:	str - the string to be tokenized.
			delimiter - char - the delimiter used for tokenization
	Output: a vector of strings, containing the tokens
*/

std::vector<std::string> tokenize(const std::string& str, char delimiter)
{
	std::vector<std::string> result;
	std::stringstream ss(str);
	std::string token;
	while (getline(ss, token, delimiter))
		result.push_back(token);
	return result;
}

std::istream& operator>>(std::istream& is, Event& event)
{
	std::string eventString;
	getline(is, eventString);
	std::vector<std::string> result = tokenize(eventString, ',');
	if (result.size() != 5)
		return is;

	event.title = result[0];
	event.description = result[1];
	event.date = result[2];
	event.link = result[3];
	event.nrpeople = std::stoi(result[4]);
	return is;
}

std::ostream& operator<<(std::ostream& os, const Event& event)
{
	os << event.title << ',' << event.description << ',' << event.date << ',' << event.link << ',' << event.nrpeople;
	return os;
}