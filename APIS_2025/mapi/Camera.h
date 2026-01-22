#pragma once

#include "common.h"
#include "GLFWKeyManager.h"

namespace old
{
    class Camera
    {
    public:
        glm::vec4 position;
        glm::vec4 rotation;

        glm::vec4 lookAt;

        double fovy = 90.0;
        double aspectRatio = 4.0 / 3.0;

        glm::mat4 cameraModel = glm::mat4(1);
        glm::mat4 cameraView = glm::mat4(1);
        glm::mat4 cameraProjection = glm::mat4(1);

        Camera() {};
        Camera(glm::vec4 pos, glm::vec4 lookAt, double fovy = 90.0, double aspectRatio = 4.0 / 3.0);

        void step(float timeStep);
    };
};
