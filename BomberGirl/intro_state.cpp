#include "intro_state.h"
#include "configs.h"
#include "main_menu_state.h"

Bombergirl::IntroState::IntroState(SharedContext* sharedContext) : BaseState(sharedContext), m_totalTime(0.f) {}

void Bombergirl::IntroState::init()
{
    // load resources
    m_sharedContext->m_resources->loadTexture("logo", INTRO_LOGO_PATH);

    // init components
    auto windowSize = m_sharedContext->m_window->getSize();
    m_logo.setTexture(m_sharedContext->m_resources->getTexture("logo"));
    m_logo.setPosition({ windowSize.x / 2.f - m_logo.getTexture()->getSize().x / 2.f, windowSize.y / 2.f - m_logo.getTexture()->getSize().y / 2.f });

    // sound
    //m_sharedContext->m_resources->loadSoundBuffer("intro_sound", INTRO_SOUND);
    //sf::SoundBuffer sf = m_sharedContext->m_resources->getSoundBuffer("intro_sound");
    //m_sound.setBuffer(sf);
    //m_sound.play();
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
        //m_sound.pause();
        m_sharedContext->m_stateManager->push(new MainMenuState(m_sharedContext));
        m_totalTime = 0.f;
    }
}

void Bombergirl::IntroState::render()
{
    m_sharedContext->m_window->draw(m_logo);

}

