#include "state_manager.h"
#include "base_state.h"

bombergirl::StateManager::StateManager() {}

bombergirl::StateManager::~StateManager()
{
    for (auto& iter : m_states)
        delete iter;

    while (!m_addingQueue.empty())
    {
        delete m_addingQueue.front();
        m_addingQueue.pop();
    }
}

void bombergirl::StateManager::push(BaseState* state, const bool& isReplacing)
{
    m_actionQueue.push(isReplacing ? StateAction::Replacing : StateAction::Adding);
    m_addingQueue.push(state);
}

void bombergirl::StateManager::pop()
{
    m_actionQueue.push(StateAction::Removing);
}

void bombergirl::StateManager::handleInput()
{
    if (!m_states.empty()) m_states.back()->handleInput();
}

void bombergirl::StateManager::update(const float& dt)
{
    if (!m_states.empty()) m_states.back()->update(dt);
}

void bombergirl::StateManager::render()
{
    if (m_states.empty()) return;
    auto iter = m_states.end() - 1;
    while (iter != m_states.begin() && (*iter)->isTransparent()) --iter;
    for (; iter != m_states.end(); ++iter) (*iter)->render();
}

void bombergirl::StateManager::handleStateChanges()
{
    while (!m_actionQueue.empty())
    {
        StateAction action = m_actionQueue.front();
        m_actionQueue.pop();

        if (action == StateAction::Replacing)
        {
            if (!m_states.empty())
            {
                delete m_states.back();
                m_states.pop_back();
            }

            m_states.push_back(m_addingQueue.front());
            m_addingQueue.pop();
            m_states.back()->init();
        }
        else if (action == StateAction::Adding)
        {
            m_states.push_back(m_addingQueue.front());
            m_addingQueue.pop();
            m_states.back()->init();
        }
        else
        {
            if (!m_states.empty())
            {
                delete m_states.back();
                m_states.pop_back();
            }
        }
    }
}

