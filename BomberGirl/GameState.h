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
        sf::IntRect m_arena;
        sf::View m_view;
        sf::Sprite m_mapBackgroundSprite;

        std::vector <std::vector<Cell*>> m_map;
    public:
        GameState(SharedContext* sharedContext, const sf::String& character_1, const sf::String& character_2);
        ~GameState();
        void init() override;
        void handleInput() override;
        void update(const float&) override;
        void render() override;
        void createMap();
    };
}
