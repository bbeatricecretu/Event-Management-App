#pragma once
#include "EventsList.h"
#include <vector>
#include <string>

class EventsCSV : public EventsList {
private:
	std::vector<Event> elements;
	std::string filePath;
public:
	EventsCSV(std::string filePath);
	void add(const Event& s) override;
	std::vector<Event> getElements() override;
	void display() override;
private:
	void writeToFile();
};