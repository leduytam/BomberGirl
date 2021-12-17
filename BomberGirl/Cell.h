#pragma once

#include <SFML/Graphics.hpp>

namespace Bombergirl {
	class Cell {
	public:
		enum class Type {
			Border,
			Obstacle,
			Bomb,
			Item_increaseBomb,
			Item_increaseSpeed,
			Item_increaseRange,
			Crate,
			None,
		};
	private:
		sf::Vector2f m_position;
		sf::FloatRect m_rect;
		Type m_type;
		const int cell_size = 48;
	public:
		
		Cell(Type type = Type::Border, sf::Vector2f position = sf::Vector2f(0, 0));
		Type getType();

		sf::FloatRect getBound();
	};
}

