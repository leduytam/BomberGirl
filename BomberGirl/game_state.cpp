#include "game_state.h"
#include "configs.h"
#include "barrel_cell.h"
#include "empty_cell.h"
#include "indestructible_cell.h"
#include "bomb_cell.h"
#include <sstream>
#include <string>
#include <iostream>

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

	m_coundDownTimerText.setFont(m_sharedContext->m_resources->getFont("garamond"));
	m_coundDownTimerText.setCharacterSize(55);
	m_countDown = TIME_PER_ROUND;

	m_gameTime = 0.f;
	m_timerIcon.setTexture(m_sharedContext->m_resources->getTexture("timer_icon"));
	m_timerIcon.setPosition((float)1920 / 2.0 - 80, 23.f);

	m_pointPlayer1 = m_pointPlayer2 = 0;
	m_isGameOver = false;
	m_delayTimeGameOver = 0;

	m_resultRect.setSize({ DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT });
	m_resultRect.setFillColor(sf::Color{ 0,0,0,175 });

	m_decorFrame_l.setFillColor(sf::Color{ 218, 202, 10 });
	m_decorFrame_t.setFillColor(sf::Color{ 218, 202, 10 });
	m_decorFrame_r.setFillColor(sf::Color{ 218, 202, 10 });
	m_decorFrame_b.setFillColor(sf::Color{ 218, 202, 10 });

	m_decorFrame_b.setSize({ 308.f, 10.f });

	m_decorFrame_r.setSize({ 10.f, 308.f });

	m_decorFrame_t.setSize({ 308.f, 10.f });

	m_decorFrame_l.setSize({ 10.f, 308.f });
}

Bombergirl::GameState::~GameState()
{
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

void Bombergirl::GameState::init()
{
	createMap();

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
		else if (e.key.code == sf::Keyboard::Escape) {
			m_sharedContext->m_window->close();
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
		m_player1->setUpBomb();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
		m_player2->setUpBomb();
	}
}

void Bombergirl::GameState::update(const float& dt)
{
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
			delete m_player1;
			delete m_player2;
			for (auto& row : m_map) {
				for (auto& cell : row) {
					delete cell;
				}
			}
			init();
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
	// on dead = dang chet != dead = da chet
	// can de xet truong hop ca 2 chet cung luc
	// neu goi truc tiep trong if thi player2 luon thang neu nhu ca 2 chet cung luc

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
		}
		if (m_player2->isDead()) {
			m_pointPlayer1++;
		}
		delete m_player1;
		delete m_player2;
		for (auto& row : m_map) {
			for (auto& cell : row) {
				delete cell;
			}
		}
		init();
	}

	if (!m_isGameOver && (m_pointPlayer1 >= 2 || m_pointPlayer2 >= 2)) {
		m_isGameOver = true;
		m_backSound->pause();
		m_winSound->play();
		if (m_pointPlayer1 >= 2) {
			m_winner.setTexture(m_sharedContext->m_resources->getTexture("player_face_1"));
		}
		if (m_pointPlayer2 >= 2) {
			m_winner.setTexture(m_sharedContext->m_resources->getTexture("player_face_2"));
		}
		float scale = 2.f;
		m_winner.setPosition({ (DEFAULT_WINDOW_WIDTH - m_winner.getLocalBounds().width * scale) / 2.f, (DEFAULT_WINDOW_HEIGHT - m_winner.getLocalBounds().height * scale) / 2.f - 200.f });
		m_winner.scale({ scale, scale });
	}

	if (m_isGameOver) {
		if (m_delayTimeGameOver >= 3.f) {
			m_sharedContext->m_stateManager->pop();
		}
		else {
			m_delayTimeGameOver += dt;
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

	// map view
	m_sharedContext->m_window->setView(m_mapView);
	m_sharedContext->m_window->draw(m_mapBackgroundSprite);

	for (const auto& row : m_map) {
		for (const auto& cell : row) {
			cell->render(*m_sharedContext->m_window);
		}
	}

	m_player1->render(*m_sharedContext->m_window);
	m_player2->render(*m_sharedContext->m_window);
	m_sharedContext->m_window->setView(m_mainView);
	if (m_isGameOver) {
		m_sharedContext->m_window->draw(m_resultRect);
		m_sharedContext->m_window->draw(m_winner);
		if (m_delayTimeGameOver >= 1.5f) {
			m_decorFrame_b.setPosition({ m_winner.getPosition().x - 10.f, m_winner.getPosition().y + 289.f });
			m_sharedContext->m_window->draw(m_decorFrame_b);

		}
		if (m_delayTimeGameOver >= 1.f) {
			m_decorFrame_r.setPosition({ m_winner.getPosition().x + 289.f, m_winner.getPosition().y - 10 });
			m_sharedContext->m_window->draw(m_decorFrame_r);

		}
		if (m_delayTimeGameOver >= 0.5f) {
			m_decorFrame_t.setPosition({ m_winner.getPosition().x - 10, m_winner.getPosition().y - 10 });
			m_sharedContext->m_window->draw(m_decorFrame_t);

		}
		if (m_delayTimeGameOver >= 0.f) {
			m_decorFrame_l.setPosition({ m_winner.getPosition().x - 10, m_winner.getPosition().y - 10 });
			m_sharedContext->m_window->draw(m_decorFrame_l);
		}
	}
}
