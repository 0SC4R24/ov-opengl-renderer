#include "CameraKeyboard.h"

#include "System.h"

void CameraKeyboard::step(double deltaTime)
{
    float speed = 1.5f * (float) deltaTime;
    float rotationSpeed = 2.0f * (float) deltaTime;

    auto inputManager = System::getInputManager();

    glm::vec3 forward = glm::normalize(m_lookAt - glm::vec3(m_position));
    glm::vec3 right = glm::normalize(glm::cross(forward, m_up));

    if (inputManager->isKeyPressed(GLFW_KEY_UP))
    { 
        glm::vec3 direction = m_lookAt - glm::vec3(m_position);
        float angle = rotationSpeed;
        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), angle, right);
        glm::vec3 newDirection = glm::vec3(rotation * glm::vec4(direction, 0.0f));
        m_lookAt = glm::vec3(m_position) + newDirection;
    }
    if (inputManager->isKeyPressed(GLFW_KEY_DOWN)) 
    {
        glm::vec3 direction = m_lookAt - glm::vec3(m_position);
        float angle = -rotationSpeed;
        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), angle, right);
        glm::vec3 newDirection = glm::vec3(rotation * glm::vec4(direction, 0.0f));
        m_lookAt = glm::vec3(m_position) + newDirection;
    }
    if (inputManager->isKeyPressed(GLFW_KEY_LEFT)) 
    {
        glm::vec3 direction = m_lookAt - glm::vec3(m_position);
        float angle = rotationSpeed;
        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), angle, m_up);
        glm::vec3 newDirection = glm::vec3(rotation * glm::vec4(direction, 0.0f));
        m_lookAt = glm::vec3(m_position) + newDirection;
    }
    if (inputManager->isKeyPressed(GLFW_KEY_RIGHT)) 
    {
        glm::vec3 direction = m_lookAt - glm::vec3(m_position);
        float angle = -rotationSpeed;
        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), angle, m_up);
        glm::vec3 newDirection = glm::vec3(rotation * glm::vec4(direction, 0.0f));
        m_lookAt = glm::vec3(m_position) + newDirection;
    }

    forward = glm::normalize(m_lookAt - glm::vec3(m_position));
    right = glm::normalize(glm::cross(forward, m_up));

    m_direction = glm::vec4(0);
    
    if (inputManager->isKeyPressed(GLFW_KEY_W)) m_direction += glm::vec4(forward, 0.0f);
    if (inputManager->isKeyPressed(GLFW_KEY_S)) m_direction -= glm::vec4(forward, 0.0f);
    if (inputManager->isKeyPressed(GLFW_KEY_D)) m_direction += glm::vec4(right, 0.0f);
    if (inputManager->isKeyPressed(GLFW_KEY_A)) m_direction -= glm::vec4(right, 0.0f);
    if (inputManager->isKeyPressed(GLFW_KEY_SPACE)) m_direction += glm::vec4(m_up, 0.0f);
    if (inputManager->isKeyPressed(GLFW_KEY_LEFT_SHIFT)) m_direction -= glm::vec4(m_up, 0.0f);

    if (glm::length(m_direction) > 0.0f) m_direction = glm::normalize(m_direction) * speed;

    glm::vec3 oldPosition = glm::vec3(m_position);
    m_position += m_direction + m_velocity;
    glm::vec3 displacement = glm::vec3(m_position) - oldPosition;
    m_lookAt += displacement;

    computeViewMatrix();
}