#pragma once

#include <vector>
#include "ray.h"
#include "Cell.h"

namespace Bombergirl
{
	class Bomb
	{
	private:
		sf::Vector2i m_index;
		sf::Texture* m_bombTexture;
		sf::Sprite m_bombSprite;
		Animation m_bombAnimation;
		bool m_isExploded;
		std::vector<Ray*> m_rays;
		bool m_isDone;
		float m_timeAfterExplosion;
	public:
		Bomb(sf::Texture*, const sf::Vector2i&);
		~Bomb();
		void update(const float&, const std::vector<std::vector<Cell*>>&);
		void draw(sf::RenderWindow&);
		bool isExploded() const;
		bool isDone() const;
		sf::Vector2i getIndex() const;
	};
}
