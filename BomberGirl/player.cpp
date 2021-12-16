#include "player.h"
#include<iostream>

Bombergirl::Player::Player(sf::Texture* playerTexture, sf::Texture* shadowTexture, bool directDown) : m_speed(150.f), m_isDying(false)
{
	m_direction = directDown ? Direction::Down : Direction::Up;
	m_playerSprite.setTexture(*playerTexture);
	m_shadowSprite.setTexture(*shadowTexture);
	m_shadowSprite.setPosition({ 0.f, 8.f });

	m_walkingDown.setSprite(&m_playerSprite);
	m_walkingDown.addFrame({ 0, 0, 48, 48 });
	m_walkingDown.addFrame({ 48, 0, 48, 48 });
	m_walkingDown.addFrame({ 96, 0, 48, 48 });
	m_walkingDown.update(0.f);

	m_walkingLeft.setSprite(&m_playerSprite);
	m_walkingLeft.addFrame({ 0, 48, 48, 48 });
	m_walkingLeft.addFrame({ 48, 48, 48, 48 });
	m_walkingLeft.addFrame({ 96, 48, 48, 48 });

	m_walkingRight.setSprite(&m_playerSprite);
	m_walkingRight.addFrame({ 0, 96, 48, 48 });
	m_walkingRight.addFrame({ 48, 96, 48, 48 });
	m_walkingRight.addFrame({ 96, 96, 48, 48 });

	m_walkingUp.setSprite(&m_playerSprite);
	m_walkingUp.addFrame({ 0, 144, 48, 48 });
	m_walkingUp.addFrame({ 48, 144, 48, 48 });
	m_walkingUp.addFrame({ 96, 144, 48, 48 });

	m_dying.setSprite(&m_playerSprite);
	m_dying.addFrame({ 0, 192, 48, 48 });
	m_dying.addFrame({ 48, 192, 48, 48 });
	m_dying.addFrame({ 96, 192, 48, 48 });



}

