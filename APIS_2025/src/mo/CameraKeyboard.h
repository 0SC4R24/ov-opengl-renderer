///
/// MO-OpenGL-Renderer
/// Oscar Viudez
/// Miguel Gutierrez
/// 2026
/// 

#pragma once

#include "Camera.h"

class CameraKeyboard : public Camera
{
private: // Attributes
	glm::vec4 m_velocity = glm::vec4(0);

public: // Constructor:
	CameraKeyboard(MO_ProjectionType_e cameraType, glm::vec3 position,
	glm::vec3 up, glm::vec3 lookAt) : Camera(cameraType, position, up, lookAt)
	{};

public: // Methods
	virtual void step(double deltaTime) override;
};