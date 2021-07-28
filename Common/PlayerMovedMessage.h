#pragma once
#include "Message.h"
#include "PlayerID.h"

struct PlayerMovedMessage
{
	PlayerID playerID;
	glm::vec2 direction;
	void send(tcp_connection& connection);
	void respond(tcp_connection& connection);
};

struct PlayerJumpedMessage
{
	PlayerID playerID;
	void send(tcp_connection& connection);
	void respond(tcp_connection& connection);
};


