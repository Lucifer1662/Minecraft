#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <vector>




// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
    // camera Attributes
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    float fov;

    // constructor with vectors
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), float fov = 45.0f, glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3  front = glm::vec3(0.0f, 0.0f, 1.0f)) :
        position(position),
        up(up),
        front(front),
        fov(fov)
    {
       
    }

    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix()
    {
        return  glm::perspective(glm::radians(fov), 1.0f, 0.001f, 100.0f) * glm::lookAt(position, position + front, up);
    }
};

