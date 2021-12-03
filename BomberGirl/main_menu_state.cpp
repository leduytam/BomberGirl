#include<sstream>
#include "main_menu_state.h"
#include "paused_state.h"
#include "configs.h"

Bombergirl::MainMenuState::MainMenuState(SharedContext* sharedContext) : BaseState(sharedContext){
    mainOption = STATE_OPTION::NEWGAME;
}

void Bombergirl::MainMenuState::init()
{
    // load resources
    m_sharedContext->m_resources->loadFont("garamond", GARAMOND_FONT_PATH);
    m_sharedContext->m_resources->loadTexture("background_menu", MENU_BACKGROUND_PATH);
    m_sharedContext->m_resources->loadTexture("container_menu", MENU_CONTAINER_PATH);

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
            if (e.key.code == sf::Keyboard::P)
                m_sharedContext->m_stateManager->push(new PausedState(m_sharedContext));
            if (e.key.code == sf::Keyboard::Escape) {
                m_sharedContext->m_window->close();
            }

            if (e.key.code == sf::Keyboard::Down) {
                if (mainOption == STATE_OPTION::SAVE) mainOption = STATE_OPTION::NEWGAME;
                if (mainOption == STATE_OPTION::NEWGAME) mainOption = STATE_OPTION::ABOUT;
                if (mainOption == STATE_OPTION::ABOUT) mainOption = STATE_OPTION::LOAD;
                if (mainOption == STATE_OPTION::LOAD) mainOption = STATE_OPTION::SAVE;
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
    createOptionText("Start");
}


Bombergirl::Button Bombergirl::MainMenuState::createOptionText(const std::string& option) {
    Bombergirl::Button button(m_sharedContext);
    button.setSize(sf::Vector2f(100, 100));
    button.setOutline(5, sf::Color{ 95, 2, 31 });
    auto windowSize = m_sharedContext->m_window->getSize();
    button.setText(option, sf::Color::Black, 50);
    button.setPosition(sf::Vector2f(windowSize.x / 2.f, windowSize.y / 2.f ));
    button.drawButton();
    return button;
}

sf::RectangleShape Bombergirl::MainMenuState::createContainer() {
    sf::RectangleShape menuContainer(sf::Vector2f(600, 900));
    return menuContainer;
}



