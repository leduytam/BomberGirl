#include "resource_manager.h"
#include <iostream>

void Bombergirl::ResourceManager::loadTexture(const std::string& textureID, const std::string& textureFilePath)
{
	if (m_textures.find(textureID) == m_textures.end())
	{
		sf::Texture texture;

		if (texture.loadFromFile(textureFilePath))
		{
			std::cout << "Loaded texture " << textureID << " from " << textureFilePath << std::endl;
			m_textures[textureID] = texture;
		}
		else
			std::cout << "Failed to load texture: " << textureFilePath << std::endl;
	}

}

void Bombergirl::ResourceManager::unloadTexture(const std::string& textureID)
{
	if (m_textures.find(textureID) != m_textures.end()) {
		m_textures.erase(textureID);
		std::cout << "Unloaded texture " << textureID << std::endl;
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

		if (font.loadFromFile(fontFilePath)) {
			std::cout << "Loaded font " << fontID << " from " << fontFilePath << std::endl;
			m_fonts[fontID] = font;
		}
		else {
			std::cout << "Failed to load font: " << fontFilePath << std::endl;
		}
	}
}

sf::Font& Bombergirl::ResourceManager::getFont(const std::string& fontID)
{
	return m_fonts.at(fontID);
}


void Bombergirl::ResourceManager::loadBuffer(const std::string& soundID, const std::string& soundPath) {
	if (m_sounds.find(soundID) == m_sounds.end())
	{
		sf::SoundBuffer sound;

		if (sound.loadFromFile(soundPath)) {
			std::cout << "Loaded sound " << soundID << " from " << soundPath << std::endl;
			m_sounds[soundID] = sound;
		}
		else {
			std::cout << "Failed to load sound: " << soundPath << std::endl;
		}
	}
}

sf::SoundBuffer& Bombergirl::ResourceManager::getBuffer(const std::string& soundID) {
	return m_sounds.at(soundID);
}
