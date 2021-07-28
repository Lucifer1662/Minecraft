#include "MaterialFactory.h"

bool MaterialFactory::vertexShaderFromFile(std::string fileName)
{
	return shader->vertexShaderFromFile("assets\\shaders\\" + fileName);
}

bool MaterialFactory::fragmentShaderFromFile(std::string fileName)
{
	return shader->fragmentShaderFromFile("assets\\shaders\\" + fileName);
}

void MaterialFactory::setCamera(std::shared_ptr<Camera> camera)
{
	this->camera = camera;
}

std::shared_ptr<Material> MaterialFactory::create()
{
	shader->create();
	auto material = std::make_shared<Material>(shader);
	material->setCamera(camera);
	return material;
}


MaterialFactory materialFactory = MaterialFactory();
