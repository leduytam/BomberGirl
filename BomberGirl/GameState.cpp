#include "GameState.h"
#include "configs.h"
#include <iostream>

Bombergirl::GameState::GameState(SharedContext* sharedContext, const sf::String& character_1, const sf::String& character_2) : BaseState(sharedContext)
{
	m_sharedContext->m_resources->loadTexture("shadow1", PLAYER_SHADOW_PATH);
	m_sharedContext->m_resources->loadTexture("shadow2", PLAYER_SHADOW_PATH);
	m_player1 = new Player(&m_sharedContext->m_resources->getTexture(character_1), &m_sharedContext->m_resources->getTexture("shadow1"), false);
	m_player2 = new Player(&m_sharedContext->m_resources->getTexture(character_2), &m_sharedContext->m_resources->getTexture("shadow2"), true);
	m_arena = sf::IntRect{ 0, 0, WORLD_WIDTH, WORLD_HEIGHT };

	m_mapView.reset(sf::FloatRect(0, 0, 1920, 1080));
	m_mapView.setCenter(WORLD_WIDTH / 2.f, WORLD_HEIGHT / 2.f);
	m_mapView.zoom(0.7f);

	m_mainView.reset(sf::FloatRect(0, 0, 1920, 1080));
	
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

	for (auto& bomb : m_bombs) {
		delete bomb;
	}
}

void Bombergirl::GameState::createMap() {
	int world_widthTiles = m_arena.width / TILE_SIZE;
	int world_heightTiles = m_arena.height / TILE_SIZE;

	m_map.assign(world_heightTiles, std::vector<Cell*>(world_widthTiles));

	for (int h = 0; h < world_heightTiles; h++) {
		for (int w = 0; w < world_widthTiles; w++) {
			if (h == 0 || w == 0 || h == world_heightTiles - 1 || w == world_widthTiles - 1) {
				m_map[h][w] = new Cell(Cell::Type::Border, sf::Vector2f{ 1.f * w * TILE_SIZE, 1.f * h * TILE_SIZE });
			}
			else if (h % 2 == 0 && w % 2 == 0) {
				m_map[h][w] = new Cell(Cell::Type::Obstacle, sf::Vector2f{ 1.f * w * TILE_SIZE, 1.f * h * TILE_SIZE });
			}
			else if ((rand() % 10 + 1) / 10.f <= CREATE_RATIO &&
				!(h == 1 && w == 1) &&
				!(h == 1 && w == 2) &&
				!(h == 2 && w == 1) &&
				!(h == world_heightTiles - 2 && w == world_widthTiles - 2) &&
				!(h == world_heightTiles - 2 && w == world_widthTiles - 3) &&
				!(h == world_heightTiles - 3 && w == world_widthTiles - 2)
				)
			{
				m_map[h][w] = new Cell(Cell::Type::Crate, sf::Vector2f{ 1.f * w * TILE_SIZE, 1.f * h * TILE_SIZE });
			}
			else {
				m_map[h][w] = new Cell(Cell::Type::None, sf::Vector2f{ 1.f * w * TILE_SIZE, 1.f * h * TILE_SIZE });
			}
		}
	}
}

void Bombergirl::GameState::init()
{
	m_sharedContext->m_resources->loadTexture("map_background", MAP_BACKGROUND_TEXTURE_PATH);
	m_sharedContext->m_resources->loadTexture("bomb", BOMB_TEXTURE_PATH);
	m_sharedContext->m_resources->loadTexture("crate", CRATE_PATH);
	m_sharedContext->m_resources->loadTexture("background_gamestate", GAMESTATE_BACKGROUND_PATH);
	createMap();

	m_player1->setArena(m_arena);
	m_player2->setArena(m_arena);

	m_player1->setPosition(sf::Vector2f{ (float)m_arena.left + TILE_SIZE * 1.5f, (float)m_arena.top + TILE_SIZE * 1.5f });
	m_player1->setSpeed(PLAYER_DEFAULT_SPEED);
	m_player2->setPosition(sf::Vector2f{ (float)m_arena.width - TILE_SIZE * 1.5f, (float)m_arena.height - TILE_SIZE * 1.5f });
	m_player2->setSpeed(PLAYER_DEFAULT_SPEED);

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
		m_player2->moveUp();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		m_player2->moveDown();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		m_player2->moveLeft();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		m_player2->moveRight();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
		m_player2->setIsDead();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		m_player1->moveUp();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		m_player1->moveDown();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		m_player1->moveLeft();
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		m_player1->moveRight();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
		sf::Vector2i index = { static_cast<int>((m_player2->getCenter().y / TILE_SIZE)), static_cast<int>((m_player2->getCenter().x / TILE_SIZE)) };
		if (index.x >= 0 && index.x < (float)m_map.size() && index.y >= 0 && index.y < (float)m_map.front().size() && m_map[index.x][index.y]->getType() != Cell::Type::Bomb) {
			m_map[index.x][index.y]->setType(Cell::Type::Bomb);
			m_bombs.push_back(new Bomb(&m_sharedContext->m_resources->getTexture("bomb"), index));
			std::cout << m_bombs.size() << std::endl;
		}
	}
}

void Bombergirl::GameState::update(const float& dt)
{
	for (unsigned int i = 0; i < m_bombs.size(); i++) {
		m_bombs[i]->update(dt, m_map);

		if (m_bombs[i]->isDone()) {
			m_map[m_bombs[i]->getIndex().x][m_bombs[i]->getIndex().y]->setType(Cell::Type::None);
			delete m_bombs[i];
			m_bombs.erase(m_bombs.begin() + i);
			--i;
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

	sf::Sprite crate;
	crate.setTexture(m_sharedContext->m_resources->getTexture("crate"));
	for (unsigned int i = 0; i < m_map.size(); i++) {
		for (unsigned int j = 0; j < m_map[i].size(); j++) {
			if (m_map[i][j]->getType() == Cell::Type::Crate) {
				crate.setPosition(sf::Vector2f(m_map[i][j]->getBound().left, m_map[i][j]->getBound().top));
				m_sharedContext->m_window->draw(crate);
			}
		}
	}

	for (auto& bomb : m_bombs) {
		bomb->draw(*m_sharedContext->m_window);
	}

	m_player1->render(*m_sharedContext->m_window);
	m_player2->render(*m_sharedContext->m_window);
}
