#pragma once

#include "resource_manager.h"
#include "state_manager.h"
#include "soundManager.h"
#include <memory>
#include <SFML/Graphics.hpp>

namespace Bombergirl
{
    class SharedContext
    {
    public:
        sf::RenderWindow* m_window;
        ResourceManager* m_resources;
        StateManager* m_stateManager;
        SoundManager* m_soundManager;

    };
}