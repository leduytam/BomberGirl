#include "animation.h"

Bombergirl::Animation::Animation() : m_time(0.f), m_frameDuration(0.15f) { }

void Bombergirl::Animation::setSprite(sf::Sprite* sprite)
{
    m_playerSprite = sprite;
}

void Bombergirl::Animation::setFrameDuration(const float& frameDuration)
{
    m_frameDuration = frameDuration;
}

void Bombergirl::Animation::addFrame(const sf::IntRect& frame)
{
    m_frames.push_back(frame);
}

void Bombergirl::Animation::update(const float& dt)
{
    m_time += dt;

    if (m_time >= m_frameDuration * m_frames.size())
        m_time -= m_frameDuration * m_frames.size();

    float m_tmp = m_time;

    for (size_t i = 0; i < m_frames.size(); i++)
    {
        m_tmp -= m_frameDuration;

        if (m_tmp < 0.f)
        {
            m_playerSprite->setTextureRect(m_frames[i]);
            break;
        }
    }
}

