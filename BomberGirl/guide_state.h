#pragma once

#include "base_state.h"

namespace Bombergirl
{
    class GuideState : public BaseState
    {
    private:
        sf::Sprite m_backgroundGuide;
        sf::Sprite m_imageGuide;
        sf::Text m_textMoveCharacter;
        sf::Text m_textBomb;
        sf::Text m_textMovePickUp;
        sf::Text m_textPickUp;
        sf::Text m_textControls;
        sf::Text m_textPotionsIncreaseSpeed;
        sf::Text m_textPotionsIncreaseRange;
        sf::Text m_textPotionsIncreaseTheNumberOfBombs;

    public:
        GuideState(SharedContext* sharedContext);

        void init() override;
        void handleInput() override;
        void update(const float&) override;
        void render() override;
    };
}

