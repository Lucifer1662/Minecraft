#pragma once
#include <boost/timer.hpp>



class GameTime {
	boost::timer timer;
	float deltaTime = 0.0f;	// Time between current frame and last frame
	float lastFrame = 0.0f; // Time of last frame
public:
	float getDeltaTime();
	void update();
	
};

extern GameTime mainTime;