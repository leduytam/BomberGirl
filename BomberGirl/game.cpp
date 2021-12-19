#include "game.h"
#include "configs.h"
#include "intro_state.h"

Bombergirl::Game::Game()
{
    m_sharedContext.m_window = &m_window;
    m_sharedContext.m_resources = &m_resources;
    m_sharedContext.m_stateManager = &m_stateManager;
    //m_sharedContext.m_soundManager = &m_soundManager;
    m_sharedContext.m_window->setKeyRepeatEnabled(false);

    m_window.create(sf::VideoMode(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT), GAME_TITLE, sf::Style::Default);
    m_window.setMouseCursorVisible(false);
    m_stateManager.push(new IntroState(&m_sharedContext));
}

void Bombergirl::Game::handleInput()
{
    m_stateManager.handleInput();
}

void Bombergirl::Game::update(const float& dt)
{
    m_stateManager.update(dt);
}

void Bombergirl::Game::render()
{
    m_window.clear();
    m_stateManager.render();
    m_window.display();
}

void Bombergirl::Game::run()
{
    m_clock.restart();
    while (m_window.isOpen())
    {

        m_stateManager.handleStateChanges();

        handleInput();
        update(m_clock.restart().asSeconds());

        render();
    }
}
