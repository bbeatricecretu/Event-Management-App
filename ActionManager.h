#pragma once
#include <stack>
#include <memory>
#include "Action.h"

class ActionManager {
private:
    std::stack<std::unique_ptr<Action>> undoStack;
    std::stack<std::unique_ptr<Action>> redoStack;

public:
    void executeAction(std::unique_ptr<Action> action);
    void undo();
    void redo();
};
