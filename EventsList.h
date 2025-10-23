#pragma once
#include "Event.h"
#include <vector>

class EventsList {
public:
	virtual void add(const Event& e) = 0;
	virtual std::vector<Event> getElements() = 0;
	virtual ~EventsList() {}
	virtual void display() = 0;
};