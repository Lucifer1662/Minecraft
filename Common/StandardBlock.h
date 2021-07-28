#pragma once
#include "Block.h"
#include "glm/glm.hpp"
#include "Mesh.h"

struct Air : public Block
{
	virtual bool isSolid() const override
	{
		return false;
	}

	virtual ~Air()
	{
		Block::~Block();
	}

	virtual size_t blockId() const override {
		return 0;
	}

};

template<size_t id, bool IsSolid, typename Uvs>
class StandardBlock : public Block
{
public:
	virtual void addToMesh(glm::ivec3 pos, Mesh& mesh, IsNeibhoursSolid isNeighboursSolid) const override
	{
		if (IsSolid) {
			auto& verts = mesh.getVertices();
			auto& indices = mesh.getIndices();

			if (!isNeighboursSolid.test(North))
				front(pos, verts, indices, Uvs::front());
			if (!isNeighboursSolid.test(South))
				back(pos, verts, indices, Uvs::back());
			if (!isNeighboursSolid.test(East))
				left(pos, verts, indices, Uvs::left ());
			if (!isNeighboursSolid.test(West))
				right(pos, verts, indices, Uvs::right());
			if (!isNeighboursSolid.test(Top))
				top(pos, verts, indices, Uvs::top());
			if (!isNeighboursSolid.test(Bottom))
				bottom(pos, verts, indices, Uvs::bottom());
		}
	}

	virtual bool isSolid() const override
	{
		return IsSolid;
	}

	virtual ~StandardBlock()
	{
		Block::~Block();
	}

	virtual size_t blockId() const override {
		return id;
	}
};


struct DirtUvs {
	static constexpr glm::vec4 front()  { return { 3.0f / 16,1.0f / 16,4.0f / 16,0.0f / 16 }; }
	static constexpr glm::vec4 right()  { return { 3.0f / 16,1.0f / 16,4.0f / 16,0.0f / 16 }; }
	static constexpr glm::vec4 left()   { return { 3.0f / 16,1.0f / 16,4.0f / 16,0.0f / 16 }; }
	static constexpr glm::vec4 back()   { return { 3.0f / 16,1.0f / 16,4.0f / 16,0.0f / 16 }; }
	static constexpr glm::vec4 bottom() { return { 2.0f / 16,1.0f / 16,3.0f / 16,0.0f / 16 }; }
	static constexpr glm::vec4 top()    { return { 2.0f / 16,1.0f / 16,3.0f / 16,0.0f / 16 }; }
};

using Dirt = StandardBlock<1, true, DirtUvs>;



