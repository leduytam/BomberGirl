#pragma once

#include "base_state.h"

namespace Bombergirl
{
    class PausedState : public BaseState
    {
    private:
        sf::RectangleShape m_overlay;
        sf::Text m_pausedText;
    public:
        PausedState(SharedContext* sharedContext);

        void init() override;
        void handleInput() override;
        void update(const float&) override;
        void render() override;
    };
}

