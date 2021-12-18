#include "resource_manager.h"
#include <iostream>

void Bombergirl::ResourceManager::loadTexture(const std::string& textureID, const std::string& textureFilePath)
{
    if (m_textures.find(textureID) == m_textures.end())
    {
        sf::Texture texture;
        
        if (texture.loadFromFile(textureFilePath))
            m_textures[textureID] = texture;
        else
            std::cout << "Failed to load texture: " << textureFilePath << std::endl;
    }
}

void Bombergirl::ResourceManager::loadTexture(const std::string& textureID, const std::string& textureFilePath, const sf::IntRect& crop) {
    if (m_textures.find(textureID) == m_textures.end())
    {
        sf::Texture texture;

        if (texture.loadFromFile(textureFilePath, crop))
            m_textures[textureID] = texture;
        else
            std::cout << "Failed to load texture: " << textureFilePath << std::endl;
    }
}


sf::Texture& Bombergirl::ResourceManager::getTexture(const std::string& textureID)
{
    return m_textures.at(textureID);
}

void Bombergirl::ResourceManager::loadFont(const std::string& fontID, const std::string& fontFilePath)
{
    if (m_fonts.find(fontID) == m_fonts.end())
    {
        sf::Font font;

        if (font.loadFromFile(fontFilePath))
            m_fonts[fontID] = font;
        else
            std::cout << "Failed to load font: " << fontFilePath << std::endl;
    }
}

sf::Font& Bombergirl::ResourceManager::getFont(const std::string& fontID)
{
    return m_fonts.at(fontID);
}
//
//void  Bombergirl::ResourceManager::loadSoundBuffer(const std::string& soundID, const std::string& soundFilePath) {
//    if (m_sounds.find(soundID) == m_sounds.end()) {
//        sf::SoundBuffer soundbuffer;
//        if (soundbuffer.loadFromFile(soundFilePath)) {
//            m_sounds[soundID] = soundbuffer;
//        }
//        else {
//            std::cout << "Failed to load font: " << soundFilePath << std::endl;
//
//        }
//    }
//}
//
//
//sf::SoundBuffer& Bombergirl::ResourceManager::getSoundBuffer(const std::string& soundID)
//{
//    return m_sounds.at(soundID);
//}
//

