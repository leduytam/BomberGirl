#include "pick_up_character_state.h"
#include "configs.h"
#include <string>
#include "game_state.h"

Bombergirl::PickUpCharacterState::PickUpCharacterState(SharedContext* sharedContext, sf::Sound*backSound) :BaseState(sharedContext) {
	m_select_1 = 0;
	m_select_2 = 1;
	m_character_value_1 = "";
	m_character_value_2 = "";
	m_soundClick = new sf::Sound();
	m_soundconfirm = new sf::Sound();
	if (backSound) {
		m_backsound = backSound;
	}
	else m_backsound = new sf::Sound();
	m_transition = 0.f;
	m_donePickingUp = false;
}

void Bombergirl::PickUpCharacterState::init() {
	// init component
	auto windowSize = m_sharedContext->m_window->getSize();

	setText(m_pickUpText, 75u, "PICK UP CHARACTER");
	m_pickUpText.setPosition(windowSize.x / 2.f, windowSize.y / 2.f - 350);

	// player select
	setText(m_character_text_1, 50u, "Player 1");
	setText(m_character_text_2, 50u, "Player 2");
	m_character_text_1.setPosition(250, 700);
	m_character_text_2.setPosition((float)windowSize.x - 250, 700.f);

	// character texture
	for (int i = 0; i < CHARACTER_NUMBER_OF; i++) {
		auto orderPlayer = "player_" + std::to_string(i + 1);
		auto sprite = sf::Sprite(m_sharedContext->m_resources->getTexture(orderPlayer));
		sprite.setPosition((windowSize.x - (sprite.getLocalBounds().width * CHARACTER_NUMBER_OF + (CHARACTER_NUMBER_OF - 1) * (200 - sprite.getLocalBounds().width))) / 2.f + 200 * i + sprite.getLocalBounds().width / 2, 500);
		sprite.setOrigin(sprite.getLocalBounds().width / 2.f, sprite.getLocalBounds().height / 2.f);
		m_characters.push_back(sprite);
	}

	//background
	m_backgroundSprite.setTexture(m_sharedContext->m_resources->getTexture("background_menu"));

	// border
	m_borderSelect_1.setTexture(m_sharedContext->m_resources->getTexture("border_select_blue"));
	m_borderSelect_2.setTexture(m_sharedContext->m_resources->getTexture("border_select_red"));
	m_borderSelect_1.setOrigin(m_borderSelect_1.getLocalBounds().width / 2.f, m_borderSelect_1.getLocalBounds().height / 2.f);
	m_borderSelect_2.setOrigin(m_borderSelect_2.getLocalBounds().width / 2.f, m_borderSelect_2.getLocalBounds().height / 2.f);
	m_borderSelect_1.setPosition(m_characters[m_select_1].getPosition());
	m_borderSelect_2.setPosition(m_characters[m_select_2].getPosition());

	//frame
	m_frame_1.setTexture(m_sharedContext->m_resources->getTexture("border_select_blue"));
	m_frame_2.setTexture(m_sharedContext->m_resources->getTexture("border_select_red"));

	m_frame_1.setScale(2, 2);
	m_frame_1.setOrigin(m_frame_1.getLocalBounds().width / 2.f, m_frame_1.getLocalBounds().height / 2.f);
	m_frame_1.setPosition(m_character_text_1.getPosition().x, 500);

	m_frame_2.setScale(2, 2);
	m_frame_2.setOrigin(m_frame_2.getLocalBounds().width / 2.f, m_frame_2.getLocalBounds().height / 2.f);
	m_frame_2.setPosition(m_character_text_2.getPosition().x, 500);

	m_soundClick->setBuffer(m_sharedContext->m_resources->getBuffer("select_sound"));
	m_soundconfirm->setBuffer(m_sharedContext->m_resources->getBuffer("confirm_character_sound"));

}

