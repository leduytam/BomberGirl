#pragma once

#include "cell.h"
#include "animation.h"

namespace Bombergirl
{
	class BarrelCell : public Cell
	{
	private:
		sf::Sprite m_barrelSprite;
		sf::Sprite m_explosionSprite;
		Animation m_explosionAnimation;
		bool m_isOnExplosion;
	public:
		BarrelCell(const sf::Vector2i&, SharedContext*);
		CellType getType() const override;
		bool isObstacle() const override;
		void update(const float&, std::vector<std::vector<Cell*>>&) override;
		void render(sf::RenderWindow&) const override;
		void setOnExplosion();
	};
}
