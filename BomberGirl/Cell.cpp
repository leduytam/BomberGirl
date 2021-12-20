#include "cell.h"
#include "configs.h"

Bombergirl::Cell::Cell(const sf::Vector2i& index, SharedContext* sharedContext) : m_index(index), m_sharedContext(sharedContext)
{
	m_bound = sf::FloatRect(static_cast<float>(index.y * TILE_SIZE), static_cast<float>(index.x * TILE_SIZE), static_cast<float>(TILE_SIZE), static_cast<float>(TILE_SIZE));
}

Bombergirl::Cell::~Cell() {}

sf::FloatRect Bombergirl::Cell::getBound() const
{
	return m_bound;
}

sf::Vector2i Bombergirl::Cell::getIndex() const
{
	return m_index;
}

sf::Vector2f Bombergirl::Cell::getPosision() const
{
	return sf::Vector2f(m_bound.left, m_bound.top);
}

void Bombergirl::Cell::update(const float&, std::vector<std::vector<Cell*>>&) {}

void Bombergirl::Cell::render(sf::RenderWindow&) const {}