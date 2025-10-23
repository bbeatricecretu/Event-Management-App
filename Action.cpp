#include "Action.h"
#include "Repo.h"
#include "Exception.h"

// ------- AddAction -------
AddAction::AddAction(Repository& r, const Event& e)
    : repo(r), event(e) {
}

void AddAction::executeUndo() {
    int pos = repo.find_event_position(event);
    repo.delete_event_repo(event, pos);
}

void AddAction::executeRedo() {
    repo.add_event_repo(event);
}

// ------- DeleteAction -------
DeleteAction::DeleteAction(Repository& r, const Event& e)
    : repo(r), event(e) {
}

void DeleteAction::executeUndo() {
    repo.add_event_repo(event);
}

void DeleteAction::executeRedo() {
    int pos = repo.find_event_position(event);
    repo.delete_event_repo(event, pos);
}

// ------- UpdateAction -------
UpdateAction::UpdateAction(Repository& r, const Event& oldE, const Event& newE)
    : repo(r), oldEvent(oldE), newEvent(newE) {
}

void UpdateAction::executeUndo() {
    int pos = repo.find_event_position(newEvent);
    repo.update_event_repo(oldEvent, pos); // revert
}

void UpdateAction::executeRedo() {
    int pos = repo.find_event_position(oldEvent);
    repo.update_event_repo(newEvent, pos); // apply again
}
