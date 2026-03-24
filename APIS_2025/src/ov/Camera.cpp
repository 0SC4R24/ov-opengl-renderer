#include "Camera.h"

Camera::Camera(OV_ProjectionType_e cameraType, glm::vec3 position, glm::vec3 up, glm::vec3 lookAt)
{
	m_type = cameraType;
	m_position = glm::vec4(position, 1.0f);
	m_up = up;
	m_lookAt = lookAt;

	m_direction = glm::normalize(m_lookAt - position);

	computeProjectionMatrix();
	computeViewMatrix();
}

void Camera::computeProjectionMatrix()
{
	m_projection = glm::perspective(glm::radians(m_fovy), m_aspectRatio, m_zNear, m_zFar);
}

void Camera::computeViewMatrix()
{
	//m_view = glm::lookAt(glm::vec3(m_position), glm::vec3(m_lookAt), glm::vec3(m_up));
	m_view = glm::lookAt(glm::vec3(m_position), glm::vec3(m_position) + m_direction, glm::vec3(m_up));
}