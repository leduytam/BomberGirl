#include "game_state.h"
#include "configs.h"
#include "barrel_cell.h"
#include "empty_cell.h"
#include "indestructible_cell.h"
#include "paused_state.h"
#include "bomb_cell.h"
#include <sstream>
#include <string>

Bombergirl::GameState::GameState(SharedContext* sharedContext) : BaseState(sharedContext), m_player1(nullptr), m_player2(nullptr)
{
	m_arena = sf::IntRect{ 0, 0, WORLD_WIDTH, WORLD_HEIGHT };

	m_mapView.reset(sf::FloatRect(0, 0, 1920, 1080));
	m_mapView.setCenter(WORLD_WIDTH / 2.f, WORLD_HEIGHT / 2.f);
	m_mapView.zoom(0.8f);

	m_mainView.reset(sf::FloatRect(0, 0, 1920, 1080));


	m_backSound = new sf::Sound();
	m_backSound->setBuffer(m_sharedContext->m_resources->getBuffer("game_back_sound"));
	m_backSound->setLoop(true);
	m_backSound->play();
	m_backSound->setVolume(50.f);

	m_tickSound = new sf::Sound();
	m_tickSound->setBuffer(m_sharedContext->m_resources->getBuffer("tick_sound"));
	m_tickSound->setVolume(100.f);

	m_winSound = new sf::Sound();
	m_winSound->setBuffer(m_sharedContext->m_resources->getBuffer("win_sound"));

	m_readySound = new sf::Sound();
	m_readySound->setBuffer(m_sharedContext->m_resources->getBuffer("ready_sound"));

	m_startSound = new sf::Sound();
	m_startSound->setBuffer(m_sharedContext->m_resources->getBuffer("start_sound"));

	m_drawSound = new sf::Sound();
	m_drawSound->setBuffer(m_sharedContext->m_resources->getBuffer("draw_sound"));

	m_coundDownTimerText.setFont(m_sharedContext->m_resources->getFont("arista_font"));
	m_coundDownTimerText.setCharacterSize(55);
	m_countDown = TIME_PER_ROUND;

	m_gameTime = 0.f;
	m_timerIcon.setTexture(m_sharedContext->m_resources->getTexture("timer_icon"));
	m_timerIcon.setPosition((float)1920 / 2.0 - 100, 30.f);

	m_pointPlayer1 = m_pointPlayer2 = 0;
	m_isGameOver = false;
	m_delayTimeGameOver = 0.f;

	m_resultRect.setSize({ DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT });
	m_resultRect.setFillColor(sf::Color{ 0,0,0,175 });

	m_pointText1.setFont(m_sharedContext->m_resources->getFont("arista_font"));
	m_pointText1.setCharacterSize(300);
	m_pointText1.setString("0");
	m_pointText1.setPosition({ 150.f, 300.f });
	m_pointText1.setFillColor(sf::Color{ 82, 121, 255 });

	m_pointText2.setFont(m_sharedContext->m_resources->getFont("arista_font"));
	m_pointText2.setCharacterSize(300);
	m_pointText2.setString("0");
	m_pointText2.setPosition({ 1920 - 170.f - m_pointText2.getLocalBounds().width, 300.f });
	m_pointText2.setFillColor(sf::Color{ 255, 112, 93 });

	m_countDownPreGame.setFont(m_sharedContext->m_resources->getFont("arista_font"));
	m_countDownPreGame.setCharacterSize(400);

	m_preGameText.setFont(m_sharedContext->m_resources->getFont("arista_font"));
	m_preGameText.setCharacterSize(300);
	m_isPreGame = false;
	m_preGameTime = 0.f;
	m_currentRound = 0;

	m_winBoard.setTexture(m_sharedContext->m_resources->getTexture("character_background"));
}

