#include "player.h"
#include "configs.h"

Bombergirl::Player::Player(sf::Texture* playerTexture, sf::Texture* shadowTexture, bool isFaceUp) : m_speed(150.f), m_isDead(false)
{
	m_direction = isFaceUp ? Direction::Up : Direction::Down;
	m_playerSprite.setTexture(*playerTexture);
	m_shadowSprite.setTexture(*shadowTexture);
	m_shadowSprite.setPosition({ 0.f, 8.f });

	m_walkingDownAnimation.setSprite(&m_playerSprite);
	for (int i = 0; i < 3; i++) {
		m_walkingDownAnimation.addFrame({ i * TILE_SIZE, 0 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
	}

	m_walkingLeftAnimation.setSprite(&m_playerSprite);
	for (int i = 0; i < 3; i++) {
		m_walkingLeftAnimation.addFrame({ i * TILE_SIZE, 1 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
	}

	m_walkingRightAnimation.setSprite(&m_playerSprite);
	for (int i = 0; i < 3; i++) {
		m_walkingRightAnimation.addFrame({ i * TILE_SIZE, 2 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
	}

	m_walkingUpAnimation.setSprite(&m_playerSprite);
	for (int i = 0; i < 3; i++) {
		m_walkingUpAnimation.addFrame({ i * TILE_SIZE, 3 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
	}

	m_deadAnimation.setSprite(&m_playerSprite);
	m_deadAnimation.setFrameDuration(0.5f);
	m_deadAnimation.setRepeat(false);
	for (int i = 0; i < 3; i++) {
		m_deadAnimation.addFrame({ i * TILE_SIZE, 4 * TILE_SIZE, TILE_SIZE, TILE_SIZE });
	}

	if (isFaceUp) {
		m_walkingUpAnimation.update(0.f);
	}
	else {
		m_walkingDownAnimation.update(0.f);
	}
}

void Bombergirl::Player::update(const float& dt, const std::vector<std::vector<Cell*>>& map)
{
	if (m_isDead) {
		m_deadAnimation.update(dt);
		return;
	}

	sf::Vector2f offset;

	switch (m_direction)
	{
	case Player::Direction::Up:
		offset = { 0.f, -dt * m_speed };
		m_walkingUpAnimation.update(dt);
		break;
	case Player::Direction::Down:
		offset = { 0.f, dt * m_speed };
		m_walkingDownAnimation.update(dt);
		break;
	case Player::Direction::Left:
		offset = { -dt * m_speed, 0.f };
		m_walkingLeftAnimation.update(dt);
		break;
	case Player::Direction::Right:
		offset = { dt * m_speed, 0.f };
		m_walkingRightAnimation.update(dt);
		break;
	}

	sf::FloatRect playerBound = this->getBound();
	sf::FloatRect newPlayerBound = {
		playerBound.left + offset.x,
		playerBound.top + offset.y,
		playerBound.width,
		playerBound.height
	};

	if (newPlayerBound.top < m_arena.top) { 
		offset.y = playerBound.top - m_arena.top;
	}
	else if (newPlayerBound.top + newPlayerBound.height > m_arena.height) {
		offset.y = m_arena.height - (playerBound.top + newPlayerBound.height);
	}

	if (newPlayerBound.left < m_arena.left) { 
		offset.x = playerBound.left - m_arena.left;
	}
	else if (newPlayerBound.left + newPlayerBound.width > m_arena.width) {
		offset.x = m_arena.width - (playerBound.left + newPlayerBound.width);
	}

	bool isCollision = false;

	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[i].size(); j++)
		{
			Cell* cell = map[i][j];
			auto isBlocked = [](const Cell::Type& type) {
				return type == Cell::Type::Crate || type == Cell::Type::Border || type == Cell::Type::Obstacle;
			};

			if (newPlayerBound.intersects(cell->getBound()) && (cell->getType() == Cell::Type::Obstacle || cell->getType() == Cell::Type::Crate)) {
				
				if (offset.x != 0.f)
				{
					auto centerPlayer_Y = this->getCenter().y;
					auto centerCell_Y = cell->getBound().top + cell->getBound().height / 2.f;
					bool isUp = centerPlayer_Y < centerCell_Y - cell->getBound().height / 7.f;
					bool isDown = centerPlayer_Y > centerCell_Y + cell->getBound().height / 7.f;

					float tmp = fabs(offset.x);

					if (offset.x < 0.f) {
						offset.x = cell->getBound().left + cell->getBound().width - playerBound.left;
						offset.y = tmp - fabs(offset.x);
					}
					else {
						offset.x = cell->getBound().left - (playerBound.left + playerBound.width);
						offset.y = tmp - fabs(offset.x);
					}

					if (isUp) {
						offset.y = -offset.y;
					}
					else if (!isDown) {
						offset.y = 0.f;
					}

					sf::Vector2i index1 = { i, j };
					sf::Vector2i index2 = { i, j };

					if (isUp) {
						index1.x -= 1;
						index2.x -= 1;
					}
					else if (isDown) {
						index1.x += 1;
						index2.x += 1;
					}

					if (m_direction == Player::Direction::Left) {
						index2.y += 1;
					}
					else if (m_direction == Player::Direction::Right) {
						index2.y -= 1;
					}

					if (isUp || isDown) {
						if (index1.x >= 0 && index1.x < map.size() && index1.y >= 0 && index1.y < map.front().size() && isBlocked(map[index1.x][index1.y]->getType())) {
							offset.y = 0.f;
						}

						if (index2.x >= 0 && index2.x < map.size() && index2.y >= 0 && index2.y < map.front().size() && isBlocked(map[index2.x][index2.y]->getType())) {
							offset.y = 0.f;
						}
					}
				}
				else {
					auto centerPlayer_X = this->getCenter().x;
					auto centerCell_X = cell->getBound().left + cell->getBound().width / 2.f;
					bool isLeft = centerPlayer_X < centerCell_X - cell->getBound().width / 7.f;
					bool isRight = centerPlayer_X > centerCell_X + cell->getBound().width / 7.f;

					float tmp = fabs(offset.y);

					if (offset.y < 0.f) {
						offset.y = cell->getBound().top + cell->getBound().height - playerBound.top;
						offset.x = tmp - fabs(offset.y);
					}
					else {
						offset.y = cell->getBound().top - (playerBound.top + playerBound.height);
						offset.x = tmp - fabs(offset.y);
					}

					if (isLeft) {
						offset.x = -offset.x;
					}
					else if (!isRight) {
						offset.x = 0.f;
					}

					sf::Vector2i index1 = { i, j };
					sf::Vector2i index2 = { i, j };

					if (isLeft) {
						index1.y -= 1;
						index2.y -= 1;
					}
					else if (isRight) {
						index1.y += 1;
						index2.y += 1;
					}

					if (m_direction == Player::Direction::Up) {
						index2.x += 1;
					}
					else if (m_direction == Player::Direction::Down) {
						index2.x -= 1;
					}

					if (isLeft || isRight) {
						if (index1.x >= 0 && index1.x < map.size() && index1.y >= 0 && index1.y < map.front().size() && isBlocked(map[index1.x][index1.y]->getType())) {
							offset.x = 0.f;
						}

						if (index2.x >= 0 && index2.x < map.size() && index2.y >= 0 && index2.y < map.front().size() && isBlocked(map[index2.x][index2.y]->getType())) {
							offset.x = 0.f;
						}
					}
				}

				isCollision = true;
				break;
			}
		}

		if (isCollision) {
			break;
		}
	}

	m_playerSprite.move(offset);

	m_direction = Direction::None;
}

void Bombergirl::Player::render(sf::RenderWindow& window)
{
	window.draw(m_shadowSprite, m_playerSprite.getTransform());
	window.draw(m_playerSprite);

	sf::RectangleShape rect;
	rect.setPosition({ getBound().left, getBound().top });
	rect.setSize({ getBound().width, getBound().height });
	rect.setFillColor(sf::Color::Transparent);
	rect.setOutlineColor(sf::Color::Red);
	rect.setOutlineThickness(-2.f);
	window.draw(rect);
}

void Bombergirl::Player::moveUp()
{
	m_direction = Direction::Up;
}

void Bombergirl::Player::moveDown()
{
	m_direction = Direction::Down;
}

void Bombergirl::Player::moveLeft()
{
	m_direction = Direction::Left;
}

void Bombergirl::Player::moveRight()
{
	m_direction = Direction::Right;
}

void Bombergirl::Player::setIsDead()
{
	m_isDead = true;
}

void Bombergirl::Player::setPosition(const sf::Vector2f& position)
{
	m_playerSprite.setPosition({ position.x - 24.f, position.y - 24.f });
}

void Bombergirl::Player::setSpeed(const float& speed)
{
	m_speed = speed;
}

void Bombergirl::Player::setArena(const sf::IntRect& arena) {
	m_arena.left = (int)(arena.left + m_playerSprite.getLocalBounds().width);
	m_arena.top = (int)(arena.top + m_playerSprite.getLocalBounds().height);
	m_arena.width = (int)(arena.width - m_playerSprite.getLocalBounds().width);
	m_arena.height = (int)(arena.height - m_playerSprite.getLocalBounds().height);
}

sf::Vector2f Bombergirl::Player::getCenter()
{
	return { getBound().left + getBound().width / 2.f, getBound().top + getBound().height / 2.f };
}

sf::FloatRect Bombergirl::Player::getBound()
{
	return {
		m_playerSprite.getPosition().x + 8.f,
		m_playerSprite.getPosition().y + 8.f,
		m_playerSprite.getLocalBounds().width - 16.f,
		m_playerSprite.getLocalBounds().height - 8.f,
	};
}
