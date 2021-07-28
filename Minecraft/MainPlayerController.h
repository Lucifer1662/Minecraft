#pragma once
#include <memory>
#include "Player.h"
#include "CameraController.h"
#include "WorldRenderer.h"


class MainPlayerController
{
	std::shared_ptr<Player> player;
    std::shared_ptr<Camera> camera;

    static const glm::vec3 cameraOffset;
    CameraController cameraController;
    WorldRenderer worldRenderer;

    void ProccessKeyboard();
    
    float MovementSpeed = 5;
    glm::vec2 oldDirection;

    glm::vec3 right;
    Key& forwardKey = keys[GLFW_KEY_W];
    Key& rightKey = keys[GLFW_KEY_D];
    Key& leftKey = keys[GLFW_KEY_A];
    Key& backwardsKey = keys[GLFW_KEY_S]; 


public:
    MainPlayerController(std::shared_ptr<Player> player, std::shared_ptr<Camera> camera);
    void update();	
};

