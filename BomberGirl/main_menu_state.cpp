#include "main_menu_state.h"
#include "paused_state.h"
#include "configs.h"

Bombergirl::MainMenuState::MainMenuState(SharedContext* sharedContext) : BaseState(sharedContext) {}

void Bombergirl::MainMenuState::init()
{
    // load resources
    m_sharedContext->m_resources->loadFont("garamond", GARAMOND_FONT_PATH);
    m_sharedContext->m_resources->loadTexture("background_menu", BACKGROUND_MENU_PATH);

    // init components
    m_mainMenuText.setFont(m_sharedContext->m_resources->getFont("garamond"));
    m_mainMenuText.setString("MAIN   MENU");
    m_mainMenuText.setCharacterSize(75u);
    sf::FloatRect bounds = m_mainMenuText.getLocalBounds();
    m_mainMenuText.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
    auto windowSize = m_sharedContext->m_window->getSize();
    m_mainMenuText.setPosition(windowSize.x / 2.f, windowSize.y / 2.f - 300);

    //background
    m_backgroundSprite.setTexture(m_sharedContext->m_resources->getTexture("background_menu"));
}

void Bombergirl::MainMenuState::handleInput()
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
            if (e.key.code == sf::Keyboard::Escape) {
                m_sharedContext->m_window->close();

            }   
        }
    }
}

void Bombergirl::MainMenuState::update(const float& dt)
{
}

void Bombergirl::MainMenuState::render()
{
    m_sharedContext->m_window->draw(m_backgroundSprite);
    m_sharedContext->m_window->draw(m_mainMenuText);
}

