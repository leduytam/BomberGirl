#pragma once

#include "base_state.h"

namespace Bombergirl
{
    class MainMenuState : public BaseState
    {
    private:
        sf::Text m_mainMenuText;
        sf::Sprite m_backgroundSprite;
    public:
        MainMenuState(SharedContext* sharedContext);

        void init() override;
        void handleInput() override;
        void update(const float&) override;
        void render() override;
    };
}

