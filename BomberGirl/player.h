#pragma once

#include "animation.h"
#include "Cell.h"
#include <vector>

namespace Bombergirl
{
    class Player
    {
    private:
        enum class Direction { Up, Down, Left, Right, None };

        sf::Sprite m_playerSprite;
        sf::Sprite m_shadowSprite;
        Animation m_walkingUpAnimation;
        Animation m_walkingDownAnimation;
        Animation m_walkingLeftAnimation;
        Animation m_walkingRightAnimation;
        Animation m_deadAnimation;
        Direction m_direction;
        float m_speed;
        bool m_isDead;
        sf::IntRect m_arena;

    public:
        Player(sf::Texture*, sf::Texture*, bool isFaceUp = true);

        void update(const float&, const std::vector<std::vector<Cell*>>&);
        void render(sf::RenderWindow&);

        void moveUp();
        void moveDown();
        void moveLeft();
        void moveRight();
        void setIsDead();
        void setArena(const sf::IntRect& arena = { 0, 0, 1920, 1080});
        void setPosition(const sf::Vector2f&);
        void setSpeed(const float&);

        sf::Vector2f getCenter();
        sf::FloatRect getBound();
    };
};

