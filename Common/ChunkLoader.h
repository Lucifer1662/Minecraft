#pragma once
#include "WorldGenerator.h"
#include "IChunkLoader.h"

class ChunkLoader : public IChunkLoader
{
	std::shared_ptr<WorldGenerator> worldGen;
public:
	ChunkLoader(const ChunkLoader&) = default;
	ChunkLoader(ChunkLoader&&) = default;
	ChunkLoader(std::shared_ptr<WorldGenerator> worldGen);
	ChunkLoader& operator=(const ChunkLoader& c) = default;
	ChunkLoader& operator=(ChunkLoader&& c) = default;

	virtual std::shared_ptr<Chunk> loadChunk(glm::ivec3 chunkPosition) override;	
	virtual ~ChunkLoader(){}
};

