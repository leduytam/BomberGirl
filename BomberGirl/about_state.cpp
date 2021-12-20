#include "about_state.h"
#include "configs.h"

Bombergirl::AboutState::AboutState(Bombergirl::SharedContext* sharedContext) : BaseState(sharedContext) {}

void Bombergirl::AboutState::init()
{
    m_textImage.setTexture(m_sharedContext->m_resources->getTexture("about_text_image"));
    auto windowSize = m_sharedContext->m_window->getSize();
    m_whiteBackground.setSize(sf::Vector2f(windowSize.x*1.f, windowSize.y*1.f));
    m_whiteBackground.setFillColor(sf::Color::White);

    m_whiteRectUp.setSize(sf::Vector2f(windowSize.x * 1.f, windowSize.y* 0.15f));
    m_whiteRectUp.setFillColor(sf::Color::White);

    m_whiteRectDown.setSize(sf::Vector2f(windowSize.x * 1.f, windowSize.y * 0.15f));
    m_whiteRectDown.setFillColor(sf::Color::White);
    m_whiteRectDown.setPosition(0.f, windowSize.y - m_whiteRectDown.getSize().y);

    m_textImage.setPosition(windowSize.x - 960.f, m_whiteRectDown.getPosition().y);

    
}

void Bombergirl::AboutState::handleInput()
{
    sf::Event e;
    while (m_sharedContext->m_window->pollEvent(e))
    {
        if (e.type == sf::Event::Closed)
            m_sharedContext->m_window->close();
        else if (e.key.code == sf::Keyboard::Escape) {
            m_sharedContext->m_window->close();
        }
        else if (e.key.code == sf::Keyboard::BackSpace) {
            m_sharedContext->m_stateManager->pop();
        }
    }
}

void Bombergirl::AboutState::update(const float&dt)
{
    if (m_textImage.getPosition().y + m_textImage.getLocalBounds().height <= m_whiteRectUp.getSize().y) {
        return;
    }
    m_textImage.move(0.f, -TEXT_SPEED * dt);
}

void Bombergirl::AboutState::render()
{
    m_sharedContext->m_window->draw(m_whiteBackground);
    m_sharedContext->m_window->draw(m_textImage);
    m_sharedContext->m_window->draw(m_whiteRectUp);
    m_sharedContext->m_window->draw(m_whiteRectDown);
}
