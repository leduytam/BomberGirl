#include "item_cell.h"
#include "empty_cell.h"
#include "configs.h"

Bombergirl::ItemCell::ItemCell(const sf::Vector2i& index, SharedContext* sharedContext, const ItemType& itemType)
	: Cell(index, sharedContext), m_elapsedTime(0.f), m_isOnExplosion(false), m_itemType(itemType)
{
	m_itemSprite.setTexture(m_sharedContext->m_resources->getTexture("items"));
	m_itemSprite.setPosition(getPosision());

	m_itemSprite.setTextureRect(sf::IntRect(static_cast<int>(itemType) * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE));

	m_explosionSprite.setTexture(m_sharedContext->m_resources->getTexture("explosion"));
	m_explosionSprite.setPosition(getPosision());
	m_explosionAnimation.setSprite(&m_explosionSprite);
	m_explosionAnimation.setFrameDuration(0.1f);
	m_explosionAnimation.setRepeat(false);

	for (int i = 0; i < 3; i++) {
		m_explosionAnimation.addFrame({ i * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE });
	}
}

void Bombergirl::ItemCell::update(const float& dt, std::vector<std::vector<Cell*>>& map)
{
	if (!m_isOnExplosion) {
		m_elapsedTime += dt;

		if (m_elapsedTime >= ITEM_EXISTING_TIME) {
			setOnExplosion();
		}
	}
	else {
		m_explosionAnimation.update(dt);

		if (m_explosionAnimation.isDone()) {
			map[getIndex().x][getIndex().y] = new EmptyCell(getIndex(), m_sharedContext);
			delete this;
		}
	}
}

void Bombergirl::ItemCell::render(sf::RenderWindow& window) const
{
	window.draw(m_itemSprite);

	if (m_isOnExplosion) {
		window.draw(m_explosionSprite);
	}
}

void Bombergirl::ItemCell::setOnExplosion()
{
	m_isOnExplosion = true;
}

bool Bombergirl::ItemCell::isOnExplosion() const
{
	return m_isOnExplosion;
}

Bombergirl::ItemCell::ItemType Bombergirl::ItemCell::getItemType() const
{
	return m_itemType;
}

Bombergirl::Cell::CellType Bombergirl::ItemCell::getType() const
{
	return CellType::Item;
}

bool Bombergirl::ItemCell::isObstacle() const
{
	return false;
}
