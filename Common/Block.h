#pragma once
#include "glm/glm.hpp"
#include <bitset>
#include <memory>
#include <vector>
#include "Mesh.h"
#include <ostream>
#include <istream>


class Block
{
public:
	
	enum NeighourSide {
		North=0,
		East=1,
		South=2,
		West=3,
		Top=4,
		Bottom=5
	};
	using IsNeibhoursSolid = std::bitset<6>;

	virtual void addToMesh(glm::ivec3 pos, Mesh& mesh, IsNeibhoursSolid isNeighboursSolid) const;

	virtual bool isSolid() const;

	virtual ~Block();

	virtual size_t blockId() const = 0 ;

	virtual std::vector<unsigned char> dynamicContent() const { return {}; }

	

	static void front(glm::vec3 posf, std::vector<Vertex>& verts, std::vector<size_t>& indices, const glm::vec4& uvs);
	static void back(glm::vec3 posf, std::vector<Vertex>& verts, std::vector<size_t>& indices, const glm::vec4& uvs );
	static void left(glm::vec3 posf, std::vector<Vertex>& verts, std::vector<size_t>& indices, const glm::vec4& uvs);
	static void right(glm::vec3 posf, std::vector<Vertex>& verts, std::vector<size_t>& indices, const glm::vec4& uvs);
	static void top(glm::vec3 posf, std::vector<Vertex>& verts, std::vector<size_t>& indices, const glm::vec4& uvs);
	static void bottom(glm::vec3 posf, std::vector<Vertex>& verts, std::vector<size_t>& indices, const glm::vec4& uvs);
};


std::ostream& operator<<(std::ostream& os, const Block& block);

std::istream& operator>>(std::istream& os, Block& block);



