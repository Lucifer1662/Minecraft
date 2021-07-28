#pragma once
#include <memory>
#include "Mesh.h"
#include "Material.h"

class MeshRenderer
{
	std::shared_ptr<Mesh> mesh;
	std::shared_ptr<Material> material;

public:
	MeshRenderer() = default;
	MeshRenderer(const MeshRenderer&) = default;
	MeshRenderer(MeshRenderer&&) = default;
	MeshRenderer& operator=(const MeshRenderer&) = default;
	MeshRenderer& operator=(MeshRenderer&&) = default;

	void setMesh(std::shared_ptr<Mesh> mesh);
	void setMaterial(std::shared_ptr<Material> material);


	void render();
};

