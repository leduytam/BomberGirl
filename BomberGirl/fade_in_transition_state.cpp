#include "fade_in_transition_state.h"

Bombergirl::FadeInTransitionState::FadeInTransitionState(SharedContext* sharedContext) : BaseState(sharedContext), m_existTime(1.f), m_totalTime(0.f)
{
    setTransparent(true);
}

void Bombergirl::FadeInTransitionState::init()
{
    sf::Vector2u windowSize = m_sharedContext->m_window->getSize();
    m_overlay.setSize({ static_cast<float>(windowSize.x), static_cast<float>(windowSize.y) });
}

void Bombergirl::FadeInTransitionState::handleInput()
{
    sf::Event e;
    while (m_sharedContext->m_window->pollEvent(e))
    {
        if (e.type == sf::Event::Closed)
            m_sharedContext->m_window->close();
        else if (e.type == sf::Event::KeyPressed)
        {
            if (e.key.code == sf::Keyboard::Escape) {
                m_sharedContext->m_window->close();
            }
        }
    }
}

void Bombergirl::FadeInTransitionState::update(const float& dt)
{
    m_totalTime += dt;

    unsigned int alpha = m_totalTime >= m_existTime ? 255u : static_cast<unsigned int>(255u * m_totalTime / m_existTime);
    m_overlay.setFillColor(sf::Color(0u, 0u, 0u, 255u - alpha));

    if (alpha == 255u)
        m_sharedContext->m_stateManager->pop();
}

void Bombergirl::FadeInTransitionState::render()
{
    m_sharedContext->m_window->draw(m_overlay);
}
