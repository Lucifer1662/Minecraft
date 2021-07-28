#include "RemoteChunkLoader.h"
#include "Message.h"

RemoteChunkLoader::RemoteChunkLoader(std::shared_ptr<tcp_connection> connection)
	: connection(connection)
{
}

std::shared_ptr<Chunk> RemoteChunkLoader::loadChunk(glm::ivec3 chunkPosition)
{
	auto message = GetChunkMessage();
	message.chunkPos = chunkPosition;
	auto chunk_future = message.send(*connection);
	return chunk_future.get();
}
