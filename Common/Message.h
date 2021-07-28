#pragma once
#include <boost/asio.hpp>
#include <glm/glm.hpp>
#include <future>
#include "Chunk.h"
#include <memory>

class tcp_connection;

enum class MessageType : size_t {
	GetChunk,
	PlayerMovedDirection,
	Connect,
	PlayerJumped
};

#define MessageTypeSize 1


enum class MessageClass : unsigned char {
	Request,
	Response
};

using MessageID = size_t;




struct GetChunkMessageResponse {
	glm::ivec3 chunkPos;
	void send(tcp_connection& connection);
};



struct GetChunkMessage{

	glm::ivec3 chunkPos;
	MessageID messageID;

	std::future<std::shared_ptr<Chunk>> send(tcp_connection& connection);
	static std::shared_ptr<Chunk> getChunk(tcp_connection& connection, const glm::ivec3 position);
	void respond(tcp_connection& connection);
};





