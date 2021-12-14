#include "GameState.h"
#include "configs.h"

Bombergirl::GameState::GameState(SharedContext* sharedContext, const sf::String& character_1, const sf::String& character_2) : BaseState(sharedContext)
{
    m_sharedContext->m_resources->loadTexture("shadow1", PLAYER_SHADOW_PATH);
    m_sharedContext->m_resources->loadTexture("shadow2", PLAYER_SHADOW_PATH);

    m_player1 = new Player(&m_sharedContext->m_resources->getTexture(character_1), &m_sharedContext->m_resources->getTexture("shadow1"), true);
    m_player2 = new Player(&m_sharedContext->m_resources->getTexture(character_2), &m_sharedContext->m_resources->getTexture("shadow2"), false);
    
    m_player1->setArena(m_sharedContext->m_window->getSize());
    m_player2->setArena(m_sharedContext->m_window->getSize());
}

Bombergirl::GameState::~GameState()
{
    delete m_player1;
    delete m_player2;
}

void Bombergirl::GameState::init()
{
    auto windowSize = m_sharedContext->m_window->getSize();
    m_background.setFillColor(sf::Color::White);
    m_background.setSize({ (float)windowSize.x, (float)windowSize.y });
}

void Bombergirl::GameState::handleInput()
{
    sf::Event e;
    while (m_sharedContext->m_window->pollEvent(e))
    {
        if (e.type == sf::Event::Closed)
            m_sharedContext->m_window->close();
        if (e.key.code == sf::Keyboard::Escape) {
            m_sharedContext->m_window->close();
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        m_player2->moveUp();
    }   
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        m_player2->moveDown();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        m_player2->moveLeft();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        m_player2->moveRight();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        m_player1->moveUp();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        m_player1->moveDown();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        m_player1->moveLeft();
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        m_player1->moveRight();
    }
}

void Bombergirl::GameState::update(const float& dt)
{
    m_player1->update(dt);
    m_player2->update(dt);
}

void Bombergirl::GameState::render()
{
    m_player1->render(*m_sharedContext->m_window);
    m_player2->render(*m_sharedContext->m_window);
}

