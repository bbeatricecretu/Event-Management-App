// FileRepository.cpp (updated version)
#include "FileRepository.h"
#include "Exception.h"
#include <fstream>
using namespace std;

FileRepository::FileRepository(string filePath) : filePath(filePath)
{
    try {
        readFromFile();
    }
    catch (const RepositoryException& e) {
        // If file doesn't exist, create it
        ofstream fout(this->filePath);
        if (!fout.is_open()) {
            throw RepositoryException("Failed to create repository file: " + filePath );
        }
        fout.close();
    }
}

void FileRepository::add_event_repo(const Event& e)
{
    // Check if event already exists
    if (find_event_position(e) != -1) {
        throw RepositoryException("Event with same title and date already exists");
    }

    this->elements.push_back(e);
    this->writeToFile();
}

void FileRepository::update_event_repo(const Event& e, int pos)
{
    if (pos < 0 || pos >= this->elements.size()) {
        throw RepositoryException("Invalid event for update");
    }

    this->elements[pos] = e;
    this->writeToFile();
}

void FileRepository::delete_event_repo(const Event& e, int pos)
{
    if (pos < 0 || pos >= this->elements.size()) {
        throw RepositoryException("Invalid event for delete");
    }

    this->elements.erase(this->elements.begin() + pos);
    this->writeToFile();
}

const std::vector<Event>& FileRepository::get_all() const
{
    return this->elements;
}

int FileRepository::get_number_of_events() const
{
    return static_cast<int>(this->elements.size());
}

Event* FileRepository::get_event_by_index(int pos)
{
    if (pos < 0 || pos >= this->elements.size()) {
        throw RepositoryException("Invalid event");
    }
    return &this->elements[pos];
}

int FileRepository::find_event_position(const Event& event)
{
    auto it = std::find_if(this->elements.begin(), this->elements.end(),
        [&event](const Event& e) { return e == event; });

    if (it != this->elements.end()) {
        return static_cast<int>(std::distance(this->elements.begin(), it));
    }
    return -1;
}

std::vector<Event> FileRepository::get_events_by_people_count(int people_count) const
{
    if (people_count < 0) {
        throw RepositoryException("People count cannot be negative");
    }

    std::vector<Event> filtered_events;

    for (const auto& event : this->elements) {
        if (event.getNrpeople() == people_count) {
            filtered_events.push_back(event);
        }
    }

    return filtered_events;
}

void FileRepository::readFromFile()
{
    ifstream fin(this->filePath);
    if (!fin.is_open()) {
        throw RepositoryException("Failed to open file for reading: " + this->filePath );
    }

    Event s;
    this->elements.clear();
    while (fin >> s) {
        this->elements.push_back(s);
    }
    fin.close();
}

void FileRepository::writeToFile()
{
    ofstream fout(this->filePath);
    if (!fout.is_open()) {
        throw RepositoryException("Failed to open file for writing: " + this->filePath);
    }

    for (const auto& event : this->elements) {
        fout << event << '\n';
    }
    fout.close();
}