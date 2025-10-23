// Validator.h
#pragma once
#include "Event.h"
#include "Exception.h"
#include <regex>
#include <vector>
#include <string>

class EventValidator {
private:
    // Helper methods for validation
    bool isValidDate(const std::string& date) const;
    bool isValidLink(const std::string& link) const;
    bool isValidPeopleCount(int count) const;

public:
    // Main validation method
    void validate(const Event& event) const;
};