#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

#include <vector>
#include "Camera.h"
#include "Keyboard.h"
#include "GameTime.h"

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
const float YAW = 90.0f;
const float PITCH = 0.0f;
const float SPEED = 10.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;


// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class CameraController
{
public:
    // euler Angles
    float Yaw;
    float Pitch;
    // camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;
    Camera& camera;
    glm::vec3 right;
    Key& forwardKey;
    Key& rightKey;
    Key& leftKey;
    Key& backwardsKey;

    // constructor with vectors
    CameraController(Camera& camera, float yaw = YAW, float pitch = PITCH) :
        MovementSpeed(SPEED),
        MouseSensitivity(SENSITIVITY),
        Zoom(ZOOM),
        Yaw(yaw),
        Pitch(pitch),
        camera(camera),
        forwardKey(keys[GLFW_KEY_W]),
        rightKey(keys[GLFW_KEY_D]),
        leftKey(keys[GLFW_KEY_A]),
        backwardsKey(keys[GLFW_KEY_S])
    {
        
        //updateCameraVectors();
    }


    void ProccessKeyboard();

    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard(Camera_Movement direction, float deltaTime);

    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);

    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(float yoffset);

private:
    // calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors();
};



