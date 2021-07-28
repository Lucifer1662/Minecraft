#include "PlayerMovedMessage.h"
#include "tcp_connection.h"
#include "bits.h"
#include "World.h"
#include "Player.h"

void PlayerMovedMessage::send(tcp_connection& connection)
{
	connection.getMutexWrite().lock();
	connection.write(MessageClass::Request);
	connection.write(MessageType::PlayerMovedDirection);
	connection.write(*this);
	connection.getMutexWrite().unlock();
}



void PlayerMovedMessage::respond(tcp_connection& connection)
{
	auto player = World::mainWorld->getPlayerOfId(playerID);
	player->move(direction);
}

void PlayerJumpedMessage::send(tcp_connection& connection)
{
	connection.getMutexWrite().lock();
	connection.write(MessageClass::Request);
	connection.write(MessageType::PlayerJumped);
	connection.write(*this);
	connection.getMutexWrite().unlock();
}

void PlayerJumpedMessage::respond(tcp_connection& connection)
{
	auto player = World::mainWorld->getPlayerOfId(playerID);
	player->jump();
}
