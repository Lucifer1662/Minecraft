#pragma once
#include <memory>
#include "World.h"
#include "ChunkRenderer.h"
#include <unordered_map>
#include "IVec3KeyHasher.h"

class WorldRenderer
{
	std::shared_ptr<World> world;

public:
	int chunkRadius=1;
	glm::vec3 position;
	WorldRenderer(std::shared_ptr<World> world);

	std::unordered_map<glm::ivec3, std::shared_ptr<ChunkRenderer>, IVec3KeyHasher> chunkRenderers;
	
	void render();
	void addChunk(std::shared_ptr<Chunk> chunk);
	void removeDistanceChunks();
	void loadChunks();
};

