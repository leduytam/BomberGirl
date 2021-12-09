#pragma once

#include "base_state.h"

namespace Bombergirl
{
    class AboutState : public BaseState
    {
    private:
        sf::Sprite m_background;
        sf::View m_view;
    public:
        AboutState(SharedContext* sharedContext);

        void init() override;
        void handleInput() override;
        void update(const float&) override;
        void render() override;
    };
}

