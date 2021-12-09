#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

namespace Bombergirl
{
    class Animation
    {
    private:
        std::vector<sf::IntRect> m_frames;
        sf::Sprite* m_playerSprite;
        float m_time;
        float m_frameDuration;
    public:
        Animation();
        void setSprite(sf::Sprite*);
        void setFrameDuration(const float&);
        void addFrame(const sf::IntRect&);
        void update(const float&);
    };
}

