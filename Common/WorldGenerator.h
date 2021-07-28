#pragma once
#include "Chunk.h"
#include "PerlinNoise.h"

class WorldGenerator
{
	siv::PerlinNoise perlin = siv::PerlinNoise(3245);
public:
	std::shared_ptr<Chunk> generateChunk(const glm::ivec3& chunkPosition);
	std::shared_ptr<Block> generateBlockAt(glm::vec3 worldPosition);
};

