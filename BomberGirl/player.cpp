#include "player.h"
#include "item_cell.h"
#include "empty_cell.h"
#include "bomb_cell.h"
#include "configs.h"

Bombergirl::Player::Player(SharedContext* sharedContext, sf::Texture* m_playerTexture, const PlayerDirection& playerDirection)
	: m_sharedContext(sharedContext), m_speed(PLAYER_DEFAULT_SPEED), m_isOnDead(false), m_isOnSetUpBomb(false), m_elapsedTime(0.f),
	m_playerDirection(playerDirection), m_bombs(PLAYER_DEFAULT_BOMBS), m_bombRange(PLAYER_DEFAULT_BOMB_RANGE)
{
	m_playerSprite.setTexture(*m_playerTexture);
	m_shadowSprite.setTexture(m_sharedContext->m_resources->getTexture("shadow"));
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

	if (m_playerDirection == PlayerDirection::Up) {
		m_walkingUpAnimation.update(0.f);
	}
	else if (m_playerDirection == PlayerDirection::Left) {
		m_walkingLeftAnimation.update(0.f);
	}
	else if (m_playerDirection == PlayerDirection::Right) {
		m_walkingRightAnimation.update(0.f);
	}
	else {
		m_walkingDownAnimation.update(0.f);
	}

	m_increaseBombCountSound = new sf::Sound();
	m_increaseBombRangeSound = new sf::Sound();
	m_IncreaseSpeedSound = new sf::Sound();
	m_hitSound = new sf::Sound();

	m_increaseBombCountSound->setBuffer(m_sharedContext->m_resources->getBuffer("get_item_IncreaseBombCount"));
	m_increaseBombRangeSound->setBuffer(m_sharedContext->m_resources->getBuffer("get_item_IncreaseBombRange"));
	m_IncreaseSpeedSound->setBuffer(m_sharedContext->m_resources->getBuffer("get_item_IncreaseSpeed"));
	m_hitSound->setBuffer(m_sharedContext->m_resources->getBuffer("hit_sound"));

	m_countWinRounds = 0;
}

