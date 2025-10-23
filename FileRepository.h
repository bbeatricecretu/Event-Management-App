#pragma once
#include "Repo.h"

class FileRepository : public Repository {
private:
    std::vector<Event> elements;
    std::string filePath;
public:
    FileRepository(std::string filePath);
public:
    void add_event_repo(const Event& e) override;
    void update_event_repo(const Event& e, int pos) override;
    void delete_event_repo(const Event& e, int pos) override;
    const std::vector<Event>& get_all() const override;
    int get_number_of_events() const override;
    Event* get_event_by_index(int pos) override;
    int find_event_position(const Event& event) override;
    std::vector<Event> get_events_by_people_count(int people_count) const override;
private:
    void writeToFile();
    void readFromFile();
};