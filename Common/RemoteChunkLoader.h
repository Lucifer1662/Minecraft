#pragma once
#include "IChunkLoader.h"
#include "tcp_connection.h"

class RemoteChunkLoader : public IChunkLoader
{
	std::shared_ptr<tcp_connection> connection;
public:
	RemoteChunkLoader(const RemoteChunkLoader&) = default;
	RemoteChunkLoader(RemoteChunkLoader&&) = default;
	RemoteChunkLoader(std::shared_ptr<tcp_connection> connection);
	RemoteChunkLoader& operator=(const RemoteChunkLoader& c) = default;
	RemoteChunkLoader& operator=(RemoteChunkLoader&& c) = default;

	virtual std::shared_ptr<Chunk> loadChunk(glm::ivec3 chunkPosition) override;

	virtual ~RemoteChunkLoader() {}
};

