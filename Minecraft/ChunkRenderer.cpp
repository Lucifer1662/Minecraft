#include "ChunkRenderer.h"
#include "MaterialFactory.h"
#include <iostream>

ChunkRenderer::ChunkRenderer(std::shared_ptr<Chunk> chunk) : chunk(chunk)
{	
	materialFactory.fragmentShaderFromFile("simpleFrag.frag");
	materialFactory.vertexShaderFromFile("simpleVertex.vert");


	auto material = materialFactory.create();

	auto texture = std::make_shared<Texture>();
	texture->load("assets/images/texture.png");
	material->setMainTexture(texture);

	meshRenderer.setMesh(mesh);
	meshRenderer.setMaterial(material);

	std::cout << this << std::endl;
	chunk->blocksBrokenEvent += [=](auto& blocks) { this->blocksRemoved(blocks); };

	calculateMesh();

}

void ChunkRenderer::render()
{

	meshRenderer.render();
}

std::shared_ptr<Chunk> ChunkRenderer::getChunk()
{
	return chunk;
}

ChunkRenderer::~ChunkRenderer()
{
	std::cout << this << "  Deleted" << std::endl;
}




void ChunkRenderer::calculateMesh()
{
	auto newMesh = std::make_shared<Mesh>();

	auto& blocks = chunk->getBlocks();
	size_t i = 0;
	for (int x = 0; x < Chunk::chunkWidth; x++)
	{
		for (int z = 0; z < Chunk::chunkWidth; z++)
		{
			for (int y = 0; y < Chunk::chunkHeight; y++)
			{
				auto& block = blocks[i];
				if (block) {
					Block::IsNeibhoursSolid solid;


					auto west = chunk->blockAt(x - 1, y, z);
					auto east = chunk->blockAt(x + 1, y, z);
					auto top = chunk->blockAt(x, y + 1, z);
					auto bottom = chunk->blockAt(x, y - 1, z);
					auto north = chunk->blockAt(x, y, z - 1);
					auto south = chunk->blockAt(x, y, z + 1);

					solid.set(Block::East, east && east->isSolid());
					solid.set(Block::West, west && west->isSolid());
					solid.set(Block::Top, top && top->isSolid());
					solid.set(Block::Bottom, bottom && bottom->isSolid());
					solid.set(Block::South, south && south->isSolid());
					solid.set(Block::North, north && north->isSolid());

					if (x + 1 >= Chunk::chunkWidth)
						solid.set(Block::East, false);
					if (x - 1 < 0)
						solid.set(Block::West, false);
					if (y + 1 >= Chunk::chunkHeight)
						solid.set(Block::Top, false);
					if (y - 1 < 0)
						solid.set(Block::Bottom, false);
					if (z + 1 >= Chunk::chunkWidth)
						solid.set(Block::South, false);
					if (z - 1 < 0)
						solid.set(Block::North, false);

					
					block->addToMesh(glm::ivec3( x,y,z ) + glm::ivec3(chunk->worldPos), *newMesh, solid);
				}
				i++;
			}
		}
	}

	mesh = newMesh;
	meshRenderer.setMesh(mesh);

}

std::shared_ptr<Mesh> ChunkRenderer::getMesh()
{
	return mesh;
}

void ChunkRenderer::blocksRemoved(const std::vector<glm::ivec3> blocks)
{
	this->calculateMesh();
}
