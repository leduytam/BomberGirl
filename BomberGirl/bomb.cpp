#include "bomb.h"
#include "configs.h"
#include "Cell.h"

Bombergirl::Bomb::Bomb(sf::Texture* texture, const sf::Vector2i& index) : m_bombTexture(texture), m_isExploded(false), m_index(index), m_isDone(false), m_timeAfterExplosion(0.f)
{
	m_bombSprite.setTexture(*m_bombTexture);
	m_bombSprite.setPosition(sf::Vector2f(static_cast<float>(m_index.y * TILE_SIZE), static_cast<float>(m_index.x * TILE_SIZE)));

	m_bombAnimation.setSprite(&m_bombSprite);
	m_bombAnimation.setFrameDuration(0.4f);
	m_bombAnimation.setRepeat(false);

	for (int i = 0; i < 4; i++) {
		m_bombAnimation.addFrame({ i * TILE_SIZE, 0, TILE_SIZE, TILE_SIZE });
	}
}

Bombergirl::Bomb::~Bomb()
{
	for (auto& ray : m_rays) {
		delete ray;
	}
}

void Bombergirl::Bomb::update(const float& dt, const std::vector<std::vector<Cell*>>& map)
{
	m_bombAnimation.update(dt);

	if (m_isExploded) {
		for (auto& ray : m_rays) {
			ray->update(dt);
		}

		m_timeAfterExplosion += dt;

		if (m_timeAfterExplosion >= TIME_RAY_EXIST) {
			m_isDone = true;
		}
	}

	if (m_bombAnimation.isDone() && !m_isExploded)
	{
		m_isExploded = true;

		auto isBlocked = [](const Cell::Type& type) {
			return type == Cell::Type::Crate || type == Cell::Type::Border || type == Cell::Type::Obstacle;
		};

		int up = 0, left = 0, right = 0, down = 0;

		for (int i = m_index.x - 1; i >= 0; i--) {
			if (isBlocked(map[i][m_index.y]->getType())) {
				if (map[i][m_index.y]->getType() == Cell::Type::Crate) {
					map[i][m_index.y]->setType(Cell::Type::None);
				}
				break;
			}
			++up;
		}

		for (int i = m_index.y - 1; i >= 0; i--) {
			if (isBlocked(map[m_index.x][i]->getType())) {
				if (map[m_index.x][i]->getType() == Cell::Type::Crate) {
					map[m_index.x][i]->setType(Cell::Type::None);
				}
				break;
			}
			++left;
		}

		for (unsigned int i = m_index.y + 1; i < map.front().size(); i++) {
			if (isBlocked(map[m_index.x][i]->getType())) {
				if (map[m_index.x][i]->getType() == Cell::Type::Crate) {
					map[m_index.x][i]->setType(Cell::Type::None);
				}
				break;
			}
			++right;
		}

		for (unsigned int i = m_index.x + 1; i < map.size(); i++) {
			if (isBlocked(map[i][m_index.y]->getType())) {
				if (map[i][m_index.y]->getType() == Cell::Type::Crate) {
					map[i][m_index.y]->setType(Cell::Type::None);
				}
				break;
			}
			++down;
		}

		for (int i = 0; i < up; i++) {
			m_rays.push_back(new Ray(m_bombTexture, Ray::RayDirection::Up, sf::Vector2f(static_cast<float>(m_index.y * TILE_SIZE), static_cast<float>((m_index.x - 1 - i) * TILE_SIZE))));
		}

		for (int i = 0; i < left; i++) {
			m_rays.push_back(new Ray(m_bombTexture, Ray::RayDirection::Left, sf::Vector2f(static_cast<float>((m_index.y - 1 - i) * TILE_SIZE), static_cast<float>(m_index.x * TILE_SIZE))));
		}

		for (int i = 0; i < right; i++) {
			m_rays.push_back(new Ray(m_bombTexture, Ray::RayDirection::Right, sf::Vector2f(static_cast<float>((m_index.y + 1 + i) * TILE_SIZE), static_cast<float>(m_index.x * TILE_SIZE))));
		}

		for (int i = 0; i < down; i++) {
			m_rays.push_back(new Ray(m_bombTexture, Ray::RayDirection::Down, sf::Vector2f(static_cast<float>(m_index.y * TILE_SIZE), static_cast<float>((m_index.x + 1 + i) * TILE_SIZE))));
		}
	}
}

void Bombergirl::Bomb::draw(sf::RenderWindow& window)
{
	window.draw(m_bombSprite);

	for (const auto& ray : m_rays) {
		ray->render(window);
	}
}

bool Bombergirl::Bomb::isExploded() const
{
	return m_isExploded;
}

bool Bombergirl::Bomb::isDone() const
{
	return m_isDone;
}

sf::Vector2i Bombergirl::Bomb::getIndex() const
{
	return m_index;
}
