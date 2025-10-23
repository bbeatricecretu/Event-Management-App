#include "EventsListHTML.h"
#include <fstream>
#include <cstdlib> // for system()
using namespace std;

EventsListHTML::EventsListHTML(string filePath) : filePath(filePath) {}

std::vector <Event> EventsListHTML::getElements() 
{
	return this->elements;
}

void EventsListHTML::add(const Event& e) 
{
    this->elements.push_back(e);
    this->writeToFile();
}

void EventsListHTML::writeToFile() {
    ofstream file(this->filePath);
    if (!file.is_open()) {
        throw runtime_error("Could not open file for writing.");
    }

    file << "<!DOCTYPE html>\n";
    file << "<html>\n";
    file << "<head>\n";
    file << "    <title>Events List</title>\n"; 
    file << "</head>\n";
    file << "<body>\n";
    file << "<table border=\"1\">\n";
    file << "    <tr>\n";
    file << "        <td>Title</td>\n";
    file << "        <td>Description</td>\n";
    file << "        <td>Date</td>\n";
    file << "        <td>Link</td>\n";
    file << "        <td>Number of People</td>\n";
    file << "    </tr>\n";

    for (const auto& event : this->elements) {
        file << "    <tr>\n";
        file << "        <td>" << event.getTitle() << "</td>\n";
        file << "        <td>" << event.getDescription() << "</td>\n";
        file << "        <td>" << event.getDate() << "</td>\n";
        file << "        <td><a href=\"" << event.getLink() << "\">Link</a></td>\n";
        file << "        <td>" << event.getNrpeople() << "</td>\n";
        file << "    </tr>\n";
    }

    file << "</table>\n";
    file << "</body>\n";
    file << "</html>\n";

    file.close();
}


void EventsListHTML::display() 
{
    #ifdef _WIN32
        std::string command = "start " + this->filePath;
    #elif __APPLE__
        std::string command = "open " + this->filePath;
    #elif __linux__
        std::string command = "xdg-open " + this->filePath;
    #else
        throw std::runtime_error("Unsupported OS for opening files!");
    #endif
        system(command.c_str());
}
