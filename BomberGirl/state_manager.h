#pragma once

#include <vector>
#include <queue>

namespace bombergirl
{
    class BaseState;

    class StateManager
    {
    private:
        enum class StateAction { Adding, Removing, Replacing };

        std::vector<BaseState*> m_states;
        std::queue<StateAction> m_actionQueue;
        std::queue<BaseState*> m_addingQueue;
    public:
        StateManager();
        ~StateManager();

        void push(BaseState*, const bool& isReplacing = false);
        void pop();

        void handleInput();
        void update(const float&);
        void render();
        void handleStateChanges();
    };
}

