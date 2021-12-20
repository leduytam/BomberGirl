#pragma once

#include "base_state.h"

namespace Bombergirl
{
    class AboutState : public BaseState
    {
    private:
        sf::Sprite m_textImage;
        sf::RectangleShape m_whiteBackground;
        sf::RectangleShape m_whiteRectUp;
        sf::RectangleShape m_whiteRectDown;

    public:
        AboutState(SharedContext* sharedContext);

        void init() override;
        void handleInput() override;
        void update(const float&) override;
        void render() override;
    };
}

