#include "about_state.h"
#include "configs.h"

Bombergirl::AboutState::AboutState(Bombergirl::SharedContext* sharedContext) : BaseState(sharedContext),m_isTextEnd(false) {}

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

    m_textEnd.setFont(m_sharedContext->m_resources->getFont("garamond"));
    m_textEnd.setString("THANKS FOR WATCHING!");
    m_textEnd.setCharacterSize(125u);
    m_textEnd.setFillColor(sf::Color(0u, 0u, 0u));
    sf::FloatRect bounds = m_textEnd.getLocalBounds();
    m_textEnd.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
    m_textEnd.setPosition(windowSize.x / 2.f, windowSize.y / 2.f - 150);

    m_textBackToMenu.setFont(m_sharedContext->m_resources->getFont("garamond"));
    m_textBackToMenu.setString("PRESS ENTER TO BACK TO MAIN MENU");
    m_textBackToMenu.setCharacterSize(75u);
    bounds = m_textBackToMenu.getLocalBounds();
    m_textBackToMenu.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
    m_textBackToMenu.setPosition(windowSize.x / 2.f, windowSize.y / 2.f + 50);


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
    if (!m_isTextEnd) {
        if (m_textImage.getPosition().y + m_textImage.getLocalBounds().height <= m_whiteRectUp.getSize().y) {
            m_isTextEnd = true;
        }
        else {
            m_textImage.move(0.f, -TEXT_SPEED * dt);
        }
    }
    else
    {
        alpha += speed * dt;
        if (alpha < 0)
        {
            alpha = 0;
            speed = -speed;
        }
        else if (alpha > 255)
        {
            alpha = 255;
            speed = -speed;
        }
        m_textBackToMenu.setFillColor(sf::Color(0u, 0u, 0u, (unsigned int)alpha));
    }
}

void Bombergirl::AboutState::render()
{
    m_sharedContext->m_window->draw(m_whiteBackground);
    if (m_isTextEnd == false) {
        m_sharedContext->m_window->draw(m_textImage);
    }
    m_sharedContext->m_window->draw(m_whiteRectUp);
    m_sharedContext->m_window->draw(m_whiteRectDown);
    if (m_isTextEnd == true)
    {
        m_sharedContext->m_window->draw(m_textEnd);
        m_sharedContext->m_window->draw(m_textBackToMenu);
    }
}
