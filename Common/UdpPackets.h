#pragma once
#include "Player.h"

enum class PacketTypes : size_t {
	PlayerPosition
};

template<typename T>
struct Packet : public T{
	PacketTypes type;
};

//struct Packet {
//	PacketTypes type;
//};

struct PlayerPosition {
	PlayerID id;
	glm::vec3 position;
};
