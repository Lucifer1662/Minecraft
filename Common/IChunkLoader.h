#pragma once
#include "Chunk.h"
#include <memory>
#include <glm/glm.hpp>

class IChunkLoader
{
public:
	virtual std::shared_ptr<Chunk> loadChunk(glm::ivec3 chunkPosition) = 0;
	virtual ~IChunkLoader() {}
};

