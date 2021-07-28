#include "MeshRenderer.h"
#include <GL\glew.h>
#include "Mesh.h"


void MeshRenderer::setMesh(std::shared_ptr<Mesh> mesh)
{
	this->mesh = mesh;
}

void MeshRenderer::setMaterial(std::shared_ptr<Material> material)
{
	this->material = material; 
}

void MeshRenderer::render()
{
	material->apply();
	mesh->bind();
	glDrawElements(GL_TRIANGLES, mesh->getIndices().size(), GL_UNSIGNED_INT, 0);

}
