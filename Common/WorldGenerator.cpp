#include "WorldGenerator.h"
#include "StandardBlock.h"

std::shared_ptr<Chunk> WorldGenerator::generateChunk(const glm::ivec3& chunkPosition)
{
    auto chunk = std::make_shared<Chunk>(chunkPosition);
    auto& blocks = chunk->getBlocks();
	size_t i = 0;
	for (int x = 0; x < Chunk::chunkWidth; x++)
	{
		for (int z = 0; z < Chunk::chunkWidth; z++)
		{
			for (int y = 0; y < Chunk::chunkHeight; y++)
			{
				blocks[i] = generateBlockAt(glm::ivec3( x,y,z ) + chunk->worldPos);
				i++;
			}
		}
	}
	return chunk;
}

std::shared_ptr<Block> WorldGenerator::generateBlockAt(glm::vec3 worldPosition)
{
	/*if (worldPosition.z == 15) {
		return std::make_shared<Dirt>();
	}
	return {};*/

	/*if ((rand()/100)%2) {
		return std::make_shared<Dirt>();
	}
	return {};*/

	auto pos = worldPosition / 20.0f;


	auto s = perlin.accumulatedOctaveNoise2D(pos.x, pos.z,8);
	
	if (s < 0) s = 0;

	s *= 10;
	

	if (s >= worldPosition.y) {
		return std::make_shared<Dirt>();
	}
	return std::make_shared<Air>();

	
}
