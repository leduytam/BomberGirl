#include"Button.h"
#include"shared_context.h"
#include"configs.h"
#include<iostream>

Bombergirl::Button::Button(SharedContext* sharedContext) {
	m_sharedContext = sharedContext;
	m_shape.setSize(sf::Vector2f(200, 100));
}

void Bombergirl::Button::setSize(const sf::Vector2f& size) {
	m_shape.setSize(size);
}

void Bombergirl::Button::setText(const std::string& text, sf::Color color, const int& sizeCharacter) {
	m_sharedContext->m_resources->loadFont("garamond", GARAMOND_FONT_PATH);
	m_content.setFont(m_sharedContext->m_resources->getFont("garamond"));
	m_content.setCharacterSize(sizeCharacter);
	m_content.setFillColor(color);
	m_content.setString(text);
	m_shape.setSize(sf::Vector2f(text.length() * sizeCharacter + 20, sizeCharacter + 20));
}

void Bombergirl::Button::setOutline(float thickness = 0.f, sf::Color color) {
	m_shape.setOutlineColor(color);
	m_shape.setOutlineThickness(thickness);
}


void Bombergirl::Button::drawButton() {
	m_sharedContext->m_window->draw(m_shape);
	m_sharedContext->m_window->draw(m_content);
}

void Bombergirl::Button::setPosition(const sf::Vector2f& position) {
	m_shape.setPosition(position);
	m_content.setPosition(position.x + (m_shape.getSize().x - m_content.getLocalBounds().width)/2, position.y + (m_shape.getSize().y - m_content.getLocalBounds().height * 2) / 2);
}

void Bombergirl::Button::setBackgroundColor(const sf::Color color) {
	m_shape.setFillColor(color);
}

