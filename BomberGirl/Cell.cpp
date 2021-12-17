#include "Cell.h"

Bombergirl::Cell::Cell(Bombergirl::Cell::Type type, sf::Vector2f position) {
	m_type = type;
	m_position = position;
	m_rect = sf::FloatRect(position.x, position.y, cell_size, cell_size);
}

Bombergirl::Cell::Type Bombergirl::Cell::getType() {
	return m_type;
}

sf::FloatRect Bombergirl::Cell::getBound() {
	return m_rect;
}