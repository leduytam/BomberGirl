#include "paused_state.h"
#include "configs.h"

Bombergirl::PausedState::PausedState(SharedContext* sharedContext, sf::Sound* soundBack) :
    BaseState(sharedContext), m_soundBack(soundBack), m_option(0)
{
    setTransparent(true);
    
    m_soundClick = new sf::Sound();
    m_soundConfirm = new sf::Sound();
    m_optionList.resize(NUMBER_OPTION);
}

Bombergirl::PausedState::~PausedState()
{
	delete m_soundClick;
	delete m_soundConfirm;
}

void Bombergirl::PausedState::init()
{
    auto windowSize = m_sharedContext->m_window->getSize();

    m_overlay.setSize({ static_cast<float>(windowSize.x), static_cast<float>(windowSize.y) });
    m_overlay.setFillColor(sf::Color(0u, 0u, 0u, 200));

	m_title.setTexture(m_sharedContext->m_resources->getTexture("title_menu"));
	m_title.setPosition({ (windowSize.x - m_title.getLocalBounds().width) / 2.f, 100.f });

	//arrow
	m_arrow.setTexture(m_sharedContext->m_resources->getTexture("arrow_menu"));

	//options
	for (int i = 0; i < NUMBER_OPTION; i++) {
		m_optionList[i].m_text.setFont(m_sharedContext->m_resources->getFont("arista_font"));
		switch (i)
		{
		case 0:
			m_optionList[i].m_text.setString("CONTINUE");
			break;
		case 1:
			m_optionList[i].m_text.setString("BACK TO MENU");
			break;
		case 2:
			m_optionList[i].m_text.setString("EXIT");
			break;
		}
		m_optionList[i].m_sprite.setTexture(m_sharedContext->m_resources->getTexture("button_menu"));
		m_optionList[i].setPosition(windowSize.x, i);
	}

	m_soundClick->setBuffer(m_sharedContext->m_resources->getBuffer("select_sound"));
	m_soundConfirm->setBuffer(m_sharedContext->m_resources->getBuffer("confirm_sound"));
}

void Bombergirl::PausedState::handleInput() {
    sf::Event e;
    while (m_sharedContext->m_window->pollEvent(e))
    {
        if (e.type == sf::Event::Closed)
            m_sharedContext->m_window->close();
        else if (e.type == sf::Event::KeyPressed)
		{
			if (e.key.code == sf::Keyboard::Escape) {
				m_sharedContext->m_window->close();
			}
			else if (e.key.code == sf::Keyboard::Down) {
				m_optionList[m_option].beInactive();
				m_option++;
				m_option %= NUMBER_OPTION;
				m_soundClick->play();
			}
			else if (e.key.code == sf::Keyboard::Up) {
				m_optionList[m_option].beInactive();
				m_option--;
				if (m_option < 0) m_option = NUMBER_OPTION - 1;
				m_soundClick->play();
			}
			else if (e.key.code == sf::Keyboard::Enter) {
				m_soundConfirm->play();
				switch (m_option)
				{
				case 0:
					m_sharedContext->m_stateManager->pop();
					break;
				case 1:
					m_sharedContext->m_stateManager->pop();
					m_sharedContext->m_stateManager->pop();
					m_soundBack->stop();
					break;
				case 2:
					m_sharedContext->m_window->close();
				default:
					break;
				}
			}
        }
    }
}

void Bombergirl::PausedState::update(const float& dt)
{
	m_arrow.setPosition(sf::Vector2f(m_optionList[m_option].m_sprite.getPosition().x - m_arrow.getLocalBounds().width,
		m_optionList[m_option].m_sprite.getPosition().y + (m_optionList[m_option].m_sprite.getLocalBounds().height - 24) / 2.f));

	m_optionList[m_option].beActive();
	if (m_soundBack->getStatus() == sf::Sound::Paused) {
		m_soundBack->play();
	}
}

void Bombergirl::PausedState::render()
{
    m_sharedContext->m_window->draw(m_overlay);
	m_sharedContext->m_window->draw(m_title);
	m_sharedContext->m_window->draw(m_arrow);
	for (auto option : m_optionList) {
		m_sharedContext->m_window->draw(option.m_sprite);
		m_sharedContext->m_window->draw(option.m_text);
	}
}
