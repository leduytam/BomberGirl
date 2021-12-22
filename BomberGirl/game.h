#pragma once

#include "shared_context.h"

namespace Bombergirl
{
    class Game
    {
    private:
        SharedContext* m_sharedContext;
        sf::Clock m_clock;

        void loadResources();
        void handleInput();
        void update(const float&);
        void render();
    public:
        Game();
        ~Game();
        void run();
    };
}
