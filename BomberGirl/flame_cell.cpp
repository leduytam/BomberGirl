#include "flame_cell.h"
#include "empty_cell.h"
#include "configs.h"

Bombergirl::FlameCell::FlameCell(const sf::Vector2i& index, SharedContext* sharedContext, const FlameDirection& flameDirection) : Cell(index, sharedContext), m_elapsedTime(0.f)
{
	m_flameSprite.setTexture(m_sharedContext->m_resources->getTexture("flame"));
	m_flameSprite.setPosition(getPosision());

	m_flameAnimation.setSprite(&m_flameSprite);
	m_flameAnimation.setFrameDuration(0.1f);

	for (int i = 0; i < 3; i++) {
		m_flameAnimation.addFrame({ i * TILE_SIZE, static_cast<int>(flameDirection) * TILE_SIZE, TILE_SIZE, TILE_SIZE });
	}
}

Bombergirl::Cell::CellType Bombergirl::FlameCell::getType() const
{
	return CellType::Flame;
}

bool Bombergirl::FlameCell::isObstacle() const
{
	return false;
}

void Bombergirl::FlameCell::update(const float& dt, std::vector<std::vector<Cell*>>& map)
{
	m_flameAnimation.update(dt);
	m_elapsedTime += dt;

	if (m_elapsedTime >= FLAME_EXISTING_TIME) {
		map[getIndex().x][getIndex().y] = new EmptyCell(getIndex(), m_sharedContext);
		delete this;
	}
}

void Bombergirl::FlameCell::render(sf::RenderWindow& window) const
{
	window.draw(m_flameSprite);
}
