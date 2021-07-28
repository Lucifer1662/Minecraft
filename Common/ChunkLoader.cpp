#include "ChunkLoader.h"

ChunkLoader::ChunkLoader(std::shared_ptr<WorldGenerator> worldGen) :worldGen(worldGen)
{
}

std::shared_ptr<Chunk> ChunkLoader::loadChunk(glm::ivec3 chunkPosition)
{
	return worldGen->generateChunk(chunkPosition);
}
