#pragma once

#include <SFML/Graphics.hpp>

namespace Bombergirl {
	class Cell {
	private:
		sf::Vector2f m_position;
		sf::FloatRect m_rect;
		int m_type;
		const int cell_size = 48;
	public:
		Cell(int type = 0, sf::Vector2f position = sf::Vector2f(0, 0));
		int getType();

		sf::FloatRect getBound();
	};
}

