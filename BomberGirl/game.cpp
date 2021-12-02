#include "game.h"
#include "configs.h"
#include "intro_state.h"

Bombergirl::Game::Game()
{
    m_sharedContext.m_window = &m_window;
    m_sharedContext.m_resources = &m_resources;
    m_sharedContext.m_stateManager = &m_stateManager;

    m_window.create(sf::VideoMode(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT), GAME_TITLE, sf::Style::Fullscreen);
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
    const float dt = 1.f / GAME_FPS;
    float newTime = 0.f, frameTime = 0.f, accumulator = 0.f;
    float currentTime = m_clock.getElapsedTime().asSeconds();

    while (m_window.isOpen())
    {

        m_stateManager.handleStateChanges();

        newTime = m_clock.getElapsedTime().asSeconds();
        frameTime = newTime - currentTime;

        if (frameTime >= 0.25f) frameTime = 0.25f;

        currentTime = newTime;
        accumulator += frameTime;

        while (accumulator >= dt)
        {
            handleInput();
            update(dt);
            accumulator -= dt;
        }

        render();
    }
}
