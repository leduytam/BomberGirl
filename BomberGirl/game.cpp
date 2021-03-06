#include "game.h"
#include "configs.h"
#include "intro_state.h"
#include <iostream>

Bombergirl::Game::Game()
{
    m_sharedContext = new SharedContext();
    m_sharedContext->m_window = new sf::RenderWindow(sf::VideoMode(0, 0), GAME_TITLE, sf::Style::Default);
    m_sharedContext->m_window->setVisible(false);
    m_sharedContext->m_resources = new ResourceManager();
    loadResources();
    m_sharedContext->m_window->create(sf::VideoMode(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT), GAME_TITLE, sf::Style::Fullscreen);
    m_sharedContext->m_window->setMouseCursorVisible(false);
    m_sharedContext->m_window->setKeyRepeatEnabled(false);
    m_sharedContext->m_window->setVisible(true);
    m_sharedContext->m_stateManager = new StateManager();
    m_sharedContext->m_window->setVerticalSyncEnabled(true);
    m_sharedContext->m_stateManager->push(new IntroState(m_sharedContext));
}

Bombergirl::Game::~Game()
{
    delete m_sharedContext;
}

void Bombergirl::Game::loadResources()
{
    std::cout << "Loading resource..." << std::endl;

    // game font
    m_sharedContext->m_resources->loadFont("garamond", GARAMOND_FONT_PATH);
    m_sharedContext->m_resources->loadFont("upheavtt_font", UPHEAVTT_FONT_PATH);
    m_sharedContext->m_resources->loadFont("arista_font", ARISTA_FONT_PATH);

    // intro state
    m_sharedContext->m_resources->loadTexture("logo", INTRO_LOGO_PATH);
    m_sharedContext->m_resources->loadBuffer("intro_sound", INTRO_SOUND);

    // main menu state
    m_sharedContext->m_resources->loadTexture("background_menu", MENU_BACKGROUND_PATH);
    m_sharedContext->m_resources->loadTexture("button_menu", MENU_BUTTON);
    m_sharedContext->m_resources->loadTexture("arrow_menu", MENU_ARROW);
    m_sharedContext->m_resources->loadTexture("title_menu", MENU_TITLE_TEXTURE_PATH);
    m_sharedContext->m_resources->loadBuffer("mainMenu_sound", MENU_SOUND);
    m_sharedContext->m_resources->loadBuffer("select_sound", SELECT_SOUND);
    m_sharedContext->m_resources->loadBuffer("confirm_sound", CONFIRM_SOUND);

    // pick up character state
    m_sharedContext->m_resources->loadTexture("background_menu", MENU_BACKGROUND_PATH);
    for (int i = 0; i < CHARACTER_NUMBER_OF; i++) {
        auto orderPlayer = "player_" + std::to_string(i + 1);
        m_sharedContext->m_resources->loadTexture(orderPlayer, CHARACTER_TEXTURE_PATH + orderPlayer + ".png");
    }
    m_sharedContext->m_resources->loadTexture("border_select_red", CHARACTER_BORDER_SELECT_RED);
    m_sharedContext->m_resources->loadTexture("border_select_blue", CHARACTER_BORDER_SELECT_BLUE);
    m_sharedContext->m_resources->loadBuffer("select_sound", SELECT_SOUND);
    m_sharedContext->m_resources->loadBuffer("confirm_character_sound", CHARACTER_CONFIRM_SOUND);
    

    // about state
    m_sharedContext->m_resources->loadTexture("about_text_image", ABOUT_TEXT_IMAGE);
    m_sharedContext->m_resources->loadTexture("group_about", GROUP_ABOUT_IMAGE);
    m_sharedContext->m_resources->loadTexture("light_about", LIGHT_ABOUT_IMAGE);
    m_sharedContext->m_resources->loadTexture("left_gear_about", LEFT_GEAR_ABOUT_IMAGE);
    m_sharedContext->m_resources->loadTexture("right_gear_about", RIGHT_GEAR_ABOUT_IMAGE);

    //guide state
    m_sharedContext->m_resources->loadTexture("guide_text_image", GUIDE_TEXT_IMAGE);
    m_sharedContext->m_resources->loadTexture("guide_background", GUIDE_BACKGROUND_IMAGE);

    // game state
    m_sharedContext->m_resources->loadTexture("map_background", MAP_BACKGROUND_TEXTURE_PATH);
    m_sharedContext->m_resources->loadTexture("bomb", BOMB_TEXTURE_PATH);
    m_sharedContext->m_resources->loadTexture("barrel", BARREL_TEXTURE_PATH);
    m_sharedContext->m_resources->loadTexture("explosion", EXPLOSION_TEXTURE_PATH);
    m_sharedContext->m_resources->loadTexture("flame", FLAME_TEXTURE_PATH);
    m_sharedContext->m_resources->loadTexture("items", ITEM_TEXTURE_PATH);
    m_sharedContext->m_resources->loadTexture("shadow", PLAYER_SHADOW_PATH);
    m_sharedContext->m_resources->loadTexture("background_gamestate", GAMESTATE_BACKGROUND_PATH);
    m_sharedContext->m_resources->loadTexture("timer_icon", TIMER_ICON_PATH);
    m_sharedContext->m_resources->loadTexture("character_background", CHARACTER_BACKGROUND_PATH);

    m_sharedContext->m_resources->loadBuffer("game_back_sound", GAME_SOUND);
    m_sharedContext->m_resources->loadBuffer("bombset_sound", SET_BOMB_SOUND);
    m_sharedContext->m_resources->loadBuffer("explosion_sound", EXPLOSION_SOUND);
    m_sharedContext->m_resources->loadBuffer("get_item_IncreaseSpeed", GET_ITEM_INCREASESPEED_SOUND);
    m_sharedContext->m_resources->loadBuffer("get_item_IncreaseBombCount", GET_ITEM_INCREASEBOMBCOUNT_SOUND);
    m_sharedContext->m_resources->loadBuffer("get_item_IncreaseBombRange", GET_ITEM_INCREASEBOMBRANGE_SOUND);
    m_sharedContext->m_resources->loadBuffer("tick_sound", TICK_SOUND);
    m_sharedContext->m_resources->loadBuffer("hit_sound", HIT_SOUND);
    m_sharedContext->m_resources->loadBuffer("win_sound", WIN_SOUND);
    m_sharedContext->m_resources->loadBuffer("ready_sound", READY_SOUND);
    m_sharedContext->m_resources->loadBuffer("start_sound", START_SOUND);
    m_sharedContext->m_resources->loadBuffer("draw_sound", DRAW_SOUND);
}

void Bombergirl::Game::handleInput()
{
    m_sharedContext->m_stateManager->handleInput();
}

void Bombergirl::Game::update(const float& dt)
{
    m_sharedContext->m_stateManager->update(dt);
}

void Bombergirl::Game::render()
{
    m_sharedContext->m_window->clear();
    m_sharedContext->m_stateManager->render();
    m_sharedContext->m_window->display();
}

void Bombergirl::Game::run()
{
    m_clock.restart();
    while (m_sharedContext->m_window->isOpen())
    {
        m_sharedContext->m_stateManager->handleStateChanges();

        handleInput();
        update(m_clock.restart().asSeconds());

        render();
    }
}
