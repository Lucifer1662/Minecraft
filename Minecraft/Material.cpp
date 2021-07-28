#include "Material.h"

Material::Material(std::shared_ptr<Shader> shader) : shader(shader)
{
}

void Material::apply()
{
	shader->bind();
	if (mainTexture) {
		shader->setTextureUnit("mainTexture", 0);
		mainTexture->bind(0);
	}
	setCamera(camera->GetViewMatrix());
	
}

void Material::setMainTexture(std::shared_ptr<Texture> mainTexture)
{
	this->mainTexture = mainTexture;
}

void Material::setCamera(const glm::mat4& matrix)
{
	shader->setUnifromMat4("camera", matrix);
}

void Material::setCamera(std::shared_ptr<Camera> camera)
{
	this->camera = camera;
}


Material::~Material()
{
}
