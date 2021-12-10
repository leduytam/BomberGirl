#include "about_state.h"
#include "configs.h"

Bombergirl::AboutState::AboutState(Bombergirl::SharedContext* sharedContext) : BaseState(sharedContext) {}

void Bombergirl::AboutState::init()
{
    // load resource 
    m_sharedContext->m_resources->loadTexture("about_background", ABOUT_BACKGROUND_PATH);

    m_background.setTexture(m_sharedContext->m_resources->getTexture("about_background"));
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

void Bombergirl::AboutState::update(const float&)
{

}

void Bombergirl::AboutState::render()
{
    m_sharedContext->m_window->draw(m_background);
}
