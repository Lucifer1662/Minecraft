#pragma once
#include <SFML/Graphics.hpp>
#include "Material.h"
#include "Shader.h"

class MaterialFactory
{
	std::shared_ptr<Shader> shader = std::make_shared<Shader>();
	std::shared_ptr<Camera> camera;
public:
	bool vertexShaderFromFile(std::string fileName);
	bool fragmentShaderFromFile(std::string fileName);
	void setCamera(std::shared_ptr<Camera> camera);

	std::shared_ptr<Material> create();
};


extern MaterialFactory materialFactory;
