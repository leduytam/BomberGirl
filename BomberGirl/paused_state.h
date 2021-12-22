#pragma once

#include "base_state.h"
#include "main_menu_state.h"

namespace Bombergirl
{
    class PausedState : public BaseState
    {
    private:
        sf::RectangleShape m_overlay;
        sf::Sprite m_title;
        sf::Sprite m_arrow;
        std::vector<MainMenuState::Option> m_optionList;
        int m_option;
        sf::Sound* m_soundBack;
        sf::Sound* m_soundClick;
        sf::Sound* m_soundConfirm;
        const int NUMBER_OPTION = 3;
    public:
        PausedState(SharedContext* sharedContext, sf::Sound* soundBack);
        ~PausedState();

        void init() override;
        void handleInput() override;
        void update(const float&) override;
        void render() override;
    };
}

