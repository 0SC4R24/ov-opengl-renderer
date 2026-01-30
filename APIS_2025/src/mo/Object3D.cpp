#include "Object3D.h"

Object3D::Object3D()
{
	m_position = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	m_rotation = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	m_scale = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_type = MO_OBJECT_TYPE_OBJECT;

	computeModelMatrix();

	m_mesh = new Mesh3D();
}

void Object3D::loadDataFromFile(std::string file)
{
	// TODO: Functionality will be added in a future version.
}

void Object3D::step(double deltaTime)
{
	// TODO: Change with new Input Manager
	float rotSpeed = 60.0f;

	if (old::GLFWKeyManager::keyboardState[GLFW_KEY_Q]) m_rotation.x += rotSpeed * deltaTime;
	if (old::GLFWKeyManager::keyboardState[GLFW_KEY_E]) m_rotation.x -= rotSpeed * deltaTime;
}