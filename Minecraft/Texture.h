#pragma once
#include <string>
#include <GL/glew.h>
class Texture
{
	unsigned int textureID;

public:
	void load(std::string fileName);

	void bind(unsigned int target);
};

