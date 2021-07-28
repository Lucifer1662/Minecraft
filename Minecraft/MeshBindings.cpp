#include "Mesh.h"
#include <GL/glew.h>

//std::vector<Vertex>& Mesh::getVertices()
//{
//	return vertices;
//}
//
//std::vector<unsigned int>& Mesh::getIndices()
//{
//	return  indices;
//}


void Mesh::loadToGPU()
{
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), vertices.data(), GL_STATIC_DRAW);


	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);

	dirty = false;
}

void Mesh::bind()
{

	if (dirty) {
		loadToGPU();
	}

	auto stride = sizeof(Vertex);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
	glEnableVertexAttribArray(0);


	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)sizeof(glm::vec3));
	glEnableVertexAttribArray(1);

}