void Bombergirl::Player::update(const float& dt, const std::vector<std::vector<Cell*>>& map)
{
	sf::Vector2f offset;

	switch (m_direction)
	{
	case Player::Direction::Up:
		offset = { 0.f, -dt * m_speed };
		m_walkingUp.update(dt);
		break;
	case Player::Direction::Down:
		offset = { 0.f, dt * m_speed };
		m_walkingDown.update(dt);
		break;
	case Player::Direction::Left:
		offset = { -dt * m_speed, 0.f };
		m_walkingLeft.update(dt);
		break;
	case Player::Direction::Right:
		offset = { dt * m_speed, 0.f };
		m_walkingRight.update(dt);
		break;
	}

	sf::Vector2f newPos = offset + m_playerSprite.getPosition();

	if (newPos.y < m_arena.top || newPos.y > m_arena.height) {
		offset.y = 0.f;
	}
	if (newPos.x < m_arena.left || newPos.x > m_arena.width) {
		offset.x = 0.f;
	}

	bool isCollision = false;

	sf::FloatRect playerBound = this->getBound();
	sf::FloatRect newPlayerBound = {
		playerBound.left + offset.x,
		playerBound.top + offset.y,
		playerBound.width,
		playerBound.height
	};

	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[i].size(); j++)
		{
			Cell* cell = map[i][j];

			if (newPlayerBound.intersects(cell->getBound()) && cell->getType() == 1) {
				if (offset.x != 0.f)
				{
					auto centerPlayer_Y = playerBound.top + playerBound.height / 2.f;
					auto centerCell_Y = cell->getBound().top + cell->getBound().height / 2.f;
					bool isUp = centerPlayer_Y < centerCell_Y;

					float tmp = fabs(offset.x);

					if (offset.x < 0.f)
					{
						offset.x = cell->getBound().left + cell->getBound().width - playerBound.left;
						offset.y = tmp - fabs(offset.x);
					}
					else
					{
						offset.x = cell->getBound().left - (playerBound.left + playerBound.width);
						offset.y = tmp - fabs(offset.x);
					}

					if (isUp) {
						offset.y = -offset.y;
					}
				}
				//else {
				//	auto centerPlayer_X = newPlayerBound.left + newPlayerBound.width / 2.f;
				//	auto centerCell_Y = cell->getBound().left + cell->getBound().width / 2.f;
				//}
			}
		}
	}



	/*for (const auto& row : map) {
		for (const auto& cell : row) {
			if (newPlayerBound.intersects(cell->getBound()) && cell->getType() == 1) {
				if (v.x != 0.f)
				{
					auto centerPlayer_Y = newPlayerBound.top + newPlayerBound.height / 2.f;
					auto centerCell_Y = cell->getBound().top + cell->getBound().height / 2.f;
					bool isUp = centerPlayer_Y < centerCell_Y;
					
					if (v.x < 0.f)
					{
						auto gap_X = cell->getBound().left + cell->getBound().width - newPlayerBound.left;

					}
					else
					{
						auto gap_X = newPlayerBound.left + newPlayerBound.width - cell->getBound().left;
					}
				}
				else {
					auto centerPlayer_X = newPlayerBound.left + newPlayerBound.width / 2.f;
					auto centerCell_Y = cell->getBound().left + cell->getBound().width / 2.f;
				}

				isCollision = true;
				break;
			}
		}

		if (isCollision) {
			break;
		}
	}*/
	m_playerSprite.move(offset);
	//if (m_isDying)
	//{
	//    m_dying.update(dt);
	//}
	//else
	//{
	//    switch (m_direction)
	//    {
	//    case Player::Direction::Up:
	//        m_playerSprite.move(0.f, -dt * m_speed);
	//        m_walkingUp.update(dt);
	//        if (m_playerSprite.getPosition().y < m_arena.top) {
	//            m_playerSprite.move(0.f, dt * m_speed);
	//        }
	//        break;
	//    case Player::Direction::Down:
	//        m_playerSprite.move(0.f, dt * m_speed);
	//        m_walkingDown.update(dt);
	//        if (m_playerSprite.getPosition().y > (m_arena.height)) {
	//            m_playerSprite.move(0.f, -dt * m_speed);
	//        }
	//        break;
	//    case Player::Direction::Left:
	//        m_playerSprite.move(-dt * m_speed, 0.f);
	//        m_walkingLeft.update(dt);
	//        if (m_playerSprite.getPosition().x < m_arena.left) {
	//            m_playerSprite.move(dt * m_speed, 0.f);
	//        }
	//        break;
	//    case Player::Direction::Right:
	//        m_playerSprite.move(dt * m_speed, 0.f);
	//        m_walkingRight.update(dt);
	//        if (m_playerSprite.getPosition().x > (m_arena.width)) {
	//            m_playerSprite.move(-dt * m_speed, 0.f);
	//        }
	//        break;
	//    }
	//}

	m_direction = Direction::None;
}

void Bombergirl::Player::render(sf::RenderWindow& window)
{
	window.draw(m_shadowSprite, m_playerSprite.getTransform());
	window.draw(m_playerSprite);
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

void Bombergirl::Player::die()
{
	m_isDying = true;
}



void Bombergirl::Player::setPosition(const sf::Vector2f& position)
{
	m_playerSprite.setPosition({ position.x - 24.f, position.y - 24.f });
}

void Bombergirl::Player::setArena(const sf::IntRect& arena) {
	m_arena.left = arena.left + m_playerSprite.getLocalBounds().width;
	m_arena.top = arena.top + m_playerSprite.getLocalBounds().height;
	m_arena.width = arena.width - 2 * m_playerSprite.getLocalBounds().width;
	m_arena.height = arena.height - 2 * m_playerSprite.getLocalBounds().height;

}

sf::FloatRect Bombergirl::Player::getBound()
{
	return {
		m_playerSprite.getPosition().x + 8.f,
		m_playerSprite.getPosition().y + 8.f,
		m_playerSprite.getLocalBounds().width - 8.f,
		m_playerSprite.getLocalBounds().height - 8.f,
	};
}
