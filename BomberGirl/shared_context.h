#pragma once

#include "resource_manager.h"
#include "state_manager.h"
#include <SFML/Graphics.hpp>

namespace Bombergirl
{
    class SharedContext
    {
    public:
        sf::RenderWindow* m_window;
        ResourceManager* m_resources;
        StateManager* m_stateManager;

        SharedContext() : m_window(nullptr), m_resources(nullptr), m_stateManager(nullptr) {}

        ~SharedContext() {
            delete m_window;
            delete m_stateManager;
            delete m_resources;
        }
    };
}
