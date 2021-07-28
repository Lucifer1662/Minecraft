#include "Block.h"
#include "Mesh.h"
#include <iostream>

void Block::front(glm::vec3 posf, std::vector<Vertex>& verts, std::vector<size_t>& indices, const glm::vec4& uvs) {
	auto lastIndex = verts.size();
	verts.push_back({ glm::vec3(0.0f, 1.0f, 0.0f) + posf, {uvs.z,  uvs.w} });  // top right
	verts.push_back({ glm::vec3(0.0f, 0.0f, 0.0f) + posf, {uvs.z,  uvs.y} });  // bottom right
	verts.push_back({ glm::vec3(1.0f, 0.0f, 0.0f) + posf, {uvs.x,  uvs.y} });  // bottom left
	verts.push_back({ glm::vec3(1.0f, 1.0f, 0.0f) + posf, {uvs.x,  uvs.w} });   // top left

	indices.push_back(lastIndex + 0);
	indices.push_back(lastIndex + 3);
	indices.push_back(lastIndex + 1);

	indices.push_back(lastIndex + 1);
	indices.push_back(lastIndex + 3);
	indices.push_back(lastIndex + 2);
}

void Block::back(glm::vec3 posf, std::vector<Vertex>& verts, std::vector<size_t>& indices, const glm::vec4& uvs) {
	auto lastIndex = verts.size();
	verts.push_back({ glm::vec3(1.0f, 1.0f, 1.0f) + posf, {uvs.z,  uvs.w} });  // top right
	verts.push_back({ glm::vec3(1.0f, 0.0f, 1.0f) + posf, {uvs.z,  uvs.y} });  // bottom right
	verts.push_back({ glm::vec3(0.0f, 0.0f, 1.0f) + posf, {uvs.x,  uvs.y} });  // bottom left
	verts.push_back({ glm::vec3(0.0f, 1.0f, 1.0f) + posf, {uvs.x,  uvs.w} });   // top left

	
	indices.push_back(lastIndex + 0);
	indices.push_back(lastIndex + 3);
	indices.push_back(lastIndex + 1);

	indices.push_back(lastIndex + 1);
	indices.push_back(lastIndex + 3);
	indices.push_back(lastIndex + 2);
}

void Block::right(glm::vec3 posf, std::vector<Vertex>& verts, std::vector<size_t>& indices, const glm::vec4& uvs) {
	auto lastIndex = verts.size();
	verts.push_back({ glm::vec3(0.0f, 1.0f, 1.0f) + posf, {uvs.z,  uvs.w} });  // top right
	verts.push_back({ glm::vec3(0.0f, 0.0f, 1.0f) + posf, {uvs.z,  uvs.y} });  // bottom right
	verts.push_back({ glm::vec3(0.0f, 0.0f, 0.0f) + posf, {uvs.x,  uvs.y} });  // bottom left
	verts.push_back({ glm::vec3(0.0f, 1.0f, 0.0f) + posf, {uvs.x,  uvs.w} });   // top left


	indices.push_back(lastIndex + 0);
	indices.push_back(lastIndex + 3);
	indices.push_back(lastIndex + 1);

	indices.push_back(lastIndex + 1);
	indices.push_back(lastIndex + 3);
	indices.push_back(lastIndex + 2);
}

void Block::left(glm::vec3 posf, std::vector<Vertex>& verts, std::vector<size_t>& indices, const glm::vec4& uvs) {
	auto lastIndex = verts.size();
	verts.push_back({ glm::vec3(1.0f, 1.0f, 0.0f) + posf, {uvs.z,  uvs.w} });  // top right
	verts.push_back({ glm::vec3(1.0f, 0.0f, 0.0f) + posf, {uvs.z,  uvs.y} });  // bottom right
	verts.push_back({ glm::vec3(1.0f, 0.0f, 1.0f) + posf, {uvs.x,  uvs.y} });  // bottom left
	verts.push_back({ glm::vec3(1.0f, 1.0f, 1.0f) + posf, {uvs.x,  uvs.w} });   // top left


	indices.push_back(lastIndex + 0);
	indices.push_back(lastIndex + 3);
	indices.push_back(lastIndex + 1);

	indices.push_back(lastIndex + 1);
	indices.push_back(lastIndex + 3);
	indices.push_back(lastIndex + 2);
}

void Block::top(glm::vec3 posf, std::vector<Vertex>& verts, std::vector<size_t>& indices, const glm::vec4& uvs) {
	auto lastIndex = verts.size();
	verts.push_back({ glm::vec3(0.0f, 1.0f, 1.0f) + posf, {uvs.z,  uvs.w} });  // top right
	verts.push_back({ glm::vec3(0.0f, 1.0f, 0.0f) + posf, {uvs.z,  uvs.y} });  // bottom right
	verts.push_back({ glm::vec3(1.0f, 1.0f, 0.0f) + posf, {uvs.x,  uvs.y} });  // bottom left
	verts.push_back({ glm::vec3(1.0f, 1.0f, 1.0f) + posf, {uvs.x,  uvs.w} });   // top left


	indices.push_back(lastIndex + 0);
	indices.push_back(lastIndex + 3);
	indices.push_back(lastIndex + 1);

	indices.push_back(lastIndex + 1);
	indices.push_back(lastIndex + 3);
	indices.push_back(lastIndex + 2);
}

void Block::bottom(glm::vec3 posf, std::vector<Vertex>& verts, std::vector<size_t>& indices, const glm::vec4& uvs) {
	auto lastIndex = verts.size();
	verts.push_back({ glm::vec3(0.0f, 0.0f, 1.0f) + posf, {uvs.z,  uvs.w} });  // top right
	verts.push_back({ glm::vec3(0.0f, 0.0f, 0.0f) + posf, {uvs.z,  uvs.y} });  // bottom right
	verts.push_back({ glm::vec3(1.0f, 0.0f, 0.0f) + posf, {uvs.x,  uvs.y} });  // bottom left
	verts.push_back({ glm::vec3(1.0f, 0.0f, 1.0f) + posf, {uvs.x,  uvs.w} });   // top left


	indices.push_back(lastIndex + 0);
	indices.push_back(lastIndex + 1);
	indices.push_back(lastIndex + 3);

	indices.push_back(lastIndex + 1);
	indices.push_back(lastIndex + 2);
	indices.push_back(lastIndex + 3);
}


void Block::addToMesh(glm::ivec3 pos, Mesh& mesh, IsNeibhoursSolid isNeighboursSolid) const
{
}

bool Block::isSolid() const
{
	return true;
}

Block::~Block()
{
}







