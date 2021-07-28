#include "WorldRenderer.h"
#include "glm/glm.hpp"
#include <algorithm>

WorldRenderer::WorldRenderer(std::shared_ptr<World> world) : world(world)
{
	world->newChunkloaded += [=](auto chunk) {this->addChunk(chunk); };
}


void WorldRenderer::render()
{
	//removeDistanceChunks();
	loadChunks();
	for (auto& chunk : chunkRenderers)
	{
		chunk.second->render();
	}
}

void WorldRenderer::addChunk(std::shared_ptr<Chunk> chunk)
{
	
	chunkRenderers.insert_or_assign(chunk->chunkPos, std::make_shared<ChunkRenderer>(chunk));
}

void WorldRenderer::removeDistanceChunks()
{

	std::vector<decltype(chunkRenderers)::key_type> vec;
	auto chunkPos = World::worldToChunkPos(position);
	chunkPos.y = 0;
	for (auto& i : chunkRenderers) {
		auto chunk = i.second->getChunk();
		auto dis = glm::abs(chunk->chunkPos - chunkPos);
		if (dis.x > chunkRadius || dis.y > chunkRadius || dis.z > chunkRadius) {
			vec.emplace_back(i.first);
		}
	}
	for (auto& key : vec)
		chunkRenderers.erase(key);
}

void WorldRenderer::loadChunks(){
	auto chunkPos = World::worldToChunkPos(position);
	for (int x = -chunkRadius; x <= chunkRadius; x++){
		for (int z = -chunkRadius; z <= chunkRadius; z++){
			auto pos = chunkPos + glm::ivec3(x, 0, z);
			pos.y = 0;
			auto it = chunkRenderers.find(pos);
			if (it == chunkRenderers.end()) {
				//loading a chunk causes a chunk renderer to be added
				auto chunk = world->getChunkAtChunkPos(pos);
			}
		}
	}
}
