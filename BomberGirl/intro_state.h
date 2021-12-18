#pragma once

#include "base_state.h"
#include <SFML/Graphics.hpp>

namespace Bombergirl
{
    class IntroState : public BaseState
    {
    private:
        sf::Sprite m_logo;
        float m_totalTime;
        sf::Sound m_sound;
    public:
        IntroState(SharedContext* sharedContext);

        void init() override;
        void handleInput() override;
        void update(const float&) override;
        void render() override;
    };
}

