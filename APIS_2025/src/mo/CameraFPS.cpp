///
/// MO-OpenGL-Renderer
/// Oscar Viudez
/// Miguel Gutierrez
/// 2026
/// 

#include "mo/System.h"

#include "CameraFPS.h"

CameraFPS::CameraFPS(MO_ProjectionType_e cameraType, glm::vec3 position, glm::vec3 up, glm::vec3 lookAt)
	: Camera(cameraType, position, up, lookAt)
{
	m_movementSpeed = 10;
	m_rotationSpeed = 1;

	m_direction = glm::normalize(lookAt - position);
	yaw = glm::degrees(std::atan2(m_direction.z,m_direction.x));
	pitch = glm::degrees(glm::asin(m_direction.y));

	m_mouseLastPosition = glm::vec2(0, 0);
}


void CameraFPS::move_camera_x_axis(float value, double delta)
{
	// Get forward and right
	glm::vec3 right = glm::normalize(glm::cross(m_direction, m_up));

	// vec3 position
	glm::vec3 position = glm::vec3(m_position) - right * value * m_movementSpeed * (float)delta;

	// Set vec4 position
	setPosition(glm::vec4(position, 1.0f));
	setVectorLookAt(glm::vec3(m_position) + m_direction);
}

void CameraFPS::move_camera_z_axis(float value, double delta)
{
	// vec3 position
	glm::vec3 position = glm::vec3(m_position) + m_direction * value * m_movementSpeed * (float)delta;

	// Set vec4 position
	setPosition(glm::vec4(position, 1.0f));
	setVectorLookAt(glm::vec3(m_position) + m_direction);
}

void CameraFPS::rotate_camera(glm::vec2 positionDifference, double delta)
{
	yaw += positionDifference.x * 0.1f;
	pitch += -positionDifference.y * 0.1f;

	if (pitch > 89.0f)
	{ pitch = 89.0f; }
	if (pitch < -89.0f)
	{ pitch = -89.0f; }

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	m_direction = glm::normalize(direction);
	std::cout << m_direction.x << " " << m_direction.y << " " << m_direction.z << std::endl;

}

void CameraFPS::step(double deltaTime)
{
	auto inputManager = System::getInputManager();
	glm::vec2 currentMousePosition = inputManager->getMousePosition();
	glm::vec2 positionDifference = currentMousePosition - m_mouseLastPosition;

	m_mouseLastPosition = currentMousePosition;

	std::cout << positionDifference.x << " " << positionDifference.y << std::endl;

	// Move
	float xAxis = 0;
	float zAxis = 0;

	if (inputManager->isKeyPressed(GLFW_KEY_W)) ++zAxis;
	if (inputManager->isKeyPressed(GLFW_KEY_S)) --zAxis;
	if (inputManager->isKeyPressed(GLFW_KEY_D)) --xAxis;
	if (inputManager->isKeyPressed(GLFW_KEY_A)) ++xAxis;

	rotate_camera(positionDifference, deltaTime);

	move_camera_x_axis(xAxis, deltaTime);
	move_camera_z_axis(zAxis, deltaTime);

	computeViewMatrix();
}
