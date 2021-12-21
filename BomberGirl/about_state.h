 #pragma once

#include "base_state.h"

namespace Bombergirl
{
    class AboutState : public BaseState
    {
    private:
        sf::Text m_textEnd;
        sf::Text m_textBackToMenu;
        sf::Sprite m_textImage;
        sf::RectangleShape m_whiteBackground;
        sf::RectangleShape m_whiteRectUp;
        sf::RectangleShape m_whiteRectDown;
        bool m_isTextEnd;
        float alpha = 0;
        float speed = 200;

    public:
        AboutState(SharedContext* sharedContext);

        void init() override;
        void handleInput() override;
        void update(const float&) override;
        void render() override;
    };
}

