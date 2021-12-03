#include"Button.h"
#include"shared_context.h"
#include"configs.h"

Bombergirl::Button::Button(SharedContext* sharedContext) {
	m_sharedContext = sharedContext;
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
}

void Bombergirl::Button::setOutline(float thickness = 0.f, sf::Color color = sf::Color::White) {
	m_shape.setOutlineColor(color);
	m_shape.setOutlineThickness(thickness);
}

void Bombergirl::Button::drawButton() {
	m_sharedContext->m_window->draw(m_shape);
	m_sharedContext->m_window->draw(m_content);
}

void Bombergirl::Button::setPosition(const sf::Vector2f& position) {
	m_shape.setPosition(position);
	m_content.setPosition(position);
}