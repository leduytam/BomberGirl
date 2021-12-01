#pragma once

#include "shared_context.h"

namespace bombergirl
{
    class Game
    {
    private:
        SharedContext m_sharedContext;
        sf::RenderWindow m_window;
        ResourceManager m_resources;
        StateManager m_stateManager;

        sf::Clock m_clock;

        void handleInput();
        void update(const float&);
        void render();
    public:
        Game();
        void run();
    };
}


