#pragma once

#include "cell.h"
#include "animation.h"

namespace Bombergirl
{
	class FlameCell : public Cell
	{
	private:
		sf::Sprite m_flameSprite;
		Animation m_flameAnimation;
		float m_elapsedTime;
	public:
		enum class FlameDirection {
			Up = 0,
			Left = 1,
			Right = 2,
			Down = 3
		};

		FlameCell(const sf::Vector2i&, SharedContext*, const FlameDirection&);
		CellType getType() const override;
		bool isObstacle() const override;
		void update(const float&, std::vector<std::vector<Cell*>>&) override;
		void render(sf::RenderWindow&) const override;
	};
}
