#include "Cell.h"

Bombergirl::Cell::Cell(const Cell::Type& type, const sf::Vector2f& position) {
	m_type = type;
	m_position = position;
	m_rect = sf::FloatRect((float)position.x, (float)position.y, (float)cell_size, (float)cell_size);
}

Bombergirl::Cell::Type Bombergirl::Cell::getType() const {
	return m_type;
}

void Bombergirl::Cell::setType(const Type& type)
{
	m_type = type;
}

sf::FloatRect Bombergirl::Cell::getBound() const {
	return m_rect;
}
