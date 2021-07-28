#include "Mesh.h"


void Mesh::setVertices(const std::vector<Vertex>& vertices)
{
	this->vertices = vertices;
	dirty = true;
}

void Mesh::addVertex(const Vertex& vertex)
{
	vertices.push_back(vertex);
	dirty = true;
}

void Mesh::setIndices(const std::vector<unsigned int>& indices)
{
	this->indices = indices;
	dirty = true;
}

