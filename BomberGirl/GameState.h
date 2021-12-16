#pragma once

#include "base_state.h"
#include "player.h"
#include<vector>

namespace Bombergirl
{
    class Cell {
    private:
        sf::Vector2f m_position;
        sf::FloatRect m_rect;
        int m_type;
        const int cell_size = 48;
    public:
        Cell(int type = 0, sf::Vector2f position = sf::Vector2f(0, 0)) {
            m_type = type;
            m_position = position;
            m_rect = sf::FloatRect(position.x, position.y, cell_size, cell_size);
        }
        int getType() {
            return m_type;
        }
        
        sf::FloatRect getBound() {
            return m_rect;
        }
       
    };

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

