// Validator.cpp
#include "Validator.h"

bool EventValidator::isValidDate(const std::string& date) const {
    // Regex for date format yyyy-mm-dd
    std::regex date_pattern(R"(^\d{4}-\d{2}-\d{2}$)");
    if (!std::regex_match(date, date_pattern)) {
        return false;
    }

    // Additional date validation (extracting year, month, day)
    std::smatch matches;
    std::regex date_components(R"(^(\d{4})-(\d{2})-(\d{2})$)");
    if (std::regex_match(date, matches, date_components)) {
        int year = std::stoi(matches[1].str());
        int month = std::stoi(matches[2].str());
        int day = std::stoi(matches[3].str());

        // Basic validation
        if (month < 1 || month > 12) return false;
        if (day < 1 || day > 31) return false;
        if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) return false;
        if (month == 2) {
            bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
            if (day > (isLeapYear ? 29 : 28)) return false;
        }
    }

    return true;
}

bool EventValidator::isValidLink(const std::string& link) const {
    // URL validation - simple version checking for basic URL pattern
    std::regex url_pattern(R"(^(http|https)://[a-zA-Z0-9-\.]+\.[a-zA-Z]{2,}(/[\w\-\.~:/?#\[\]@!$&'\(\)\*\+,;=]*)?$)");
    return std::regex_match(link, url_pattern);
}

bool EventValidator::isValidPeopleCount(int count) const {
    return count >= 0;
}

void EventValidator::validate(const Event& event) const {
    std::vector<std::string> errors;

    // Validate title
    if (event.getTitle().empty()) {
        errors.push_back("Title cannot be empty");
    }

    // Validate description
    if (event.getDescription().empty()) {
        errors.push_back("Description cannot be empty");
    }

    // Validate date
    if (!isValidDate(event.getDate())) {
        errors.push_back("Invalid date format or value. Use YYYY-MM-DD format");
    }

    // Validate link
    if (event.getLink().empty()) {
        errors.push_back("Invalid URL format");
    }

    // Validate number of people
    if (!isValidPeopleCount(event.getNrpeople())) {
        errors.push_back("Number of people must be non-negative");
    }

    // If there are validation errors, throw an exception
    if (!errors.empty()) {
        std::string errorMessage;
        for (size_t i = 0; i < errors.size(); i++) {
            errorMessage += "-> " + errors[i];
            if (i < errors.size() - 1) {
                errorMessage += "\n";
            }
        }
        throw ValidationException(errorMessage);
    }
}