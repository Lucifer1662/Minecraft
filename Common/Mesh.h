#pragma once
#include <vector>
#include <glm/glm.hpp>

struct Vertex {
	glm::vec3 position;
	glm::vec2 uv;
	Vertex(glm::vec3 p, glm::vec2 uv) : position(p), uv(uv) {}
};

class Mesh
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	unsigned int vbo;
	unsigned int ebo;
	bool dirty = true;

public:
	Mesh() = default;
	Mesh(const Mesh&) = default;
	Mesh(Mesh&&) = default;

	void setVertices(const std::vector<Vertex>& vertices);
	void addVertex(const Vertex& vertex);
	void setIndices(const std::vector<unsigned int>& indices);
	std::vector<Vertex>& getVertices()
	{
		return vertices;
	}

	std::vector<unsigned int>& getIndices()
	{
		return  indices;
	}
	void loadToGPU();
	void bind();
	
};

