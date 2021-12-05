#include"Button.h"
#include"shared_context.h"
#include"configs.h"
#include<iostream>

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
    m_shape.setSize(sf::Vector2f(text.length() * sizeCharacter, sizeCharacter));
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
    m_content.setPosition(position.x + (m_shape.getSize().x - m_content.getLocalBounds().width) / 2, position.y + (m_shape.getSize().y - m_content.getCharacterSize() * 1.5f) / 2);
}

void Bombergirl::Button::setBackgroundColor(const sf::Color color) {
    m_shape.setFillColor(color);
}

void Bombergirl::Button::setPadding(float padding) {
    m_shape.setSize(sf::Vector2f(m_shape.getSize().x + padding, m_shape.getSize().y + padding));
}

sf::Vector2f Bombergirl::Button::getSize() {
    return m_shape.getSize();
}

sf::Vector2f Bombergirl::Button::getCenter() {
    return sf::Vector2f(m_shape.getSize().x / 2.f, m_shape.getSize().y / 2.f);
}

sf::Vector2f Bombergirl::Button::getPosition() {
    return m_shape.getPosition();
}