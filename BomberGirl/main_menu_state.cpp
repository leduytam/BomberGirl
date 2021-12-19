#include<sstream>
#include<iostream>
#include "main_menu_state.h"
#include "paused_state.h"
#include "pick_up_Character_state.h"
#include "about_state.h"
#include "configs.h"

Bombergirl::MainMenuState::MainMenuState(SharedContext* sharedContext) : BaseState(sharedContext) {
	m_option = 0;
	m_soundBack = new sf::Sound();
	m_soundClick = new sf::Sound();
	m_soundConfirm = new sf::Sound();
}

void Bombergirl::MainMenuState::init()
{
	// load resources
	m_sharedContext->m_resources->loadFont("garamond", GARAMOND_FONT_PATH);
	m_sharedContext->m_resources->loadTexture("background_menu", MENU_BACKGROUND_PATH);
	m_sharedContext->m_resources->loadTexture("container_menu", MENU_SYSTEM_PATH);
	m_sharedContext->m_resources->loadTexture("arrow_menu", MENU_SYSTEM_PATH, sf::IntRect(sf::Vector2i(144, 96), sf::Vector2i(24, 24)));

	// init components
	m_mainMenuText.setFont(m_sharedContext->m_resources->getFont("garamond"));
	m_mainMenuText.setString("MAIN   MENU");
	m_mainMenuText.setCharacterSize(75u);
	sf::FloatRect bounds = m_mainMenuText.getLocalBounds();
	m_mainMenuText.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
	auto windowSize = m_sharedContext->m_window->getSize();
	m_mainMenuText.setPosition(windowSize.x / 2.f, windowSize.y / 2.f - 350);

	//background
	m_backgroundSprite.setTexture(m_sharedContext->m_resources->getTexture("background_menu"));

	//arrow
	m_arrow.setTexture(m_sharedContext->m_resources->getTexture("arrow_menu"));
	m_arrow.setOrigin(m_arrow.getLocalBounds().width / 2.f, m_arrow.getLocalBounds().height / 2.f);
	m_arrow.setScale(sf::Vector2f(2, 2));
	m_arrow.setRotation(-90);

	//options
	for (int i = 0; OPTION(i) < OPTION::MAX; i++) {
		Button btn = createOption();
		switch (i)
		{
		case 0:
			btn.setText("Play");
			break;
		case 1:
			btn.setText("Continue");
			break;
		case 2:
			btn.setText("About");
			break;
		case 3:
			btn.setText("Exit");
			break;
		}
		btn.setPadding(20);
		btn.setPosition(sf::Vector2f((float)windowSize.x / 2.f - btn.getCenter().x, (float)START_POSITION_OPTION + SPACE_BETWEEN_OPTION * i));
		options_Button.push_back(btn);
	}
	m_sharedContext->m_resources->loadBuffer("mainMenu_sound", MENU_SOUND);
	m_sharedContext->m_resources->loadBuffer("select_sound", MENU_SELECT_SOUND);
	m_sharedContext->m_resources->loadBuffer("confirm_sound", MENU_CONFIRM_SOUND);

	m_soundBack->setBuffer(m_sharedContext->m_resources->getBuffer("mainMenu_sound"));
	m_soundClick->setBuffer(m_sharedContext->m_resources->getBuffer("select_sound"));
	m_soundConfirm->setBuffer(m_sharedContext->m_resources->getBuffer("confirm_sound"));
	m_soundBack->play();
}

void Bombergirl::MainMenuState::handleInput()
{
	sf::Event e;
	while (m_sharedContext->m_window->pollEvent(e))
	{
		if (e.type == sf::Event::Closed) {
			m_sharedContext->m_window->close();
		}
		else if (e.type == sf::Event::KeyPressed)
		{
			if (e.key.code == sf::Keyboard::Escape) {
				m_sharedContext->m_window->close();
			}

			if (e.key.code == sf::Keyboard::P) {
				m_sharedContext->m_stateManager->push(new PausedState(m_sharedContext));
			}

			if (e.key.code == sf::Keyboard::BackSpace) {
				m_sharedContext->m_stateManager->pop();
			}

			if (e.key.code == sf::Keyboard::Down) {
				m_option = m_option++;
				m_option %= 4;
				m_soundClick->play();
			}

			if (e.key.code == sf::Keyboard::Up) {
				m_option = m_option--;
				if (m_option < 0) m_option = 3;
				m_soundClick->play();

			}
			if (e.key.code == sf::Keyboard::Enter) {
				m_soundConfirm->play();
				switch (m_option)
				{
				case 0:
					m_sharedContext->m_stateManager->push(new PickUpCharacterState(m_sharedContext));
					break;
				case 1:
				case 2:
					m_sharedContext->m_stateManager->push(new AboutState(m_sharedContext));
					break;
				case 3:
					m_sharedContext->m_window->close();
				default:
					break;
				}
			}
		}
	}
}

void Bombergirl::MainMenuState::update(const float& dt)
{
	m_arrow.setPosition(sf::Vector2f(options_Button[m_option].getPosition().x - m_arrow.getLocalBounds().width, options_Button[m_option].getPosition().y + options_Button[m_option].getCenter().y));
	selectOption(m_option);
}

void Bombergirl::MainMenuState::render()
{
	m_sharedContext->m_window->draw(m_backgroundSprite);
	m_sharedContext->m_window->draw(m_mainMenuText);
	m_sharedContext->m_window->draw(m_arrow);
	drawMenuOption();
}

Bombergirl::Button Bombergirl::MainMenuState::createOption() {
	Bombergirl::Button button(m_sharedContext);
	button.setOutline(0, sf::Color{ 95, 2, 31 });
	button.setBackgroundColor();
	return button;
}

void Bombergirl::MainMenuState::drawMenuOption() {
	for (size_t i = 0; i < options_Button.size(); i++) {
		options_Button[i].drawButton();
	}
}

void Bombergirl::MainMenuState::selectOption(int option) {
	for (size_t i = 0; i < options_Button.size(); i++) {
		options_Button[i].setOutline(0);
		options_Button[i].setBackgroundColor();
		if (i == option) {
			options_Button[i].setOutline(2);
			options_Button[i].setBackgroundColor(sf::Color{ 255, 255, 255, 100 });
		}
	}
}

Bombergirl::MainMenuState::~MainMenuState() {
	delete m_soundBack;
	delete m_soundClick;
	delete m_soundConfirm;
}


