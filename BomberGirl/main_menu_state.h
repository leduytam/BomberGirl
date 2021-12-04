#pragma once

#include "base_state.h"
#include"Button.h"
#include<vector>

namespace Bombergirl
{
	class MainMenuState : public BaseState
	{
	private:
		sf::Text m_mainMenuText;
		sf::Sprite m_backgroundSprite;
		sf::Sprite m_containerBoard;
		sf::Sprite m_arrow;
		const int START_POSITION_OPTION = 300;
		const int SPACE_BETWEEN_OPTION = 150;
		std::vector <Button> options_Button;
		int m_option;
	public:

		enum class OPTION {
			NEWGAME,
			ABOUT,
			LOAD,
			SAVE,
			MAX,
		};
		OPTION mainOption;
		MainMenuState(SharedContext* sharedContext);


		void init() override;
		void handleInput() override;
		void update(const float&) override;
		void render() override;

		Button createOption();
		void drawMenuOption();
		void selectOption(int option);
	};
}

