#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Shader.h"
#include "Texture.h"
#include <glm\glm.hpp>
#include "Camera.h"

class Material
{
	std::shared_ptr<Shader> shader;
	std::shared_ptr<Texture> mainTexture;
	std::shared_ptr<Camera> camera;
	
public:
	Material() = default;
	Material(std::shared_ptr<Shader> shader);
	Material(const Material&) = default;
	Material(Material&&) = default;
	virtual void apply();
	void setMainTexture(std::shared_ptr<Texture> mainTexture);
	void setCamera(const glm::mat4& matrix);
	void setCamera(std::shared_ptr<Camera> camera);

	virtual ~Material();
};

