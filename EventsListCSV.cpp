#include "EventsListCSV.h"
#include <fstream>
#include <cstdlib>
using namespace std;

EventsCSV::EventsCSV(string filePath) : filePath(filePath) {}

void EventsCSV::add(const Event& e) {
	this->elements.push_back(e);
	this->writeToFile();
}

std::vector<Event> EventsCSV::getElements() {
	return this->elements;
}

void EventsCSV::writeToFile() 
{
	ofstream fout(this->filePath);
	if (fout.is_open() == false)
		throw exception("File not open!");

	for (int i = 0; i < this->elements.size(); i++)
	{
		fout << this->elements[i] << "\n";
	}
	fout.close();
}


void EventsCSV::display() {
#ifdef _WIN32
	std::string command = "notepad.exe " + this->filePath;
#elif __APPLE__
	std::string command = "open -a TextEdit " + this->filePath;
#elif __linux__
	std::string command = "xdg-open " + this->filePath; 
#else
	throw std::runtime_error("Unsupported OS for opening CSV files!");
#endif
	system(command.c_str());
}
