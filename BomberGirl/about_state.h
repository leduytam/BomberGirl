#pragma once

#include "base_state.h"

namespace Bombergirl
{
    class AboutState : public BaseState
    {
    private:
        sf::Text m_aboutText;
        sf::Sprite m_control;
        sf::Sprite m_background;
        sf::View m_view;
        sf::Text m_controlText;
        sf::Text m_controlText2;
        sf::Text m_controlText3;
        sf::Text m_controlText4;
        sf::Text m_controlText5;
    public:
        AboutState(SharedContext* sharedContext);

        void init() override;
        void handleInput() override;
        void update(const float&) override;
        void render() override;
    };
}

