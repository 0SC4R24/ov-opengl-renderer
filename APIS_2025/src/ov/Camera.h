///
/// OV-OpenGL-Renderer
/// Oscar Viudez
/// Miguel Gutierrez
/// 2026
/// 

#pragma once

#include "Entity.h"

/// <summary>
/// Camera class
/// </summary>
class Camera : public Entity
{
protected: // Attributes for projection (no need of getters & setters)
	float m_fovy = 45.0f; // Field of view of camera
	float m_zNear = 0.01f; // Near plane of camera
	float m_zFar = 1000.0f; // Far plane of camera
	float m_aspectRatio = 4.0f / 3.0f; // Aspect ratio of the window (Default to 4/3, but the constructor 
										// calls the renderer for the actual aspect ratio)

protected: // Attributes
	glm::mat4 m_view;
	glm::mat4 m_projection;
	glm::vec3 m_up;
	glm::vec3 m_direction;
	glm::vec3 m_lookAt;
	OV_ProjectionType_e m_type;

public: // Getters & Setters
	glm::mat4 getViewMatrix()
	{ return m_view; }

	glm::mat4 getProjectionMatrix()
	{ return m_projection; }

	glm::vec3 getVectorUp()
	{ return m_up; }

	glm::vec3 getVectorLookAt()
	{ return m_lookAt; }

	OV_ProjectionType_e getCameraType()
	{ return m_type; }
	
	void setVectorUp(glm::vec3 up)
	{ m_up = up; }

	void setVectorLookAt(glm::vec3 lookAt)
	{ m_lookAt = lookAt; }

	void setCameraType(OV_ProjectionType_e cameraType)
	{ m_type = cameraType; }

public: // Constructor
	Camera(OV_ProjectionType_e cameraType, glm::vec3 position, glm::vec3 up, glm::vec3 lookAt);

public: // Methods
	void computeProjectionMatrix();
	void computeViewMatrix();

public: // Virtual method
	virtual void step(double deltaTime) = 0;
};