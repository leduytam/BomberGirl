#include<sstream>
#include "main_menu_state.h"
#include "paused_state.h"
#include "pick_up_Character_state.h"
#include "about_state.h"
#include "guide_state.h"
#include "configs.h"

Bombergirl::MainMenuState::MainMenuState(SharedContext* sharedContext) : BaseState(sharedContext) {
	m_option = 0;
	m_soundBack = new sf::Sound();
	m_soundClick = new sf::Sound();
	m_soundConfirm = new sf::Sound();
	m_optionList.resize(NUMBER_OPTION);
}

void Bombergirl::MainMenuState::init()
{
	auto windowSize = m_sharedContext->m_window->getSize();

	// init components
	m_title.setTexture(m_sharedContext->m_resources->getTexture("title_menu"));
	m_title.setPosition({ (windowSize.x - m_title.getLocalBounds().width) / 2.f, 100.f });

	//background
	m_backgroundSprite.setTexture(m_sharedContext->m_resources->getTexture("background_menu"));

	//arrow
	m_arrow.setTexture(m_sharedContext->m_resources->getTexture("arrow_menu"));
	
	//options
	for (int i = 0; i < NUMBER_OPTION; i++) {
		m_optionList[i].m_text.setFont(m_sharedContext->m_resources->getFont("arista_font"));
		switch (i)
		{
		case 0:
			m_optionList[i].m_text.setString("PLAY");
			break;
		case 1:
			m_optionList[i].m_text.setString("GUIDE");
			break;
		case 2:
			m_optionList[i].m_text.setString("ABOUT");
			break;
		case 3:
			m_optionList[i].m_text.setString("EXIT");
			break;
		}
		m_optionList[i].m_sprite.setTexture(m_sharedContext->m_resources->getTexture("button_menu"));
		m_optionList[i].setPosition(windowSize.x, i);
	}

	m_soundBack->setBuffer(m_sharedContext->m_resources->getBuffer("mainMenu_sound"));
	m_soundBack->setLoop(true);
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

			if (e.key.code == sf::Keyboard::BackSpace) {
				m_sharedContext->m_stateManager->pop();
			}

			if (e.key.code == sf::Keyboard::Down) {
				m_optionList[m_option].beInactive();
				m_option = m_option++;
				m_option %= 4;
				m_soundClick->play();
			}

			if (e.key.code == sf::Keyboard::Up) {
				m_optionList[m_option].beInactive();
				m_option = m_option--;
				if (m_option < 0) m_option = 3;
				m_soundClick->play();

			}
			if (e.key.code == sf::Keyboard::Enter) {
				m_soundConfirm->play();
				switch (m_option)
				{
				case 0:
					m_sharedContext->m_stateManager->push(new PickUpCharacterState(m_sharedContext, m_soundBack));
					break;
				case 1:
					m_sharedContext->m_stateManager->push(new GuideState(m_sharedContext));
					break;
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
	m_arrow.setPosition(sf::Vector2f(m_optionList[m_option].m_sprite.getPosition().x - m_arrow.getLocalBounds().width, 
									 m_optionList[m_option].m_sprite.getPosition().y + (m_optionList[m_option].m_sprite.getLocalBounds().height - 24) / 2.f));
	
	m_optionList[m_option].beActive();
	if (m_soundBack->getStatus() == sf::Sound::Paused) {
		m_soundBack->play();
	}
	
}

void Bombergirl::MainMenuState::render()
{
	m_sharedContext->m_window->draw(m_backgroundSprite);
	m_sharedContext->m_window->draw(m_title);
	m_sharedContext->m_window->draw(m_arrow);
	for (auto option : m_optionList) {
		m_sharedContext->m_window->draw(option.m_sprite);
		m_sharedContext->m_window->draw(option.m_text);
	}
}



Bombergirl::MainMenuState::~MainMenuState() {
	delete m_soundBack;
	delete m_soundClick;
	delete m_soundConfirm;
}
