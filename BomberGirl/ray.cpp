#include "ray.h"
#include "configs.h"

Bombergirl::Ray::Ray(sf::Texture* texture, const RayDirection& direction, const sf::Vector2f& position) : m_isDone(false)
{
	m_sprite.setTexture(*texture);
	m_sprite.setPosition(position);

	m_animation.setSprite(&m_sprite);
	m_animation.setFrameDuration(0.2f);

	int j = 1;

	if (direction == RayDirection::Up) {
		j = 1;
	}
	else if (direction == RayDirection::Left) {
		j = 2;
	}
	else if (direction == RayDirection::Right) {
		j = 3;
	}
	else if (direction == RayDirection::Down) {
		j = 4;
	}

	for (int i = 0; i < 3; i++) {
		m_animation.addFrame({ i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE });
	}
}

void Bombergirl::Ray::update(const float& dt)
{
	m_animation.update(dt);
}

void Bombergirl::Ray::render(sf::RenderWindow& window) const
{
	window.draw(m_sprite);
}

sf::FloatRect Bombergirl::Ray::getBound() const
{
	return { m_sprite.getPosition().x, m_sprite.getPosition().y, m_sprite.getLocalBounds().width, m_sprite.getLocalBounds().height };
}