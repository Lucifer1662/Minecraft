#include "RemotePlayer.h"
#include "PlayerMovedMessage.h"

RemotePlayer::RemotePlayer(std::shared_ptr<World> world, const glm::vec3& position)
	: Player(world, position)
{
}

void RemotePlayer::update()
{
}

void RemotePlayer::move(glm::vec2 direction)
{
	PlayerMovedMessage message;
	message.playerID = getPlayerID();
	message.direction = direction;
	message.send(*connection);
}

void RemotePlayer::jump()
{
	PlayerJumpedMessage message;
	message.playerID = getPlayerID();
	message.send(*connection);
}
