#pragma once
#include <array>
struct Key {
	bool heldDown = false;
	bool pressed = false;
	bool released = false;
};

extern std::array<Key, 300> keys;

