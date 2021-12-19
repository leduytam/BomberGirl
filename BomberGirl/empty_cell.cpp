#include "empty_cell.h"

Bombergirl::EmptyCell::EmptyCell(const sf::Vector2i& index, SharedContext* sharedContext) : Cell(index, sharedContext) {}

Bombergirl::Cell::CellType Bombergirl::EmptyCell::getType() const
{
	return CellType::Empty;
}

bool Bombergirl::EmptyCell::isObstacle() const
{
	return false;
}
