#pragma once

#include "base_state.h"
#include<vector>

namespace Bombergirl
{
	
	class MainMenuState : public BaseState
	{
	public:
		struct Option {
			sf::Text m_text;
			sf::Sprite m_sprite;
			const int START_POSITION_OPTION = 400;
			const int SPACE_BETWEEN_OPTION = 100;
			Option() {
				m_text.setCharacterSize(40);
				m_text.setOutlineThickness(2.5f);
				m_text.setOutlineColor(sf::Color{ 77, 36, 0 });
				m_text.setFillColor(sf::Color{ 255, 194, 16 });
			}

			void setPosition(unsigned int window_width, int index) {
				m_sprite.setPosition({ (window_width - m_sprite.getLocalBounds().width) / 2.f,
									(float)START_POSITION_OPTION + SPACE_BETWEEN_OPTION * index });

				m_text.setPosition({ m_sprite.getPosition().x + (m_sprite.getLocalBounds().width - m_text.getLocalBounds().width) / 2.f,
									m_sprite.getPosition().y + 8.5f });
			}

			void beActive() {
				m_text.setFillColor(sf::Color{ 218, 78, 83 });
			}

			void beInactive() {
				m_text.setFillColor(sf::Color{ 255, 194, 16 });
			}
		};
	private:
		sf::Sprite m_title;
		sf::Sprite m_backgroundSprite;
		sf::Sprite m_arrow;
		std::vector<Option> m_optionList;
		int m_option;
		sf::Sound *m_soundBack;
		sf::Sound *m_soundClick;
		sf::Sound* m_soundConfirm;

	public:
		const int NUMBER_OPTION = 4;
		MainMenuState(SharedContext* sharedContext);

		void init() override;
		void handleInput() override;
		void update(const float&) override;
		void render() override;

		~MainMenuState();
	};
}

