#pragma once

#include <SFML/Graphics.hpp>
#include "shared_context.h"

namespace Bombergirl {
	class Cell {
	public:
		enum class CellType {
			Indestructible,
			Bomb,
			Barrel,
			Item,
			Flame,
			Empty,
		};
	protected:
		sf::Vector2i m_index;
		sf::FloatRect m_bound;
		SharedContext* m_sharedContext;
	public:
		Cell(const sf::Vector2i&, SharedContext*);
		virtual ~Cell();
		sf::FloatRect getBound() const;
		sf::Vector2i getIndex() const;
		sf::Vector2f getPosision() const;
		virtual CellType getType() const = 0;
		virtual bool isObstacle() const = 0;
		virtual void update(const float&, std::vector<std::vector<Cell*>>&);
		virtual void render(sf::RenderWindow&) const;
	};
}
