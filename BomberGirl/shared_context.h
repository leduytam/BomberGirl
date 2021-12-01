#pragma once

#include "resource_manager.h"
#include "state_manager.h"
#include <memory>
#include <SFML/Graphics.hpp>

namespace bombergirl
{
    class SharedContext
    {
    public:
        sf::RenderWindow* m_window;
        ResourceManager* m_resources;
        StateManager* m_stateManager;
    };
}
