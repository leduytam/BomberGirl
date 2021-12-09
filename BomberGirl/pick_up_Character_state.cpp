#include "pick_up_Character_state.h"
#include "configs.h"
#include <string>
#include <iostream>

Bombergirl::PickUpCharacterState::PickUpCharacterState(SharedContext* sharedContext) :BaseState(sharedContext) {
	m_select_1 = 0;
	m_select_2 = 1;
	m_character_1 = "";
	m_character_2 = "";
}

void Bombergirl::PickUpCharacterState::init() {
	// load resource
	m_sharedContext->m_resources->loadFont("garamond", GARAMOND_FONT_PATH);
	m_sharedContext->m_resources->loadTexture("background_menu", MENU_BACKGROUND_PATH);
	for (int i = 0; i < CHARACTER_NUMBER_OF; i++) {
		auto orderPlayer = "player_" + std::to_string(i + 1);
		m_sharedContext->m_resources->loadTexture(orderPlayer, CHARACTER_TEXTURE_PATH + orderPlayer + ".png");
	}
	m_sharedContext->m_resources->loadTexture("border_select_red", CHARACTER_BORDER_SELECT_RED);
	m_sharedContext->m_resources->loadTexture("border_select_blue", CHARACTER_BORDER_SELECT_BLUE);


	// init component
	m_pickUpText.setFont(m_sharedContext->m_resources->getFont("garamond"));
	m_pickUpText.setString("PICK UP CHARACTER");
	m_pickUpText.setCharacterSize(75u);
	sf::FloatRect bounds = m_pickUpText.getLocalBounds();
	m_pickUpText.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
	auto windowSize = m_sharedContext->m_window->getSize();
	m_pickUpText.setPosition(windowSize.x / 2.f, windowSize.y / 2.f - 350);


	for (int i = 0; i < CHARACTER_NUMBER_OF; i++) {
		auto orderPlayer = "player_" + std::to_string(i + 1);
		auto sprite = sf::Sprite(m_sharedContext->m_resources->getTexture(orderPlayer));
		sprite.setPosition((windowSize.x - (sprite.getLocalBounds().width * CHARACTER_NUMBER_OF + (CHARACTER_NUMBER_OF - 1) * (200 - sprite.getLocalBounds().width))) / 2.f + 200 * i + sprite.getLocalBounds().width / 2, 400);
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

			// control
			if (m_character_2 == "") {
				if (e.key.code == sf::Keyboard::Left) {
					m_select_2 = (m_select_2 - 1 + CHARACTER_NUMBER_OF) % CHARACTER_NUMBER_OF;
					if (m_select_2 == m_select_1) m_select_2 = (m_select_2 - 1 + CHARACTER_NUMBER_OF) % CHARACTER_NUMBER_OF;
				}
				if (e.key.code == sf::Keyboard::Right) {
					m_select_2 = (m_select_2 + 1) % CHARACTER_NUMBER_OF;
					if (m_select_2 == m_select_1) m_select_2 = (m_select_2 + 1 + CHARACTER_NUMBER_OF) % CHARACTER_NUMBER_OF;
				}
			}

			if (m_character_1 == "") {
				if (e.key.code == sf::Keyboard::A) {
					m_select_1 = (m_select_1 - 1 + CHARACTER_NUMBER_OF) % CHARACTER_NUMBER_OF;
					if (m_select_2 == m_select_1) m_select_1 = (m_select_1 - 1 + CHARACTER_NUMBER_OF) % CHARACTER_NUMBER_OF;
				}
				if (e.key.code == sf::Keyboard::D) {
					m_select_1 = (m_select_1 + 1) % CHARACTER_NUMBER_OF;
					if (m_select_2 == m_select_1) m_select_1 = (m_select_1 + 1 + CHARACTER_NUMBER_OF) % CHARACTER_NUMBER_OF;
				}
			}

			// select
			if (e.key.code == sf::Keyboard::RShift) {
				lockSelect(2, m_lockBackground_2, sf::Vector2f(m_characters[m_select_2].getLocalBounds().width, m_characters[m_select_2].getLocalBounds().height), m_borderSelect_2.getPosition());
				m_character_2 = "player_" + std::to_string(m_select_2 + 1);
			}
			if (e.key.code == sf::Keyboard::LShift) {
				lockSelect(1, m_lockBackground_1, sf::Vector2f(m_characters[m_select_1].getLocalBounds().width, m_characters[m_select_1].getLocalBounds().height), m_borderSelect_1.getPosition());
				m_character_1 = "player_" + std::to_string(m_select_1 + 1);
			}
		}

	}
}

void Bombergirl::PickUpCharacterState::update(const float& dt) {

	m_borderSelect_1.setPosition(m_characters[m_select_1].getPosition());
	m_borderSelect_2.setPosition(m_characters[m_select_2].getPosition());
	if (m_character_1 != "" && m_character_2 != "") {
		
	}

}

void Bombergirl::PickUpCharacterState::render() {
	m_sharedContext->m_window->draw(m_backgroundSprite);
	m_sharedContext->m_window->draw(m_pickUpText);
	for (auto i = 0; i < m_characters.size(); i++) {

		m_sharedContext->m_window->draw(m_characters[i]);

	}
	m_sharedContext->m_window->draw(m_lockBackground_2);
	m_sharedContext->m_window->draw(m_lockBackground_1);

	m_sharedContext->m_window->draw(m_borderSelect_1);
	m_sharedContext->m_window->draw(m_borderSelect_2);
}


void Bombergirl::PickUpCharacterState::lockSelect(int order, sf::RectangleShape& lockSelect, const sf::Vector2f& size, const sf::Vector2f&position) {
	
	lockSelect.setSize(size);
	lockSelect.setOrigin(size.x /2, size.y / 2);
	if (order == 2) lockSelect.setFillColor(sf::Color{ 228, 33, 22 , 100 });
	else lockSelect.setFillColor(sf::Color{ 69, 148, 200, 100 });

	lockSelect.setTexture()
	lockSelect.setPosition(position.x , position.y);

}
