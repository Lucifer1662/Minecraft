#include "CameraController.h"
#include "GameTime.h"

void CameraController::ProccessKeyboard() {
    float delta = mainTime.getDeltaTime();
    if (forwardKey.heldDown) {
        ProcessKeyboard(Camera_Movement::FORWARD, delta);
    }
    if (rightKey.heldDown) {
        ProcessKeyboard(Camera_Movement::RIGHT, delta);
    }
    if (backwardsKey.heldDown) {
        ProcessKeyboard(Camera_Movement::BACKWARD, delta);
    }
    if (leftKey.heldDown) {
        ProcessKeyboard(Camera_Movement::LEFT, delta);
    }

}

// processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)

void CameraController::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
    float velocity = MovementSpeed * deltaTime;
    if (direction == FORWARD)
        camera.position += camera.front * velocity;
    if (direction == BACKWARD)
        camera.position -= camera.front * velocity;
    if (direction == LEFT)
        camera.position -= right * velocity;
    if (direction == RIGHT)
        camera.position += right * velocity;
}

// processes input received from a mouse input system. Expects the offset value in both the x and y direction.

void CameraController::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw += xoffset;
    Pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
    }

    // update Front, Right and Up Vectors using the updated Euler angles
    updateCameraVectors();
}

// processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis

void CameraController::ProcessMouseScroll(float yoffset)
{
    Zoom -= (float)yoffset;
    if (Zoom < 1.0f)
        Zoom = 1.0f;
    if (Zoom > 45.0f)
        Zoom = 45.0f;
}

// calculates the front vector from the Camera's (updated) Euler Angles

void CameraController::updateCameraVectors()
{
    // calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    camera.front = glm::normalize(front);
    // also re-calculate the Right and Up vector
    right = glm::normalize(glm::cross(camera.front, glm::vec3(0, 1, 0)));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    camera.up = glm::normalize(glm::cross(right, camera.front));
}
