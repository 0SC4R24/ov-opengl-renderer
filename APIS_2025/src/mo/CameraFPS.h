///
/// MO-OpenGL-Renderer
/// Oscar Viudez
/// Miguel Gutierrez
/// 2026
/// 

#pragma once

#include "mo/Camera.h"

class CameraFPS : public Camera
{

private: // Data members

	float yaw;
	float pitch;

	float m_movementSpeed;
	float m_rotationSpeed;

	glm::vec2 m_mouseLastPosition;

public: // Constructors

	CameraFPS(MO_ProjectionType_e cameraType, glm::vec3 position, glm::vec3 up, glm::vec3 lookAt);

public: // Member functions

	void move_camera_x_axis(float value, double delta);
	void move_camera_z_axis(float value, double delta);
	void move_camera_y_axis(float value, double delta);

	void rotate_camera(glm::vec2 positionDifference, double delta);

	virtual void step(double deltaTime) override;

};

