#pragma once

#include "base_state.h"
#include"Button.h"

namespace Bombergirl
{
    class MainMenuState : public BaseState
    {
    private:
        sf::Text m_mainMenuText;
        sf::Sprite m_backgroundSprite;
        sf::Sprite m_containerBoard;
        
    public:
        const int TILE_SIZE = 12;
        const int TILE_TYPES = 3;
        const int VERTEX_IN_QUAD = 4;
        enum class STATE_OPTION {
            NEWGAME,
            ABOUT,
            LOAD,
            SAVE,
        };

        STATE_OPTION mainOption;
        MainMenuState(SharedContext* sharedContext);
        

        void init() override;
        void handleInput() override;
        void update(const float&) override;
        void render() override;

        Button createOptionText(const std::string&);
        sf::RectangleShape createContainer();
    };
}

