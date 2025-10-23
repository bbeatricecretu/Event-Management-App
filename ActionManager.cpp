#include "ActionManager.h"

void ActionManager::executeAction(std::unique_ptr<Action> action) {
    action->executeRedo();
    undoStack.push(std::move(action));
    while (!redoStack.empty()) redoStack.pop();
}

void ActionManager::undo() {
    if (undoStack.empty()) throw std::runtime_error("Nothing more to undo.");
    auto action = std::move(undoStack.top());
    undoStack.pop();
    action->executeUndo();
    redoStack.push(std::move(action));
}

void ActionManager::redo() {
    if (redoStack.empty()) throw std::runtime_error("Nothing more to redo.");
    auto action = std::move(redoStack.top());
    redoStack.pop();
    action->executeRedo();
    undoStack.push(std::move(action));
}
