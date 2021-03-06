#include "intro_state.h"
#include "configs.h"
#include "main_menu_state.h"

Bombergirl::IntroState::IntroState(SharedContext* sharedContext) : BaseState(sharedContext), m_totalTime(0.f) {
    m_sound = new sf::Sound();

}

void Bombergirl::IntroState::init()
{
    // init components
    auto windowSize = m_sharedContext->m_window->getSize();
    m_logo.setTexture(m_sharedContext->m_resources->getTexture("logo"));
    m_logo.setPosition({ windowSize.x / 2.f - m_logo.getTexture()->getSize().x / 2.f, windowSize.y / 2.f - m_logo.getTexture()->getSize().y / 2.f });

    //// sounds
    m_sound->setBuffer(m_sharedContext->m_resources->getBuffer("intro_sound"));
    m_sound->play();
}

void Bombergirl::IntroState::handleInput()
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
}

void Bombergirl::IntroState::update(const float& dt)
{
    if (m_totalTime < INTRO_SCREEN_TIME)
        m_totalTime += dt;
    else
    {
        m_sharedContext->m_stateManager->push(new MainMenuState(m_sharedContext));
        m_totalTime = 0.f;
    }
}

void Bombergirl::IntroState::render()
{
    m_sharedContext->m_window->draw(m_logo);

}


Bombergirl::IntroState::~IntroState() {
    delete m_sound;
}

