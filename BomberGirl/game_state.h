#pragma once

#include "base_state.h"
#include "player.h"
#include <vector>
#include "cell.h"

namespace Bombergirl
{
    class GameState : public BaseState
    {
    private:
        Player *m_player1, *m_player2;
        sf::IntRect m_arena;
        sf::View m_mapView;
        sf::View m_mainView;
        sf::Sprite m_mapBackgroundSprite;
        sf::Sprite m_backgroundSprite;

        std::vector <std::vector<Cell*>> m_map;

        sf::Sound *m_backSound;
    public:
        GameState(SharedContext* sharedContext);
        ~GameState();
        void init() override;
        void handleInput() override;
        void update(const float&) override;
        void render() override;
        void createMap();
    };
}
