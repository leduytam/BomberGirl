#pragma once

#include "base_state.h"

namespace Bombergirl
{
    class FadeInTransitionState : public BaseState
    {
    private:
        sf::RectangleShape m_overlay;
        float m_existTime;
        float m_totalTime;
    public:
        FadeInTransitionState(SharedContext*);

        void init() override;
        void handleInput() override;
        void update(const float&) override;
        void render() override;
    };
}
