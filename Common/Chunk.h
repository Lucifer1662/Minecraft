#pragma once
#include <memory>
#include "Block.h"
#include <array>
#include "Event.h"


class Chunk
{
public:
	static const size_t chunkWidth = 16;
	static const size_t chunkHeight = 16;

	class Blocks : public std::array<std::shared_ptr<Block>, chunkWidth* chunkWidth* chunkHeight>{
	public:
		std::shared_ptr<Block>* blockAt(int x, int y, int z);
	};

private:
	Blocks blocks;


public:
	const glm::ivec3 chunkPos;
	const glm::ivec3 worldPos;
	Event<void, const std::vector<glm::ivec3>&> blocksBrokenEvent;
	Chunk(const Chunk&) = default;
	Chunk(Chunk&&) = default;
	Chunk(const glm::ivec3 chunkPos);
	Chunk(const glm::ivec3& chunkPos, const Blocks& blocks);
	Chunk(const glm::ivec3& chunkPos, Blocks&& blocks);
	Chunk& operator=(const Chunk& c) = default;
	
	

	
	std::shared_ptr<Block>& blockAt(int x, int y, int z);
	std::shared_ptr<Block>& blockAt(const glm::ivec3 worldPosition);

	
	Blocks& getBlocks();




};