void Bombergirl::Player::update(const float& dt, std::vector<std::vector<Cell*>>& map)
{
	if (m_isOnDead) {
		m_deadAnimation.update(dt);
		return;
	}

	m_elapsedTime += dt;

	sf::FloatRect playerBound = this->getBound();

	// set up bomb
	if (m_isOnSetUpBomb) {
		sf::Vector2i playerIndex = { static_cast<int>((getCenter().y / TILE_SIZE)), static_cast<int>((getCenter().x / TILE_SIZE)) };

		if (playerIndex.x >= 0 && playerIndex.x < static_cast<int>(map.size())
			&& playerIndex.y >= 0 && playerIndex.y < static_cast<int>(map.front().size())
			&& map[playerIndex.x][playerIndex.y]->getType() != Cell::CellType::Bomb) {
			m_bombs--;
			delete map[playerIndex.x][playerIndex.y];
			map[playerIndex.x][playerIndex.y] = new BombCell(playerIndex, m_sharedContext, this);
		}

		m_isOnSetUpBomb = false;
	}

	sf::Vector2f offset;

	switch (m_playerDirection)
	{
	case Player::PlayerDirection::Up:
		offset = { 0.f, -dt * m_speed };
		m_walkingUpAnimation.update(dt);
		break;
	case Player::PlayerDirection::Down:
		offset = { 0.f, dt * m_speed };
		m_walkingDownAnimation.update(dt);
		break;
	case Player::PlayerDirection::Left:
		offset = { -dt * m_speed, 0.f };
		m_walkingLeftAnimation.update(dt);
		break;
	case Player::PlayerDirection::Right:
		offset = { dt * m_speed, 0.f };
		m_walkingRightAnimation.update(dt);
		break;
	}

	sf::FloatRect newPlayerBound = {
		playerBound.left + offset.x,
		playerBound.top + offset.y,
		playerBound.width,
		playerBound.height
	};

	bool isCollision = false;
	bool isCollisionBomb = false;

	for (size_t i = 0; i < map.size(); i++)
	{
		for (size_t j = 0; j < map[i].size(); j++)
		{
			Cell* cell = map[i][j];

			if (cell->getType() == Cell::CellType::Empty) {
				continue;
			}

			if (newPlayerBound.intersects(cell->getBound())) {
				if (cell->getType() == Cell::CellType::Flame // collision flame
					|| (cell->getType() == Cell::CellType::Bomb && dynamic_cast<BombCell*>(cell)->isOnExplosion())) {
					m_isOnDead = true;
					// hit sound
					m_hitSound->play();
					return;
				}
				else if (cell->getType() == Cell::CellType::Item) { // collsion item
					ItemCell* item = dynamic_cast<ItemCell*>(cell);
					// get Item sound
					if (item->isOnExplosion()) {
						continue;
					}

					if (item->getItemType() == ItemCell::ItemType::IncreaseBombRange) {
						m_bombRange++;
						m_increaseBombRangeSound->play();
					}
					else if (item->getItemType() == ItemCell::ItemType::IncreaseBombCount) {
						m_bombs++;
						m_increaseBombCountSound->play();
					}
					else {
						m_speed += 20.f;
						m_IncreaseSpeedSound->play();

					}

					delete map[i][j];
					map[i][j] = new EmptyCell(sf::Vector2i(i, j), m_sharedContext);
				}
				else if (m_playerDirection != PlayerDirection::None && cell->isObstacle() && !isCollision) { // collision  obstacle
					if (cell->getType() == Cell::CellType::Bomb
						&& dynamic_cast<BombCell*>(cell)->isOwnerPlayerStillInside(this)) {
						continue;
					}

					// horizontal
					if (offset.x != 0.f)
					{
						auto centerPlayer_Y = this->getCenter().y;
						auto centerCell_Y = cell->getBound().top + cell->getBound().height / 2.f;
						bool isPushedUp = centerPlayer_Y < centerCell_Y - cell->getBound().height / 7.f;
						bool isPushedDown = centerPlayer_Y > centerCell_Y + cell->getBound().height / 7.f;

						float tmp = fabs(offset.x);

						if (offset.x < 0.f) { // go left
							offset.x = cell->getBound().left + cell->getBound().width - playerBound.left;
							offset.y = tmp - fabs(offset.x);
						}
						else { // go right
							offset.x = cell->getBound().left - (playerBound.left + playerBound.width);
							offset.y = tmp - fabs(offset.x);
						}

						if (isPushedUp) {
							offset.y = -offset.y;
						}
						else if (!isPushedDown) {
							offset.y = 0.f;
						}

						// 1  2  1
						// X<-O->X
						// 1  2  1
						// O: player
						// X: cell
						// 1: index1
						// 2: index2
						// ->: direction
						// i j: index of collision cell
						sf::Vector2i index1(i, j);
						sf::Vector2i index2(i, j);

						if (isPushedUp) {
							index1.x -= 1;
							index2.x -= 1;
						}
						else if (isPushedDown) {
							index1.x += 1;
							index2.x += 1;
						}

						if (m_playerDirection == Player::PlayerDirection::Left) {
							index2.y += 1;
						}
						else if (m_playerDirection == Player::PlayerDirection::Right) {
							index2.y -= 1;
						}

						if (isPushedUp || isPushedDown) {
							if (index1.x >= 0 && index1.x < static_cast<int>(map.size())
								&& index1.y >= 0 && index1.y < static_cast<int>(map.front().size())
								&& map[index1.x][index1.y]->isObstacle()) {
								offset.y = 0.f;
							}

							if (index2.x >= 0 && index2.x < static_cast<int>(map.size())
								&& index2.y >= 0 && index2.y < static_cast<int>(map.front().size())
								&& map[index2.x][index2.y]->isObstacle()
								&& !(map[index2.x][index2.y]->getType() == Cell::CellType::Bomb
									&& dynamic_cast<BombCell*>(map[index2.x][index2.y])->isOwnerPlayerStillInside(this))) {
								offset.y = 0.f;
							}
						}
					}
					else { // vertical
						auto centerPlayer_X = this->getCenter().x;
						auto centerCell_X = cell->getBound().left + cell->getBound().width / 2.f;
						bool isPushedLeft = centerPlayer_X < centerCell_X - cell->getBound().width / 7.f;
						bool isPushedRight = centerPlayer_X > centerCell_X + cell->getBound().width / 7.f;

						float tmp = fabs(offset.y);

						if (offset.y < 0.f) { // go up
							offset.y = cell->getBound().top + cell->getBound().height - playerBound.top;
							offset.x = tmp - fabs(offset.y);
						}
						else { // go down
							offset.y = cell->getBound().top - (playerBound.top + playerBound.height);
							offset.x = tmp - fabs(offset.y);
						}

						if (isPushedLeft) {
							offset.x = -offset.x;
						}
						else if (!isPushedRight) {
							offset.x = 0.f;
						}

						sf::Vector2i index1(i, j);
						sf::Vector2i index2(i, j);

						// 1 X 1
						//   ^ 
						//   |
						// 2 O 2
						//   |
						//   v
						// 1 X 1
						// O: player
						// X: cell
						// 1: index1
						// 2: index2
						// ->: direction
						// i j: index of collision cell
						if (isPushedLeft) {
							index1.y -= 1;
							index2.y -= 1;
						}
						else if (isPushedRight) {
							index1.y += 1;
							index2.y += 1;
						}

						if (m_playerDirection == Player::PlayerDirection::Up) {
							index2.x += 1;
						}
						else if (m_playerDirection == Player::PlayerDirection::Down) {
							index2.x -= 1;
						}

						if (isPushedLeft || isPushedRight) {
							if (index1.x >= 0 && index1.x < static_cast<int>(map.size())
								&& index1.y >= 0 && index1.y < static_cast<int>(map.front().size())
								&& map[index1.x][index1.y]->isObstacle()) {
								offset.x = 0.f;
							}

							if (index2.x >= 0 && index2.x < static_cast<int>(map.size())
								&& index2.y >= 0 && index2.y < static_cast<int>(map.front().size())
								&& map[index2.x][index2.y]->isObstacle()
								&& !(map[index2.x][index2.y]->getType() == Cell::CellType::Bomb
									&& dynamic_cast<BombCell*>(map[index2.x][index2.y])->isOwnerPlayerStillInside(this))) {
								offset.x = 0.f;
							}
						}
					}

					isCollision = true;
				}
			}
		}
	}

	m_playerSprite.move(offset);
	m_playerDirection = PlayerDirection::None;
}

