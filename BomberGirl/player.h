#pragma once

#include "animation.h"

namespace Bombergirl
{
    class Player
    {
    private:
        enum class Direction { Up, Down, Left, Right, None };

        sf::Sprite m_playerSprite;
        sf::Sprite m_shadowSprite;
        Animation m_walkingUp;
        Animation m_walkingDown;
        Animation m_walkingLeft;
        Animation m_walkingRight;
        Animation m_dying;
        Direction m_direction;
        float m_speed;
        bool m_isDying;
    public:
        Player(sf::Texture*, sf::Texture*);

        void update(const float&);
        void render(sf::RenderWindow&);

        void moveUp();
        void moveDown();
        void moveLeft();
        void moveRight();
        void die();

        void setPosition(const sf::Vector2f&);
    };

};

