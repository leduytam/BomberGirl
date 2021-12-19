#include "game_state.h"
#include "configs.h"
#include "barrel_cell.h"
#include "empty_cell.h"
#include "indestructible_cell.h"
#include "bomb_cell.h"

Bombergirl::GameState::GameState(SharedContext* sharedContext) : BaseState(sharedContext), m_player1(nullptr), m_player2(nullptr)
{
	m_arena = sf::IntRect{ 0, 0, WORLD_WIDTH, WORLD_HEIGHT };

	m_mapView.reset(sf::FloatRect(0, 0, 1920, 1080));
	m_mapView.setCenter(WORLD_WIDTH / 2.f, WORLD_HEIGHT / 2.f);
	m_mapView.zoom(0.7f);

	m_mainView.reset(sf::FloatRect(0, 0, 1920, 1080));

	m_backSound = new sf::Sound();
	m_backSound->setBuffer(m_sharedContext->m_resources->getBuffer("game_back_sound"));
	m_backSound->play();
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

	m_player1->update(dt, m_map);
	m_player2->update(dt, m_map);
}

void Bombergirl::GameState::render()
{
	m_sharedContext->m_window->setView(m_mainView);
	m_sharedContext->m_window->draw(m_backgroundSprite);
	m_sharedContext->m_window->setView(m_mapView);
	m_sharedContext->m_window->draw(m_mapBackgroundSprite);

	for (const auto& row : m_map) {
		for (const auto& cell : row) {
			cell->render(*m_sharedContext->m_window);
		}
	}

	m_player1->render(*m_sharedContext->m_window);
	m_player2->render(*m_sharedContext->m_window);
}
