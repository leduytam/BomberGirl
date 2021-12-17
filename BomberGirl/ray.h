#pragma once

#include <SFML/Graphics.hpp>
#include "animation.h"

namespace Bombergirl
{
	class Ray
	{
	private:
		sf::Sprite m_sprite;
		Animation m_animation;
		bool m_isDone;
	public:
		enum class RayDirection {
			Up,
			Down,
			Left,
			Right
		};

		Ray(sf::Texture*, const RayDirection&, const sf::Vector2f&);
		void update(const float&);
		void render(sf::RenderWindow&) const;
		sf::FloatRect getBound() const;
	};
}
