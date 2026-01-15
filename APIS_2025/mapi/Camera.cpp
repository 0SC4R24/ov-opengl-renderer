#include "Camera.h"

Camera::Camera(glm::vec4 pos, glm::vec4 lookAt, double fovy, double aspectRatio) :
fovy(fovy), aspectRatio(aspectRatio), lookAt(lookAt), position(pos)
{
    cameraProjection = glm::perspective(glm::radians(fovy), aspectRatio, 0.01, 1000.0);
    cameraView = glm::lookAt(glm::vec3(position), glm::vec3(lookAt), glm::vec3(0, 1, 0));
}

void Camera::step(float timeStep)
{
    float speed = 1.0f;
    float rotSpeed = 60.0f;

    if (GLFWKeyManager::keyboardState[GLFW_KEY_D])
    {
        this->position.x += speed * timeStep;
        lookAt.x += speed * timeStep;
    }
    if (GLFWKeyManager::keyboardState[GLFW_KEY_A])
    {
        this->position.x -= speed * timeStep;
        lookAt.x -= speed * timeStep;
    }
    if (GLFWKeyManager::keyboardState[GLFW_KEY_W])
    {
        this->position.z -= speed * timeStep;
        lookAt.z -= speed * timeStep;
    }
    if (GLFWKeyManager::keyboardState[GLFW_KEY_S])
    {
        this->position.z += speed * timeStep;
        lookAt.z += speed * timeStep;
    }

    cameraView = glm::lookAt(glm::vec3(position), glm::vec3(lookAt), glm::vec3(0, 1, 0));
}
