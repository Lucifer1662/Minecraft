#include "GameTime.h"
#include <GLFW\glfw3.h>
#include <boost/timer.hpp>

float GameTime::getDeltaTime() { return 0.0001; }// deltaTime; }

void GameTime::update() {

	deltaTime = timer.elapsed();
	timer.restart();
}

GameTime mainTime = GameTime();
