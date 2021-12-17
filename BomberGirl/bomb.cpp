#include "bomb.h"
#include "configs.h"
#include <iostream>

Bombergirl::Bomb::Bomb(sf::Texture* texture, const sf::Vector2i& pos) : m_bombTexture(texture), m_isExploded(false), m_pos(pos), m_isDone(false), m_timeAfterExplosion(0.f)
{
	m_bombSprite.setTexture(*m_bombTexture);
	m_bombSprite.setPosition(sf::Vector2f(static_cast<float>(m_pos.y * TILE_SIZE), static_cast<float>(m_pos.x * TILE_SIZE)));

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

		for (int i = 0; i < 3; i++) {
			m_rays.push_back(new Ray(m_bombTexture, Ray::RayDirection::Up, sf::Vector2f(static_cast<float>(m_pos.y * TILE_SIZE), static_cast<float>((m_pos.x - 1 - i) * TILE_SIZE))));
		}

		for (int i = 0; i < 3; i++) {
			m_rays.push_back(new Ray(m_bombTexture, Ray::RayDirection::Left, sf::Vector2f(static_cast<float>((m_pos.y - 1 - i) * TILE_SIZE), static_cast<float>(m_pos.x * TILE_SIZE))));
		}

		for (int i = 0; i < 3; i++) {
			m_rays.push_back(new Ray(m_bombTexture, Ray::RayDirection::Right, sf::Vector2f(static_cast<float>((m_pos.y + 1 + i) * TILE_SIZE), static_cast<float>(m_pos.x * TILE_SIZE))));
		}

		for (int i = 0; i < 3; i++) {
			m_rays.push_back(new Ray(m_bombTexture, Ray::RayDirection::Down, sf::Vector2f(static_cast<float>(m_pos.y * TILE_SIZE), static_cast<float>((m_pos.x + 1 + i) * TILE_SIZE))));
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
