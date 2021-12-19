#pragma once

#include "cell.h"
#include "animation.h"

namespace Bombergirl
{
	class ItemCell : public Cell
	{
	public:
		enum class ItemType
		{
			IncreaseBombRange = 0,
			IncreaseBombCount = 1,
			IncreaseSpeed = 2,
			Count = 3
		};
	private:
		ItemType m_itemType;
		sf::Sprite m_itemSprite;
		sf::Sprite m_explosionSprite;
		Animation m_explosionAnimation;
		bool m_isOnExplosion;
		float m_elapsedTime;
	public:
		ItemCell(const sf::Vector2i&, SharedContext*, const ItemType&);
		CellType getType() const override;
		bool isObstacle() const override;
		void update(const float&, std::vector<std::vector<Cell*>>&) override;
		void render(sf::RenderWindow&) const override;
		void setOnExplosion();
		ItemType getItemType() const;
		bool isOnExplosion() const;
	};
}