Bombergirl::GameState::~GameState()
{
	m_sharedContext->m_resources->unloadTexture("player_face_1");
	m_sharedContext->m_resources->unloadTexture("player_face_2");
	m_sharedContext->m_resources->unloadTexture("player_movement_1");
	m_sharedContext->m_resources->unloadTexture("player_movement_2");
	delete m_player1;
	delete m_player2;
	for (auto& row : m_map) {
		for (auto& cell : row) {
			delete cell;
		}
	}
	delete m_backSound;
	delete m_tickSound;
}

void Bombergirl::GameState::createMap() {
	int world_widthTiles = m_arena.width / TILE_SIZE;
	int world_heightTiles = m_arena.height / TILE_SIZE;

	m_map.assign(world_heightTiles, std::vector<Cell*>(world_widthTiles));

	for (int h = 0; h < world_heightTiles; h++) {
		for (int w = 0; w < world_widthTiles; w++) {
			sf::Vector2i index(h, w);
			if (h == 0 || w == 0 || h == world_heightTiles - 1 || w == world_widthTiles - 1 || h % 2 == 0 && w % 2 == 0) {
				m_map[h][w] = new IndestructibleCell(index, m_sharedContext);
			}
			else if ((rand() % 10 + 1) / 10.f <= BARREL_OCCURRENCE_RATE &&
				!(h == 1 && w == 1) &&
				!(h == 1 && w == 2) &&
				!(h == 2 && w == 1) &&
				!(h == world_heightTiles - 2 && w == world_widthTiles - 2) &&
				!(h == world_heightTiles - 2 && w == world_widthTiles - 3) &&
				!(h == world_heightTiles - 3 && w == world_widthTiles - 2)
				)
			{
				m_map[h][w] = new BarrelCell(index, m_sharedContext);
			}
			else {
				m_map[h][w] = new EmptyCell(index, m_sharedContext);
			}
		}
	}
}

void Bombergirl::GameState::resetRound()
{
	delete m_player1;
	delete m_player2;
	for (auto& row : m_map) {
		for (auto& cell : row) {
			delete cell;
		}
	}
	init();
}

void Bombergirl::GameState::setResult(bool isWin, bool isPlayer1)
{
	m_isGameOver = true;
	m_backSound->pause();
	if (isWin) {
		m_winSound->play();
		if (isPlayer1) {
			m_winner.setTexture(m_sharedContext->m_resources->getTexture("player_face_1"));
		}
		else {
			m_winner.setTexture(m_sharedContext->m_resources->getTexture("player_face_2"));
		}
		m_preGameText.setString("CONGRATULATIONS!");
		float scale = 2.f;
		m_winner.setPosition({ (DEFAULT_WINDOW_WIDTH - m_winner.getLocalBounds().width * 2) / 2.f, (DEFAULT_WINDOW_HEIGHT - m_winner.getLocalBounds().height * scale) / 2.f - 200.f });
		m_winBoard.setPosition({m_winner.getPosition().x + m_winner.getLocalBounds().width * scale / 2.f - m_winBoard.getLocalBounds().width / 2.f, m_winner.getPosition().y + m_winner.getLocalBounds().height * scale / 2.f - m_winBoard.getLocalBounds().height / 2.f });
		m_winner.scale({ scale, scale });
		m_preGameText.setCharacterSize(200);
		m_preGameText.setPosition({ (DEFAULT_WINDOW_WIDTH - m_preGameText.getLocalBounds().width) / 2.f, (DEFAULT_WINDOW_HEIGHT - m_preGameText.getLocalBounds().height) / 2.f });
	}
	else {
		m_winBoard.setPosition({-1000, -1000});

		m_drawSound->play();
		m_preGameText.setString("DRAW");
		m_preGameText.setPosition({ (DEFAULT_WINDOW_WIDTH - m_preGameText.getLocalBounds().width) / 2.f, (DEFAULT_WINDOW_HEIGHT - m_preGameText.getLocalBounds().height * 2) / 2.f });
	}
}

