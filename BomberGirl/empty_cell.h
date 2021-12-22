#pragma once

#include "cell.h"

namespace Bombergirl
{
	class EmptyCell : public Cell
	{
	public:
		EmptyCell(const sf::Vector2i&, SharedContext*);
		CellType getType() const override;
		bool isObstacle() const override;
	};
}
