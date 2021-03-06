#pragma once

#include "base_state.h"
#include "player.h"
#include <vector>
#include "cell.h"

namespace Bombergirl
{
	class GameState : public BaseState
	{
	private:
		Player* m_player1, * m_player2;
		sf::IntRect m_arena;
		sf::RectangleShape m_resultRect;
		sf::View m_mapView;
		sf::View m_mainView;

		sf::Sprite m_mapBackgroundSprite;
		sf::Sprite m_backgroundSprite;
		sf::Sprite m_timerIcon;
		sf::Sprite m_winner;
		sf::Sprite m_winBoard;

		sf::Text m_coundDownTimerText;

		std::vector <std::vector<Cell*>> m_map;

		sf::Sound* m_backSound;
		sf::Sound* m_tickSound;
		sf::Sound* m_winSound;
		sf::Sound* m_readySound;
		sf::Sound* m_startSound;
		sf::Sound* m_drawSound;

		sf::Text m_pointText1;
		sf::Text m_pointText2;

		sf::Text m_countDownPreGame;
		sf::Text m_preGameText;
		bool m_isPreGame;
		float m_preGameTime;


		float m_gameTime;
		float m_countDown;
		const int NUMBER_ROUNDS = 3;
		int m_currentRound;
		int m_pointPlayer1;
		int m_pointPlayer2;
		bool m_isGameOver;
		float m_delayTimeGameOver;
		
	public:
		GameState(SharedContext* sharedContext);
		~GameState();
		void init() override;
		void handleInput() override;
		void update(const float&) override;
		void render() override;
		void createMap();
		void resetRound();
		void setResult(bool isWin, bool isPlayer1 = true);
	};
}
