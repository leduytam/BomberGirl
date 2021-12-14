#pragma once

#include "base_state.h"
#include "player.h"

namespace Bombergirl
{
    class GameState : public BaseState
    {
    private:
        Player *m_player1, *m_player2;
        sf::RectangleShape m_background;
        sf::Texture m_backgroundTexture;
        sf::VertexArray m_backgroundVA;
    public:
        GameState(SharedContext* sharedContext, const sf::String& character_1, const sf::String& character_2);
        ~GameState();
        void init() override;
        void handleInput() override;
        void update(const float&) override;
        void render() override;
        void loadResources();
        void createBackground();
    };
}

