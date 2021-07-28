#include "Player.h"
#include "World.h"
#include "GameTime.h"

Player::Player(std::shared_ptr<World> world, const glm::vec3& position)
	:world(world),
	position(position)
{
}
void Player::breakBlock()
{

}

void Player::update()
{
	velocity.y += -0.98 *mainTime.getDeltaTime();
	position += velocity * mainTime.getDeltaTime();
	position += glm::vec3(direction.x, 0, direction.y) * mainTime.getDeltaTime();

	auto floorOpt = world->rayCastDown(position + glm::vec3(0,2.0f,0));
	if (floorOpt && floorOpt->y > position.y) {
		position.y = floorOpt->y;
		velocity.y = 0;
	}
}

std::shared_ptr<World> Player::getWorld()
{
	return world;
}

glm::vec3& Player::getPosition()
{
	return position;
}

PlayerID Player::getPlayerID() const
{
	return playerID;
}

glm::vec2& Player::getDirection()
{
	return direction;
}

void Player::move(glm::vec2 direction)
{
	this->direction = direction;
}

void Player::jump()
{
	auto floorOpt = world->rayCastDown(position + glm::vec3(0, 2.0f, 0));
	if (floorOpt && floorOpt->y > position.y-0.1) {
		velocity.y += 0.05;
	}
	
}
