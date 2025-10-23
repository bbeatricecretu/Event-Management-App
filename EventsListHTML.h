#pragma once
#include "EventsList.h"
class EventsListHTML : public EventsList
{
private:
	std::vector<Event> elements;
	std::string filePath;

public:
	EventsListHTML(std::string filePath);
	void add(const Event& e) override;
	std::vector<Event> getElements() override;
	void display() override;

private:
	void writeToFile();

};

