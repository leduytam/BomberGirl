#pragma once

#include <string>
#include <unordered_map>
#include <SFML/Graphics.hpp>

namespace Bombergirl
{
    class ResourceManager
    {
    private:
        std::unordered_map<std::string, sf::Texture> m_textures;
        std::unordered_map<std::string, sf::Font> m_fonts;
    public:
        void loadTexture(const std::string&, const std::string&);
        void loadTexture(const std::string&, const std::string&, const sf::IntRect &);
        sf::Texture& getTexture(const std::string&);

        void loadFont(const std::string&, const std::string&);
        sf::Font& getFont(const std::string&);
    };
}