void Bombergirl::GameState::init()
{
	createMap();
	m_isPreGame = true;
	m_currentRound++;
	if (m_currentRound > NUMBER_ROUNDS) {
		if (m_pointPlayer1 == m_pointPlayer2) {
			setResult(false);
		}
		else {
			if (m_pointPlayer1 > m_pointPlayer2) {
				setResult(true, true);
			}
			else {
				setResult(true, false);
			}
		}
	}
	m_preGameTime = 0.f;
	m_player1 = new Player(m_sharedContext, &m_sharedContext->m_resources->getTexture("player_movement_1"), Player::PlayerDirection::Down);
	m_player2 = new Player(m_sharedContext, &m_sharedContext->m_resources->getTexture("player_movement_2"), Player::PlayerDirection::Up);

	m_player1->setPosition(sf::Vector2f{ (float)m_arena.left + TILE_SIZE * 1.5f, (float)m_arena.top + TILE_SIZE * 1.5f });
	m_player2->setPosition(sf::Vector2f{ (float)m_arena.width - TILE_SIZE * 1.5f, (float)m_arena.height - TILE_SIZE * 1.5f });

	m_mapBackgroundSprite.setTexture(m_sharedContext->m_resources->getTexture("map_background"));
	m_backgroundSprite.setTexture(m_sharedContext->m_resources->getTexture("background_gamestate"));
	m_coundDownTimerText.setFillColor(sf::Color{ 54, 170, 43 });
	m_countDown = TIME_PER_ROUND;
	m_coundDownTimerText.setString(std::to_string((int)TIME_PER_ROUND));
	m_coundDownTimerText.setPosition((1920 - m_coundDownTimerText.getLocalBounds().width) / 2.f, 10);
}

void Bombergirl::GameState::handleInput()
{
	sf::Event e;
	while (m_sharedContext->m_window->pollEvent(e))
	{
		if (e.type == sf::Event::Closed) {
			m_sharedContext->m_window->close();
		}
		else  if (e.type == sf::Event::KeyPressed) {

			if (e.key.code == sf::Keyboard::Escape) {
				m_sharedContext->m_window->close();
			}

			else if (e.key.code == sf::Keyboard::Enter && !m_isGameOver) {
				m_sharedContext->m_stateManager->push(new PausedState(m_sharedContext, m_backSound));
			}
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		m_player2->setDirection(Player::PlayerDirection::Up);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		m_player2->setDirection(Player::PlayerDirection::Down);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		m_player2->setDirection(Player::PlayerDirection::Left);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		m_player2->setDirection(Player::PlayerDirection::Right);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		m_player1->setDirection(Player::PlayerDirection::Up);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		m_player1->setDirection(Player::PlayerDirection::Down);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		m_player1->setDirection(Player::PlayerDirection::Left);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		m_player1->setDirection(Player::PlayerDirection::Right);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::G)) {
		m_player1->setUpBomb();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
		m_player2->setUpBomb();
	}
}

