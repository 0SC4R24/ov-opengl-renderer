#include "CameraKeyboard.h"

#include "System.h"

void CameraKeyboard::step(double deltaTime)
{
    float speed = 5.0f;
    float acceleration = 10.0f;
    float deceleration = 8.0f;
    float rotationSpeed = 90.0f;

    glm::vec3 forward = glm::normalize(m_lookAt - glm::vec3(m_position));
    glm::vec3 right = glm::normalize(glm::cross(forward, m_up));

    m_direction = glm::vec4(0.0f);

    auto inputManager = System::getInputManager();
    if (inputManager->isKeyPressed(GLFW_KEY_W))
        m_direction += glm::vec4(forward, 0.0f);
    if (inputManager->isKeyPressed(GLFW_KEY_S))
        m_direction -= glm::vec4(forward, 0.0f);
    if (inputManager->isKeyPressed(GLFW_KEY_D))
        m_direction += glm::vec4(right, 0.0f);
    if (inputManager->isKeyPressed(GLFW_KEY_A))
        m_direction -= glm::vec4(right, 0.0f);
    if (inputManager->isKeyPressed(GLFW_KEY_SPACE))
        m_direction += glm::vec4(m_up, 0.0f);
    if (inputManager->isKeyPressed(GLFW_KEY_LEFT_SHIFT))
        m_direction -= glm::vec4(m_up, 0.0f);

    if (glm::length(glm::vec3(m_direction)) > 0.0f)
    {
        m_direction = glm::vec4(glm::normalize(glm::vec3(m_direction)), 0.0f);
        m_velocity += m_direction * acceleration * (float)deltaTime;
    }
    else
    {
        float currentSpeed = glm::length(glm::vec3(m_velocity));
        if (currentSpeed > 0.0f)
        {
            float newSpeed = std::max(0.0f, currentSpeed - deceleration * (float)deltaTime);
            m_velocity = glm::vec4(glm::normalize(glm::vec3(m_velocity)) * newSpeed, 0.0f);
        }
    }

    float currentSpeed = glm::length(glm::vec3(m_velocity));
    if (currentSpeed > speed)
    {
        m_velocity = glm::vec4(glm::normalize(glm::vec3(m_velocity)) * speed, 0.0f);
    }

    glm::vec3 displacement = glm::vec3(m_velocity) * (float)deltaTime;
    m_position += glm::vec4(displacement, 0.0f);

    glm::vec3 direction = glm::normalize(m_lookAt - glm::vec3(m_position));
    float distance = glm::length(m_lookAt - glm::vec3(m_position));

    if (inputManager->isKeyPressed(GLFW_KEY_LEFT))
    {
        float angle = glm::radians(rotationSpeed * (float)deltaTime);
        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), angle, m_up);
        direction = glm::vec3(rotation * glm::vec4(direction, 0.0f));
    }
    if (inputManager->isKeyPressed(GLFW_KEY_RIGHT))
    {
        float angle = glm::radians(-rotationSpeed * (float)deltaTime);
        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), angle, m_up);
        direction = glm::vec3(rotation * glm::vec4(direction, 0.0f));
    }

    if (inputManager->isKeyPressed(GLFW_KEY_UP))
    {
        float angle = glm::radians(rotationSpeed * (float)deltaTime);
        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), angle, right);
        glm::vec3 newDirection = glm::vec3(rotation * glm::vec4(direction, 0.0f));

        float dotUp = glm::dot(newDirection, m_up);
        if (dotUp < 0.95f && dotUp > -0.95f)
        {
            direction = newDirection;
        }
    }
    if (inputManager->isKeyPressed(GLFW_KEY_DOWN))
    {
        float angle = glm::radians(-rotationSpeed * (float)deltaTime);
        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), angle, right);
        glm::vec3 newDirection = glm::vec3(rotation * glm::vec4(direction, 0.0f));

        float dotUp = glm::dot(newDirection, m_up);
        if (dotUp < 0.95f && dotUp > -0.95f)
        {
            direction = newDirection;
        }
    }

    m_lookAt = glm::vec3(m_position) + direction * distance;

    computeViewMatrix();
}