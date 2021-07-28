#pragma once
#include "glm/vec3.hpp"
#include "glm/vec2.hpp"
#include <memory>
#include "PlayerID.h"
struct World;





class Player
{
	std::shared_ptr<World> world;
	glm::vec3 position = { 0,0,0 };
	glm::vec3 velocity = {0,0,0};
	PlayerID playerID = 0;
	glm::vec2 direction = { 0,0 };

	
public:
	Player(std::shared_ptr<World> world, const glm::vec3& position);
	void breakBlock();
	virtual void update();
	std::shared_ptr<World> getWorld();
	glm::vec3& getPosition();
	PlayerID getPlayerID() const;
	glm::vec2& getDirection();
	virtual void move(glm::vec2 direction);
	virtual void jump();
};

