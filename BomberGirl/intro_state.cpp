#include "intro_state.h"
#include "configs.h"
#include "main_menu_state.h"

bombergirl::IntroState::IntroState(SharedContext* sharedContext) : BaseState(sharedContext), m_totalTime(0.f) {}

void bombergirl::IntroState::init()
{
    // load resources
    m_sharedContext->m_resources->loadFont("garamond", GARAMOND_FONT_PATH);

    // init components
    m_introText.setFont(m_sharedContext->m_resources->getFont("garamond"));
    m_introText.setString("GAME   INTRO");
    m_introText.setCharacterSize(50u);
    sf::FloatRect bounds = m_introText.getLocalBounds();
    m_introText.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
    auto windowSize = m_sharedContext->m_window->getSize();
    m_introText.setPosition(windowSize.x / 2.f, windowSize.y / 2.f);
}

void bombergirl::IntroState::handleInput()
{
    sf::Event e;
    while (m_sharedContext->m_window->pollEvent(e))
    {
        if (e.type == sf::Event::Closed)
            m_sharedContext->m_window->close();
    }
}

void bombergirl::IntroState::update(const float& dt)
{
    if (m_totalTime < INTRO_SCREEN_TIME)
        m_totalTime += dt;
    else
        m_sharedContext->m_stateManager->push(new MainMenuState(m_sharedContext), true);
}

void bombergirl::IntroState::render()
{
    m_sharedContext->m_window->draw(m_introText);
}

