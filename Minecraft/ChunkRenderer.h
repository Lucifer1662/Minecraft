#pragma once
#include "Chunk.h"
#include <memory>
#include "MeshRenderer.h"

class ChunkRenderer
{
	std::shared_ptr<Chunk> chunk;
	std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();

	MeshRenderer meshRenderer = MeshRenderer();
	ChunkRenderer(const ChunkRenderer&) = delete;
	ChunkRenderer(ChunkRenderer&&) = delete;
	ChunkRenderer& operator=(const ChunkRenderer& c) = delete;
	ChunkRenderer& operator=(ChunkRenderer&& c) = delete;


public:
	ChunkRenderer(std::shared_ptr<Chunk> chunk);

	//ChunkRenderer(const ChunkRenderer&) = default;
	//ChunkRenderer(ChunkRenderer&&) = default;
	//ChunkRenderer& operator=(const ChunkRenderer& c) = default;
	//ChunkRenderer& operator=(ChunkRenderer&& c) = default;

	

	void calculateMesh();
	std::shared_ptr<Mesh> getMesh();
	void blocksRemoved(const std::vector<glm::ivec3> blocks);


	void render();
	std::shared_ptr<Chunk> getChunk();
	~ChunkRenderer();
};