void Bombergirl::Player::render(sf::RenderWindow& window)
{
	window.draw(m_shadowSprite, m_playerSprite.getTransform());
	window.draw(m_playerSprite);
}

void Bombergirl::Player::setDirection(const PlayerDirection& playerDirection)
{
	m_playerDirection = playerDirection;
}

void Bombergirl::Player::setPosition(const sf::Vector2f& position)
{
	m_playerSprite.setPosition({ position.x - 24.f, position.y - 24.f });
}

void Bombergirl::Player::setUpBomb()
{
	if (m_elapsedTime >= TIME_DELAY_SET_UP_BOMB && m_bombs > 0) {
		m_isOnSetUpBomb = true;
		m_elapsedTime = 0.f;
	}
}


sf::Vector2f Bombergirl::Player::getCenter() const
{
	return { getBound().left + getBound().width / 2.f, getBound().top + getBound().height / 2.f };
}

sf::FloatRect Bombergirl::Player::getBound() const
{
	return {
		m_playerSprite.getPosition().x + 8.f,
		m_playerSprite.getPosition().y + 8.f,
		m_playerSprite.getLocalBounds().width - 16.f,
		m_playerSprite.getLocalBounds().height - 8.f,
	};
}

bool Bombergirl::Player::isDead() const
{
	return m_deadAnimation.isDone();
}

bool Bombergirl::Player::isOnDead() const
{
	return m_isOnDead;
}


Bombergirl::Player::~Player() {
	delete m_increaseBombCountSound;
	delete m_increaseBombRangeSound;
	delete m_IncreaseSpeedSound;
}