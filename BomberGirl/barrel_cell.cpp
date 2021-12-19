#include "barrel_cell.h"
#include "empty_cell.h"
#include "item_cell.h"
#include "configs.h"

Bombergirl::BarrelCell::BarrelCell(const sf::Vector2i& index, SharedContext* sharedContext) : Cell(index, sharedContext), m_isOnExplosion(false)
{
	m_barrelSprite.setTexture(m_sharedContext->m_resources->getTexture("barrel"));
	m_barrelSprite.setTextureRect(sf::IntRect(0, 0, TILE_SIZE, TILE_SIZE));
	m_barrelSprite.setPosition(getPosision());

	m_explosionSprite.setTexture(m_sharedContext->m_resources->getTexture("explosion"));
	m_explosionSprite.setPosition(getPosision());
	m_explosionAnimation.setSprite(&m_explosionSprite);
	m_explosionAnimation.setFrameDuration(0.1f);
	m_explosionAnimation.setRepeat(false);

	for (int i = 0; i < 3; i++) {
		m_explosionAnimation.addFrame({ i * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE });
	}
}

void Bombergirl::BarrelCell::setOnExplosion()
{
	m_barrelSprite.setTextureRect(sf::IntRect(TILE_SIZE, 0, TILE_SIZE, TILE_SIZE));
	m_isOnExplosion = true;
}

Bombergirl::Cell::CellType Bombergirl::BarrelCell::getType() const
{
	return CellType::Barrel;
}

bool Bombergirl::BarrelCell::isObstacle() const
{
	return true;
}

void Bombergirl::BarrelCell::update(const float& dt, std::vector<std::vector<Cell*>>& map)
{
	if (m_isOnExplosion) {
		m_explosionAnimation.update(dt);

		if (m_explosionAnimation.isDone()) {
			if ((rand() % 10 + 1) / 10.f <= ITEM_OCCURRENCE_RATE) {
				map[getIndex().x][getIndex().y] = new ItemCell(getIndex(), m_sharedContext, static_cast<ItemCell::ItemType>(rand() % static_cast<int>(ItemCell::ItemType::Count)));
			}
			else {
				map[getIndex().x][getIndex().y] = new EmptyCell(getIndex(), m_sharedContext);
			}

			delete this;
		}
	}
}

void Bombergirl::BarrelCell::render(sf::RenderWindow& window) const
{
	window.draw(m_barrelSprite);

	if (m_isOnExplosion) {
		window.draw(m_explosionSprite);
	}
}