void Bombergirl::GameState::update(const float& dt)
{
	if (m_isGameOver) {
		if (m_delayTimeGameOver >= 3.f) {
			m_sharedContext->m_stateManager->pop();
		}
		else {
			m_delayTimeGameOver += dt;
			return;
		}
	}
	if (m_preGameTime >= TIME_PREGAME) {
		m_isPreGame = false;
	}
	else {
		m_preGameTime += dt;
		int countDown = (int)TIME_PREGAME - (int)m_preGameTime;
		if (countDown == 3 && m_readySound->getStatus() != sf::Sound::Playing && !m_isGameOver) {
			m_preGameText.setString("Ready");
			m_readySound->play();
		}
		if (countDown == 2 && m_startSound->getStatus() != sf::Sound::Playing && m_readySound->getStatus() != sf::Sound::Playing && !m_isGameOver) {
			m_preGameText.setString("Go!");
			m_startSound->play();
		}
		m_preGameText.setPosition({ (DEFAULT_WINDOW_WIDTH - m_preGameText.getLocalBounds().width) / 2.f, (DEFAULT_WINDOW_HEIGHT - 500 * 2) / 2.f });
		if (countDown != TIME_PREGAME) {
			m_countDownPreGame.setString(std::to_string(countDown));
		}
		else {
			m_preGameText.setString("ROUND " + std::to_string(m_currentRound));
			m_countDownPreGame.setString(std::to_string(m_pointPlayer1) + " - " + std::to_string(m_pointPlayer2)) ;
		}
		m_countDownPreGame.setPosition({ (DEFAULT_WINDOW_WIDTH - m_countDownPreGame.getLocalBounds().width) / 2.f, (DEFAULT_WINDOW_HEIGHT - m_coundDownTimerText.getLocalBounds().height * 10) / 2.f });
	}

	if (!m_isPreGame) {
		for (auto& row : m_map) {
			for (auto& cell : row) {
				cell->update(dt, m_map);
			}
		}

		if (!m_isGameOver && m_gameTime > 1.f) {
			m_countDown--;
			if (m_countDown <= 10.f) {
				m_coundDownTimerText.setFillColor(sf::Color{ 252, 69, 43 });
				m_tickSound->play();
			}
			if (m_countDown <= 0.f) {
				resetRound();
				return;
			}
			std::stringstream ssCountDown;
			ssCountDown << m_countDown;
			m_coundDownTimerText.setString(ssCountDown.str());
			m_coundDownTimerText.setPosition((1920 - m_coundDownTimerText.getLocalBounds().width) / 2.f, 10);
			m_gameTime = 0.f;
		}
		else {
			m_gameTime += dt;
		}

		bool isPlayer1OnDead = m_player1->isOnDead();
		bool isPlayer2OnDead = m_player2->isOnDead();

		if (!isPlayer2OnDead) {
			m_player1->update(dt, m_map);
		}

		if (!isPlayer1OnDead) {
			m_player2->update(dt, m_map);
		}

		if (isPlayer1OnDead && isPlayer2OnDead) {
			m_player1->update(dt, m_map);
			m_player2->update(dt, m_map);
		}

		if (m_player1->isDead() || m_player2->isDead()) {
			if (m_player1->isDead()) {
				m_pointPlayer2++;
				m_pointText2.setString(std::to_string(m_pointPlayer2));
			}
			if (m_player2->isDead()) {
				m_pointPlayer1++;
				m_pointText1.setString(std::to_string(m_pointPlayer1));
			}
			resetRound();
		}

		if (!m_isGameOver && (m_pointPlayer1 >= 2 || m_pointPlayer2 >= 2)) {
			if (m_pointPlayer1 >= 2) setResult(true, true);
			else if (m_pointPlayer2 >= 2) setResult(true, false);
		}
	}
}

void Bombergirl::GameState::render()
{
	// HUD view
	m_sharedContext->m_window->setView(m_mainView);
	m_sharedContext->m_window->draw(m_backgroundSprite);
	m_sharedContext->m_window->draw(m_timerIcon);
	m_sharedContext->m_window->draw(m_coundDownTimerText);
	m_sharedContext->m_window->draw(m_pointText1);
	m_sharedContext->m_window->draw(m_pointText2);

	// map view
	m_sharedContext->m_window->setView(m_mapView);
	m_sharedContext->m_window->draw(m_mapBackgroundSprite);

	if (!m_isGameOver) {
		for (const auto& row : m_map) {
			for (const auto& cell : row) {
				cell->render(*m_sharedContext->m_window);
			}
		}

		m_player1->render(*m_sharedContext->m_window);
		m_player2->render(*m_sharedContext->m_window);
	}
	

	// mainview
	m_sharedContext->m_window->setView(m_mainView);
	if (m_isGameOver) {
		m_sharedContext->m_window->draw(m_resultRect);
		m_sharedContext->m_window->draw(m_winBoard);
		m_sharedContext->m_window->draw(m_winner);
		m_sharedContext->m_window->draw(m_preGameText);
	}

	if (m_isPreGame && !m_isGameOver) {
		m_sharedContext->m_window->draw(m_resultRect);
		m_sharedContext->m_window->draw(m_countDownPreGame);
		m_sharedContext->m_window->draw(m_preGameText);
	}
}
