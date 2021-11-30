#pragma once

#include "base_state.h"
#include <SFML/Graphics.hpp>

namespace bombergirl
{
    class IntroState : public BaseState
    {
    private:
        sf::Text m_introText;
        float m_totalTime;
    public:
        IntroState(SharedContext* sharedContext);

        void init() override;
        void handleInput() override;
        void update(const float&) override;
        void render() override;
    };
}

