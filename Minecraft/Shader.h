#pragma once
#include <string>
#include <glm/glm.hpp>

class Shader
{
	unsigned int fragement = 0;
	unsigned int vertex = 0;
	unsigned int program = 0;
public:
	bool fragmentShaderFromFile(const std::string& fileName);
	bool vertexShaderFromFile(const std::string& fileName);
	bool create();
	void bind();
	void setTextureUnit(const std::string& name, unsigned int unit);
	void setUnifromMat4(const std::string& name, const glm::mat4& matrix);
	~Shader();
};

