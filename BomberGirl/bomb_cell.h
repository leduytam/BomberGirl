#pragma once

#include "cell.h"
#include "player.h"
#include "animation.h"

namespace Bombergirl
{
	class BombCell : public Cell
	{
	private:
		sf::Sprite m_bombSprite;
		Player* m_player;
		Animation m_bombAnimation;
		bool m_isExploded;
		float m_elapsedTimeAfterExplosion;
		bool m_isOwnerPlayerStillInside;
		int m_bombRange;

		sf::Sound* m_bombSetSound;
		sf::Sound* m_bombExplosionSound;
	public:
		BombCell(const sf::Vector2i&, SharedContext*, Player*);
		~BombCell();
		CellType getType() const override;
		bool isObstacle() const override;
		void update(const float&, std::vector<std::vector<Cell*>>&) override;
		void render(sf::RenderWindow&) const override;
		bool isOwnerPlayerStillInside(Player*) const;
		bool isOnExplosion() const;
	};
}
