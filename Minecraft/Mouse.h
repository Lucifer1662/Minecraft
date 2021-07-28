#pragma once
#include "Keyboard.h"
struct Mouse
{
	float lastX = 400, lastY = 300;
	float xoffset = 0;
	float yoffset = 0;


};

extern Mouse mouse;

extern std::array<Key, 5> mouse_buttons;

