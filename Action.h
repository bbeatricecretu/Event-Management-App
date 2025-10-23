#pragma once
#include "Repo.h"
#include "Event.h"

class Action {
public:
    virtual void executeUndo() = 0;
    virtual void executeRedo() = 0;
    virtual ~Action() = default;
};

class AddAction : public Action {
private:
    Repository& repo;
    Event event;
public:
    AddAction(Repository& r, const Event& e);
    void executeUndo() override;
    void executeRedo() override;
};

class DeleteAction : public Action {
private:
    Repository& repo;
    Event event;
public:
    DeleteAction(Repository& r, const Event& e);
    void executeUndo() override;
    void executeRedo() override;
};

class UpdateAction : public Action {
private:
    Repository& repo;
    Event oldEvent;
    Event newEvent;
public:
    UpdateAction(Repository& r, const Event& oldE, const Event& newE);
    void executeUndo() override;
    void executeRedo() override;
};
