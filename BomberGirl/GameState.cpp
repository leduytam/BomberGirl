#include "GameState.h"
#include "configs.h"

Bombergirl::GameState::GameState(SharedContext* sharedContext, const sf::String& character_1, const sf::String& character_2) : BaseState(sharedContext)
{
	m_sharedContext->m_resources->loadTexture("shadow1", PLAYER_SHADOW_PATH);
	m_sharedContext->m_resources->loadTexture("shadow2", PLAYER_SHADOW_PATH);
	m_player1 = new Player(&m_sharedContext->m_resources->getTexture(character_1), &m_sharedContext->m_resources->getTexture("shadow1"), true);
	m_player2 = new Player(&m_sharedContext->m_resources->getTexture(character_2), &m_sharedContext->m_resources->getTexture("shadow2"), false);
	m_arena = sf::IntRect{ 0,0,WORLD_WIDTH, WORLD_HEIGHT };
	
	
}

Bombergirl::GameState::~GameState()
{
	delete m_player1;
	delete m_player2;
}

void Bombergirl::GameState::loadResources() {
	m_sharedContext->m_resources->loadTexture("background_tileset", BACKGROUND_TILESETS_PATH, sf::IntRect(48 * 7, 48 * 5, 48, 48 * 4));
}

void Bombergirl::GameState::createMap() {
	int world_widthTiles = m_arena.width / TILE_SIZE;
	int world_heightTiles = m_arena.height / TILE_SIZE;
	for (int h = 0; h < world_heightTiles; h++) {
		std::vector<Cell*> rowCell;
		for (int w = 0; w < world_widthTiles; w++) {
			if (h == 0 || w == 0 || h == world_heightTiles - 1 || w == world_widthTiles - 1) {
				rowCell.push_back(new Cell());
			}
			else if (h % 2 ==0 && w % 2 == 0) {
				rowCell.push_back(new Cell(1));
			}
			else {/*
				srand((int)time(0) + h * w - h);
				int r = rand() % 2 + 2;*/
				rowCell.push_back(new Cell(3));
			}
		}
		m_map.push_back(rowCell);
	}
}

void Bombergirl::GameState::createBackground()
{
	int world_widthTiles = m_arena.width / TILE_SIZE;
	int world_heightTiles = m_arena.height / TILE_SIZE;
	m_backgroundVA.setPrimitiveType(sf::Quads);
	m_backgroundVA.resize(world_heightTiles * world_widthTiles * VERTEX_IN_QUAD);
	int currentVertex = 0;

	for (int w = 0; w < world_widthTiles; w++) {
		for (int h = 0; h < world_heightTiles; h++) {
			m_backgroundVA[currentVertex].position = sf::Vector2f(w * TILE_SIZE, h * TILE_SIZE);
			m_backgroundVA[currentVertex + 1].position = sf::Vector2f((w * TILE_SIZE) + TILE_SIZE, h * TILE_SIZE);
			m_backgroundVA[currentVertex + 2].position = sf::Vector2f((w * TILE_SIZE) + TILE_SIZE, (h * TILE_SIZE) + TILE_SIZE);
			m_backgroundVA[currentVertex + 3].position = sf::Vector2f(w * TILE_SIZE, (h * TILE_SIZE) + TILE_SIZE);

				m_backgroundVA[currentVertex].texCoords = sf::Vector2f(0, TILE_SIZE * m_map[h][w]->getType());
				m_backgroundVA[currentVertex + 1].texCoords = sf::Vector2f(TILE_SIZE, TILE_SIZE * m_map[h][w]->getType());
				m_backgroundVA[currentVertex + 2].texCoords = sf::Vector2f(TILE_SIZE, TILE_SIZE + TILE_SIZE * m_map[h][w]->getType());
				m_backgroundVA[currentVertex + 3].texCoords = sf::Vector2f(0, TILE_SIZE + TILE_SIZE * m_map[h][w]->getType());
			
			currentVertex += VERTEX_IN_QUAD;
		}
	}
}


void Bombergirl::GameState::init()
{
	loadResources();
	auto windowSize = m_sharedContext->m_window->getSize();
	m_background.setFillColor(sf::Color::White);
	m_background.setSize({ (float)windowSize.x, (float)windowSize.y });

	m_backgroundTexture = m_sharedContext->m_resources->getTexture("background_tileset");
	createMap();
	createBackground();

	m_player1->setArena(m_arena);
	m_player2->setArena(m_arena);

	m_player1->setPosition(sf::Vector2f{ (float)m_arena.left + TILE_SIZE * 1.5f, (float)m_arena.top + TILE_SIZE * 1.5f });
	m_player2->setPosition(sf::Vector2f{ (float)m_arena.width - TILE_SIZE * 1.5f, (float)m_arena.height - TILE_SIZE * 1.5f });
}

void Bombergirl::GameState::handleInput()
{
	sf::Event e;
	while (m_sharedContext->m_window->pollEvent(e))
	{
		if (e.type == sf::Event::Closed)
			m_sharedContext->m_window->close();
		if (e.key.code == sf::Keyboard::Escape) {
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
}

void Bombergirl::GameState::update(const float& dt)
{
	m_player1->update(dt);
	m_player2->update(dt);
}

void Bombergirl::GameState::render()
{
	m_sharedContext->m_window->draw(m_backgroundVA, &m_backgroundTexture);
	m_player1->render(*m_sharedContext->m_window);
	m_player2->render(*m_sharedContext->m_window);
	sf::Sprite demo;/*
	demo.setTexture(m_sharedContext->m_resources->getTexture("background_tileset"));
	m_sharedContext->m_window->draw(demo);*/

}

