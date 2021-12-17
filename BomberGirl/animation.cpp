#include "animation.h"

Bombergirl::Animation::Animation() : m_time(0.f), m_frameDuration(0.15f), m_isRepeat(true) { }

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

    if (!m_isRepeat && m_time >= m_frameDuration * m_frames.size()) {
        return;
    }

    m_playerSprite->setTextureRect(m_frames[static_cast<int>(m_time / m_frameDuration) % m_frames.size()]);
}

void Bombergirl::Animation::setRepeat(const bool& isRepeat)
{
    m_isRepeat = isRepeat;
}

