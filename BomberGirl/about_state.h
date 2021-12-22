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
        sf::Sprite m_groupSprite;
        sf::Sprite m_lightSprite;
        sf::Sprite m_leftGearSprite;
        sf::Sprite m_rightGearSprite;
        bool m_isTextEnd;
        float m_pressEnterTextEffectAlpha;
        float m_pressEnterTextEffectSpeed;
        float m_animationImageAlpha;
        bool isThanksDisplayed;
    public:
        AboutState(SharedContext* sharedContext);

        void init() override;
        void handleInput() override;
        void update(const float&) override;
        void render() override;
    };
}

