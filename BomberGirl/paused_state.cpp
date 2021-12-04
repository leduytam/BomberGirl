#include "paused_state.h"
#include "configs.h"

Bombergirl::PausedState::PausedState(SharedContext* sharedContext) : BaseState(sharedContext)
{
    setTransparent(true);
}

void Bombergirl::PausedState::init()
{
    // load resources
    m_sharedContext->m_resources->loadFont("garamond", GARAMOND_FONT_PATH);

    // init components
    auto windowSize = m_sharedContext->m_window->getSize();

    m_overlay.setSize({ static_cast<float>(windowSize.x), static_cast<float>(windowSize.y) });
    m_overlay.setFillColor(sf::Color(0u, 0u, 0u, 150u));

    m_pausedText.setFont(m_sharedContext->m_resources->getFont("garamond"));
    m_pausedText.setString("PAUSED");
    m_pausedText.setCharacterSize(50u);
    sf::FloatRect bounds = m_pausedText.getLocalBounds();
    m_pausedText.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
    m_pausedText.setPosition(windowSize.x / 2.f, windowSize.y / 2.f);
}

void Bombergirl::PausedState::handleInput() {
    sf::Event e;
    while (m_sharedContext->m_window->pollEvent(e))
    {
        if (e.type == sf::Event::Closed)
            m_sharedContext->m_window->close();
        else if (e.type == sf::Event::KeyPressed)
        {
            if (e.key.code == sf::Keyboard::Enter)
                m_sharedContext->m_stateManager->pop();
            if (e.key.code == sf::Keyboard::Escape) {
                m_sharedContext->m_window->close();
            }
        }
    }
}

void Bombergirl::PausedState::update(const float& dt)
{
    
}

void Bombergirl::PausedState::render()
{
    m_sharedContext->m_window->draw(m_overlay);
    m_sharedContext->m_window->draw(m_pausedText);
}
