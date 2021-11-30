#include "main_menu_state.h"
#include "paused_state.h"
#include "configs.h"

bombergirl::MainMenuState::MainMenuState(SharedContext* sharedContext) : BaseState(sharedContext) {}

void bombergirl::MainMenuState::init()
{
    // load resources
    m_sharedContext->m_resources->loadFont("garamond", GARAMOND_FONT_PATH);

    // init components
    m_mainMenuText.setFont(m_sharedContext->m_resources->getFont("garamond"));
    m_mainMenuText.setString("MAIN MENU");
    m_mainMenuText.setCharacterSize(50u);
    sf::FloatRect bounds = m_mainMenuText.getLocalBounds();
    m_mainMenuText.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
    auto windowSize = m_sharedContext->m_window->getSize();
    m_mainMenuText.setPosition(windowSize.x / 2.f, windowSize.y / 2.f);
}

void bombergirl::MainMenuState::handleInput()
{
    sf::Event e;
    while (m_sharedContext->m_window->pollEvent(e))
    {
        if (e.type == sf::Event::Closed)
            m_sharedContext->m_window->close();
        else if (e.type == sf::Event::KeyPressed)
        {
            if (e.key.code == sf::Keyboard::Enter)
                m_sharedContext->m_stateManager->push(new PausedState(m_sharedContext));
        }
    }
}

void bombergirl::MainMenuState::update(const float& dt)
{
}

void bombergirl::MainMenuState::render()
{
    m_sharedContext->m_window->draw(m_mainMenuText);
}

