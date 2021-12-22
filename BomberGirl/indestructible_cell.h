#pragma once

#include "cell.h"

namespace Bombergirl
{
	class IndestructibleCell : public Cell
	{
	public:
		IndestructibleCell(const sf::Vector2i&, SharedContext*);
		CellType getType() const override;
		bool isObstacle() const override;
	};
}