void Bombergirl::PickUpCharacterState::handleInput() {
	sf::Event e;
	while (m_sharedContext->m_window->pollEvent(e))
	{
		if (e.type == sf::Event::Closed) {
			m_sharedContext->m_window->close();
		}
		else if (e.type == sf::Event::KeyPressed)
		{
			//escape
			if (e.key.code == sf::Keyboard::Escape) {
				m_sharedContext->m_window->close();
			}

			if (e.key.code == sf::Keyboard::BackSpace && !m_donePickingUp) {
				m_soundClick->play();
				m_sharedContext->m_stateManager->pop();
			}

			// control
			if (m_character_value_2 == "") {
				if (e.key.code == sf::Keyboard::Left) {
					m_select_2 = (m_select_2 - 1 + CHARACTER_NUMBER_OF) % CHARACTER_NUMBER_OF;
					if (m_select_2 == m_select_1) m_select_2 = (m_select_2 - 1 + CHARACTER_NUMBER_OF) % CHARACTER_NUMBER_OF;
					m_soundClick->play();
				}
				if (e.key.code == sf::Keyboard::Right) {
					m_select_2 = (m_select_2 + 1) % CHARACTER_NUMBER_OF;
					if (m_select_2 == m_select_1) m_select_2 = (m_select_2 + 1 + CHARACTER_NUMBER_OF) % CHARACTER_NUMBER_OF;
					m_soundClick->play();
				}
			}

			if (m_character_value_1 == "") {
				if (e.key.code == sf::Keyboard::A) {
					m_select_1 = (m_select_1 - 1 + CHARACTER_NUMBER_OF) % CHARACTER_NUMBER_OF;
					if (m_select_2 == m_select_1) m_select_1 = (m_select_1 - 1 + CHARACTER_NUMBER_OF) % CHARACTER_NUMBER_OF;
					m_soundClick->play();
				}
				if (e.key.code == sf::Keyboard::D) {
					m_select_1 = (m_select_1 + 1) % CHARACTER_NUMBER_OF;
					if (m_select_2 == m_select_1) m_select_1 = (m_select_1 + 1 + CHARACTER_NUMBER_OF) % CHARACTER_NUMBER_OF;
					m_soundClick->play();
				}

			}

			// select
			if (e.key.code == sf::Keyboard::RShift && m_character_value_2 == "") {
				lockSelect(2, m_lockBackground_2, sf::Vector2f(m_characters[m_select_2].getLocalBounds().width, m_characters[m_select_2].getLocalBounds().height), m_borderSelect_2.getPosition());
				m_character_value_2 = "player_" + std::to_string(m_select_2 + 1);
				const sf::Texture* demo = m_characters[m_select_2].getTexture();
				m_character_select_2.setTexture(*demo);
				m_character_select_2.setOrigin(m_character_select_2.getLocalBounds().width / 2.f, m_character_select_2.getGlobalBounds().height / 2.f);
				m_character_select_2.setScale(2, 2);
				m_character_select_2.setPosition(m_frame_2.getPosition());
				m_soundconfirm->play();
			}
			if (e.key.code == sf::Keyboard::LShift && m_character_value_1 == "") {
				lockSelect(1, m_lockBackground_1, sf::Vector2f(m_characters[m_select_1].getLocalBounds().width, m_characters[m_select_1].getLocalBounds().height), m_borderSelect_1.getPosition());
				m_character_value_1 = "player_" + std::to_string(m_select_1 + 1);
				const sf::Texture* demo = m_characters[m_select_1].getTexture();
				m_character_select_1.setTexture(*demo);
				m_character_select_1.setOrigin(m_character_select_1.getLocalBounds().width / 2.f, m_character_select_1.getGlobalBounds().height / 2.f);
				m_character_select_1.setScale(2, 2);
				m_character_select_1.setPosition(m_frame_1.getPosition());
				m_soundconfirm->play();
			}
			if (m_character_value_1 != "" && m_character_value_2 != "")
			{
				m_donePickingUp = true;
			}
		}
	}
}

void Bombergirl::PickUpCharacterState::update(const float& dt) {
	m_borderSelect_1.setPosition(m_characters[m_select_1].getPosition());
	m_borderSelect_2.setPosition(m_characters[m_select_2].getPosition());
	if (m_donePickingUp) {
		if (m_transition >= TRANSITION_PICKUP_TIME) {
			m_backsound->pause();
			m_sharedContext->m_resources->loadTexture("player_face_1", CHARACTER_TEXTURE_PATH + m_character_value_1 + ".png");
			m_sharedContext->m_resources->loadTexture("player_face_2", CHARACTER_TEXTURE_PATH + m_character_value_2 + ".png");
			m_sharedContext->m_resources->loadTexture("player_movement_1", PLAYER_MOVEMENT_TEXTURE_PATH + m_character_value_1 + ".png");
			m_sharedContext->m_resources->loadTexture("player_movement_2", PLAYER_MOVEMENT_TEXTURE_PATH + m_character_value_2 + ".png");
			m_sharedContext->m_stateManager->push(new GameState(m_sharedContext), true);
		}
		else {
			m_transition += dt;
		}
	}
}

void Bombergirl::PickUpCharacterState::render() {
	m_sharedContext->m_window->draw(m_backgroundSprite);
	m_sharedContext->m_window->draw(m_pickUpText);
	for (unsigned int i = 0; i < m_characters.size(); i++) {
		m_sharedContext->m_window->draw(m_characters[i]);
	}

	m_sharedContext->m_window->draw(m_lockBackground_2);
	m_sharedContext->m_window->draw(m_lockBackground_1);

	m_sharedContext->m_window->draw(m_borderSelect_1);
	m_sharedContext->m_window->draw(m_borderSelect_2);

	m_sharedContext->m_window->draw(m_character_text_1);
	m_sharedContext->m_window->draw(m_character_text_2);

	m_sharedContext->m_window->draw(m_character_select_1);
	m_sharedContext->m_window->draw(m_character_select_2);

	m_sharedContext->m_window->draw(m_frame_1);
	m_sharedContext->m_window->draw(m_frame_2);
}

void Bombergirl::PickUpCharacterState::lockSelect(int order, sf::RectangleShape& background, const sf::Vector2f& size, const sf::Vector2f& position) {

	background.setSize(size);
	background.setOrigin(size.x / 2, size.y / 2);
	if (order == 2) background.setFillColor(sf::Color{ 228, 33, 22 , 100 });
	else background.setFillColor(sf::Color{ 69, 148, 200, 100 });
	background.setPosition(position.x, position.y);
}

void Bombergirl::PickUpCharacterState::setText(sf::Text & text, const int& charactersize, const sf::String& content) {
	text.setFont(m_sharedContext->m_resources->getFont("upheavtt_font"));
	text.setString(content);
	text.setCharacterSize(charactersize);
	sf::FloatRect bounds = text.getLocalBounds();
	text.setStyle(sf::Text::Style::Bold);
	text.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
}
