#pragma once

#include "base_state.h"
#include "player.h"
#include <vector>
#include "Cell.h"

namespace Bombergirl
{
    class GameState : public BaseState
    {
    private:
        Player *m_player1, *m_player2;
        sf::RectangleShape m_background;
        sf::Texture m_backgroundTexture;
        sf::VertexArray m_backgroundVA;
        sf::IntRect m_arena;
        sf::View m_view;

        std::vector <std::vector<Cell*>> m_map;

        const int TILE_SIZE = 48;
        const int TILE_TYPES = 3;
        const int VERTEX_IN_QUAD = 4;
        const int WORLD_WIDTH = 720;
        const int WORLD_HEIGHT = 720;
        

    public:
        GameState(SharedContext* sharedContext, const sf::String& character_1, const sf::String& character_2);
        ~GameState();
        void init() override;
        void handleInput() override;
        void update(const float&) override;
        void render() override;
        void loadResources();
        void createBackground();
        void createMap();
    };
}

