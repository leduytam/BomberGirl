#include "indestructible_cell.h"

Bombergirl::IndestructibleCell::IndestructibleCell(const sf::Vector2i& index, SharedContext* sharedContext) : Cell(index, sharedContext) {}

Bombergirl::Cell::CellType Bombergirl::IndestructibleCell::getType() const
{
	return CellType::Indestructible;
}

bool Bombergirl::IndestructibleCell::isObstacle() const
{
	return true;
}
