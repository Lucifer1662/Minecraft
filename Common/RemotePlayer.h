#pragma once
#include "Player.h"
#include "tcp_connection.h"

struct RemotePlayer : public Player
{
	RemotePlayer(std::shared_ptr<World> world, const glm::vec3& position);
	std::shared_ptr<tcp_connection> connection;
	virtual void update();
	virtual void move(glm::vec2 direction);
	virtual void jump();
};

