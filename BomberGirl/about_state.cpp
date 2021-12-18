#include "about_state.h"
#include "configs.h"

Bombergirl::AboutState::AboutState(Bombergirl::SharedContext* sharedContext) : BaseState(sharedContext) {}

void Bombergirl::AboutState::init()
{
    // load resource 
    m_sharedContext->m_resources->loadTexture("about_background", ABOUT_BACKGROUND_PATH);
    m_sharedContext->m_resources->loadFont("garamond", GARAMOND_FONT_PATH);
    m_sharedContext->m_resources->loadTexture("about_control", ABOUT_CONTROL_PATH);


    // init components
    m_aboutText.setFont(m_sharedContext->m_resources->getFont("garamond"));
    m_aboutText.setString("ABOUT AND CONTROL");
    m_aboutText.setCharacterSize(75u);
    sf::FloatRect bounds = m_aboutText.getLocalBounds();
    m_aboutText.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
    auto windowSize = m_sharedContext->m_window->getSize();
    m_aboutText.setPosition(windowSize.x / 2.f, windowSize.y / 2.f - 450);


    m_controlText.setFont(m_sharedContext->m_resources->getFont("garamond"));
    m_controlText.setString("BOMBER-GIRL GAME IS DEVELOPED BASED ON THE CLASSIC BOMBERMAN GAME,");
    m_controlText.setCharacterSize(30u);
    m_controlText.setPosition(windowSize.x - 1550, windowSize.y - 920);


    m_controlText2.setFont(m_sharedContext->m_resources->getFont("garamond"));
    m_controlText2.setString("CONTROL THE CHARACTER TO MOVE SKILLFULLY, PLACE BOMBS AND BLOW UP THE ENEMY!");
    m_controlText2.setCharacterSize(30u);
    m_controlText2.setPosition(windowSize.x - 1550, windowSize.y - 870);

    m_controlText3.setFont(m_sharedContext->m_resources->getFont("garamond"));
    m_controlText3.setString("THE GAME HAS ONLY ONE MODE:");
    m_controlText3.setCharacterSize(30u);
    m_controlText3.setPosition(windowSize.x - 1550, windowSize.y - 800);

    m_controlText4.setFont(m_sharedContext->m_resources->getFont("garamond"));
    m_controlText4.setString("CLASSIC ENTERTAINMENT: TAKE DOWN ALL OPPONENTS ON THE MAP.");
    m_controlText4.setCharacterSize(30u);
    m_controlText4.setPosition(windowSize.x - 1550, windowSize.y - 750);

    m_controlText5.setFont(m_sharedContext->m_resources->getFont("garamond"));
    m_controlText5.setString("LET'S SHOW OFF OUR SUPER BOMB-MAKING TALENT!");
    m_controlText5.setCharacterSize(30u);
    m_controlText5.setPosition(windowSize.x - 1550, windowSize.y - 680);




    //background
    m_background.setTexture(m_sharedContext->m_resources->getTexture("about_background"));

    //controls
    m_control.setTexture(m_sharedContext->m_resources->getTexture("about_control"));
    m_control.setPosition(windowSize.x - 1440, windowSize.y - 630);

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
    m_sharedContext->m_window->draw(m_aboutText);
    m_sharedContext->m_window->draw(m_control);
    m_sharedContext->m_window->draw(m_controlText);
    m_sharedContext->m_window->draw(m_controlText2);
    m_sharedContext->m_window->draw(m_controlText3);
    m_sharedContext->m_window->draw(m_controlText4);
    m_sharedContext->m_window->draw(m_controlText5);
}
