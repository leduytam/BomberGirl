#pragma once

#include "animation.h"
#include "cell.h"

namespace Bombergirl
{
    class Player
    {
    public:
        enum class PlayerDirection { Up, Down, Left, Right, None };
    private:
        SharedContext* m_sharedContext;
        float m_speed;
        int m_bombs;
        int m_bombRange;
        bool m_isDead;
        bool m_isOnSetUpBomb;
        float m_elapsedTime;
        sf::Sprite m_playerSprite;
        sf::Sprite m_shadowSprite;
        Animation m_walkingUpAnimation;
        Animation m_walkingDownAnimation;
        Animation m_walkingLeftAnimation;
        Animation m_walkingRightAnimation;
        Animation m_deadAnimation;
        PlayerDirection m_playerDirection;
        
        sf::Sound* m_increaseBombRangeSound;
        sf::Sound* m_increaseBombCountSound;
        sf::Sound* m_IncreaseSpeedSound;
        sf::Sound* m_hitSound;
        int m_countWinRounds;
        friend class BombCell;
    public:
        Player(SharedContext*, sf::Texture*, const PlayerDirection&);
        void update(const float&, std::vector<std::vector<Cell*>>&);
        void render(sf::RenderWindow&);
        void setDirection(const PlayerDirection&);
        void setPosition(const sf::Vector2f&);
        void setUpBomb();
        sf::Vector2f getCenter() const;
        sf::FloatRect getBound() const;
        bool isDead() const;
        ~Player();
    };
};
