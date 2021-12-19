#include "bomb_cell.h"
#include "empty_cell.h"
#include "flame_cell.h"
#include "barrel_cell.h"
#include "item_cell.h"
#include "configs.h"
#include <algorithm>

Bombergirl::BombCell::BombCell(const sf::Vector2i& index, SharedContext* sharedContext, Player* player)
	: Cell(index, sharedContext), m_player(player), m_isExploded(false),
	m_elapsedTimeAfterExplosion(0.f), m_isOwnerPlayerStillInside(true),
	m_bombRange(player->m_bombRange)
{
	m_bombSprite.setTexture(sharedContext->m_resources->getTexture("bomb"));
	m_bombSprite.setPosition(getPosision());

	m_bombAnimation.setSprite(&m_bombSprite);
	m_bombAnimation.setFrameDuration(0.6f);
	m_bombAnimation.setRepeat(false);

	for (int i = 0; i < 3; i++) {
		m_bombAnimation.addFrame({ i * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE });
	}

	m_bombSetSound = new sf::Sound();
	m_bombSetSound->setBuffer(m_sharedContext->m_resources->getBuffer("bombset_sound"));
	m_bombSetSound->play();

	// m_bomb explosion here
}

Bombergirl::BombCell::~BombCell()
{
	delete m_bombSetSound;
	//delete m_bombExplosionSound;
}

Bombergirl::Cell::CellType Bombergirl::BombCell::getType() const
{
	return CellType::Bomb;
}

bool Bombergirl::BombCell::isObstacle() const
{
	return true;
}

void Bombergirl::BombCell::update(const float& dt, std::vector<std::vector<Cell*>>& map)
{
	m_bombAnimation.update(dt);

	if (m_isOwnerPlayerStillInside && !m_player->getBound().intersects(getBound())) {
		m_isOwnerPlayerStillInside = false;
	}

	if (m_isExploded) {
		m_elapsedTimeAfterExplosion += dt;
		if (m_elapsedTimeAfterExplosion >= FLAME_EXISTING_TIME) {
			map[getIndex().x][getIndex().y] = new EmptyCell(getIndex(), m_sharedContext);
			m_player->m_bombs++;
			delete this;
			return;
		}
	}

	if (m_bombAnimation.isDone() && !m_isExploded)
	{
		m_isExploded = true;

		m_bombSprite.setTextureRect(sf::IntRect(3 * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE));

		int up = 0, left = 0, right = 0, down = 0;

		auto isBlockedFlameCell = [](Cell* cell) {
			return cell->isObstacle() || cell->getType() == Cell::CellType::Flame || cell->getType() == Cell::CellType::Item;
		};

		int j = std::max(m_index.x - m_bombRange, 0);

		for (int i = m_index.x - 1; i >= j; i--) {
			if (isBlockedFlameCell(map[i][m_index.y])) {
				if (map[i][m_index.y]->getType() == Cell::CellType::Barrel) {
					dynamic_cast<BarrelCell*>(map[i][m_index.y])->setOnExplosion();
				}
				else if (map[i][m_index.y]->getType() == Cell::CellType::Item) {
					dynamic_cast<ItemCell*>(map[i][m_index.y])->setOnExplosion();
				}
				break;
			}
			else {
				delete map[i][m_index.y];
				map[i][m_index.y] = new FlameCell({ i, m_index.y }, m_sharedContext, FlameCell::FlameDirection::Up);
			}
			++up;
		}

		j = std::max(m_index.y - m_bombRange, 0);

		for (int i = m_index.y - 1; i >= j; i--) {
			if (isBlockedFlameCell(map[m_index.x][i])) {
				if (map[m_index.x][i]->getType() == Cell::CellType::Barrel) {
					dynamic_cast<BarrelCell*>(map[m_index.x][i])->setOnExplosion();
				}
				else if (map[i][m_index.y]->getType() == Cell::CellType::Item) {
					dynamic_cast<ItemCell*>(map[m_index.x][i])->setOnExplosion();
				}
				break;
			}
			else {
				delete map[m_index.x][i];
				map[m_index.x][i] = new FlameCell({ m_index.x, i }, m_sharedContext, FlameCell::FlameDirection::Left);
			}
			++left;
		}

		j = std::min(m_index.y + m_bombRange, static_cast<int>(map.front().size() - 1));

		for (int i = m_index.y + 1; i <= j; i++) {
			if (isBlockedFlameCell(map[m_index.x][i])) {
				if (map[m_index.x][i]->getType() == Cell::CellType::Barrel) {
					dynamic_cast<BarrelCell*>(map[m_index.x][i])->setOnExplosion();
				}
				else if (map[i][m_index.y]->getType() == Cell::CellType::Item) {
					dynamic_cast<ItemCell*>(map[m_index.x][i])->setOnExplosion();
				}
				break;
			}
			else {
				delete map[m_index.x][i];
				map[m_index.x][i] = new FlameCell({ m_index.x, i }, m_sharedContext, FlameCell::FlameDirection::Right);
			}
			++right;
		}

		j = std::min(m_index.x + m_bombRange, static_cast<int>(map.size() - 1));

		for (int i = m_index.x + 1; i <= j; i++) {
			if (isBlockedFlameCell(map[i][m_index.y])) {
				if (map[i][m_index.y]->getType() == Cell::CellType::Barrel) {
					dynamic_cast<BarrelCell*>(map[i][m_index.y])->setOnExplosion();
				}
				else if (map[i][m_index.y]->getType() == Cell::CellType::Item) {
					dynamic_cast<ItemCell*>(map[i][m_index.y])->setOnExplosion();
				}
				break;
			}
			else {
				delete map[i][m_index.y];
				map[i][m_index.y] = new FlameCell({ i, m_index.y }, m_sharedContext, FlameCell::FlameDirection::Down);
			}
			++down;
		}
	}
}

void Bombergirl::BombCell::render(sf::RenderWindow& window) const
{
	window.draw(m_bombSprite);
}

bool Bombergirl::BombCell::isOwnerPlayerStillInside() const
{
	return m_isOwnerPlayerStillInside;
}

bool Bombergirl::BombCell::isOnExplosion() const
{
	return m_isExploded;
}
