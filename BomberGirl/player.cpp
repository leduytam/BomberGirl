#include "player.h"
#include<iostream>

Bombergirl::Player::Player(sf::Texture* playerTexture, sf::Texture* shadowTexture, bool directDown) : m_speed(200.f), m_isDying(false)
{
    m_direction = directDown ? Direction::Down : Direction::Up;
    m_playerSprite.setTexture(*playerTexture);
    m_shadowSprite.setTexture(*shadowTexture);
    m_shadowSprite.setPosition({ 0.f, 8.f });
    
    m_walkingDown.setSprite(&m_playerSprite);
    m_walkingDown.addFrame({ 0, 0, 48, 48 });
    m_walkingDown.addFrame({ 48, 0, 48, 48 });
    m_walkingDown.addFrame({ 96, 0, 48, 48 });
    m_walkingDown.update(0.f);

    m_walkingLeft.setSprite(&m_playerSprite);
    m_walkingLeft.addFrame({ 0, 48, 48, 48 });
    m_walkingLeft.addFrame({ 48, 48, 48, 48 });
    m_walkingLeft.addFrame({ 96, 48, 48, 48 });

    m_walkingRight.setSprite(&m_playerSprite);
    m_walkingRight.addFrame({ 0, 96, 48, 48 });
    m_walkingRight.addFrame({ 48, 96, 48, 48 });
    m_walkingRight.addFrame({ 96, 96, 48, 48 });

    m_walkingUp.setSprite(&m_playerSprite);
    m_walkingUp.addFrame({ 0, 144, 48, 48 });
    m_walkingUp.addFrame({ 48, 144, 48, 48 });
    m_walkingUp.addFrame({ 96, 144, 48, 48 });

    m_dying.setSprite(&m_playerSprite);
    m_dying.addFrame({ 0, 192, 48, 48 });
    m_dying.addFrame({ 48, 192, 48, 48 });
    m_dying.addFrame({ 96, 192, 48, 48 });
    

    
}

void Bombergirl::Player::update(const float& dt)
{
    if (m_isDying)
    {
        m_dying.update(dt);
    }
    else
    {
        switch (m_direction)
        {
        case Player::Direction::Up:
            m_playerSprite.move(0.f, -dt * m_speed);
            m_walkingUp.update(dt);
            if (m_playerSprite.getPosition().y < m_arena.top) {
                m_playerSprite.move(0.f, dt * m_speed);
            }
            break;
        case Player::Direction::Down:
            m_playerSprite.move(0.f, dt * m_speed);
            m_walkingDown.update(dt);
            if (m_playerSprite.getPosition().y > (m_arena.height)) {
                m_playerSprite.move(0.f, -dt * m_speed);
            }
            break;
        case Player::Direction::Left:
            m_playerSprite.move(-dt * m_speed, 0.f);
            m_walkingLeft.update(dt);
            if (m_playerSprite.getPosition().x < m_arena.left) {
                m_playerSprite.move(dt * m_speed, 0.f);
            }
            break;
        case Player::Direction::Right:
            m_playerSprite.move(dt * m_speed, 0.f);
            m_walkingRight.update(dt);
            if (m_playerSprite.getPosition().x > (m_arena.width)) {
                m_playerSprite.move(-dt * m_speed, 0.f);
            }
            break;
        }
    }

    m_direction = Direction::None;
}

void Bombergirl::Player::render(sf::RenderWindow& window)
{
    window.draw(m_shadowSprite, m_playerSprite.getTransform());
    window.draw(m_playerSprite);
}

void Bombergirl::Player::moveUp()
{
    m_direction = Direction::Up;
}

void Bombergirl::Player::moveDown()
{
    m_direction = Direction::Down;
}

void Bombergirl::Player::moveLeft()
{
    m_direction = Direction::Left;
}

void Bombergirl::Player::moveRight()
{
    m_direction = Direction::Right;
}

void Bombergirl::Player::die()
{
    m_isDying = true;
}



void Bombergirl::Player::setPosition(const sf::Vector2f& position)
{
   m_playerSprite.setPosition({ position.x - 24.f, position.y - 24.f });
}

void Bombergirl::Player::setArena(const sf::IntRect& arena) {
    m_arena.left = arena.left + m_playerSprite.getLocalBounds().width;
    m_arena.top = arena.top + m_playerSprite.getLocalBounds().height;
    m_arena.width = arena.width - 2*m_playerSprite.getLocalBounds().width;
    m_arena.height = arena.height - 2*m_playerSprite.getLocalBounds().height;

}
