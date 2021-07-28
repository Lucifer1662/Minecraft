#include "Chunk.h"

Chunk::Chunk(const glm::ivec3 chunkPos) :
	chunkPos(chunkPos),
	worldPos(chunkPos* glm::ivec3(Chunk::chunkWidth, Chunk::chunkHeight, Chunk::chunkWidth))
{
}

Chunk::Chunk(const glm::ivec3& chunkPos, const Blocks& blocks) :
	blocks(blocks), 
	chunkPos(chunkPos),
	worldPos(chunkPos*glm::ivec3(Chunk::chunkWidth,Chunk::chunkHeight, Chunk::chunkWidth))
{
}

Chunk::Chunk(const glm::ivec3& chunkPos, Blocks&& blocks) : 
	blocks(blocks), 
	chunkPos(chunkPos),
	worldPos(chunkPos* glm::ivec3(Chunk::chunkWidth, Chunk::chunkHeight, Chunk::chunkWidth))
{
}



std::shared_ptr<Block> fakeNull;
std::shared_ptr<Block>& Chunk::blockAt(int x, int y, int z)
{
	if (x >= 0 && x < chunkWidth && z >= 0 && z < chunkWidth && y >= 0 && y < chunkHeight) {
		int index = x * chunkWidth * chunkHeight + z * chunkHeight + y;
		return blocks[index];
	}
	return fakeNull;
}

std::shared_ptr<Block>& Chunk::blockAt(const glm::ivec3 worldPosition)
{
	auto relativePos = worldPosition - worldPos;
	return blockAt(relativePos.x, relativePos.y, relativePos.z);
}

Chunk::Blocks& Chunk::getBlocks()
{
	return blocks;
}

std::shared_ptr<Block>* Chunk::Blocks::blockAt(int x, int y, int z)
{
	if (x >= 0 && x < chunkWidth && z >= 0 && z < chunkWidth && y >= 0 && y < chunkWidth) {
		int index = x * chunkWidth * chunkHeight + z * chunkHeight + y;
		return &(*this)[index];
	}
	return {};
}
