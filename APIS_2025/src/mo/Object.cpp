#include "Object.h"

old::Object::Object()
{
	this->objectId = objectCounter++;

	this->vertexList = {
		{
			glm::vec4(0.5f, 0.5f, 0.0f, 1.0f),
			glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)
		},
		{
			glm::vec4(-0.5f, 0.5f, 0.0f, 1.0f),
			glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)
		},
		{
			glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f),
			glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)
		},
		{
			glm::vec4(0.5f, -0.5f, 0.0f, 1.0f),
			glm::vec4(1.0f, 0.0f, 1.0f, 1.0f)
		}
	};

	this->vertexIndexList = { 2, 1, 0, 2, 0, 3 };

	this->position = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	this->rotation = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	this->scale = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	this->renderProgram = new Program();
	this->renderProgram->addShader("data/shader.vert");
	this->renderProgram->addShader("data/shader.frag");
	this->renderProgram->linkProgram();
}

glm::mat4 old::Object::getModelMatrix()
{
	glm::mat4 modelMatrix = glm::mat4(1.0f);

	modelMatrix = glm::translate(modelMatrix, glm::vec3(this->position));

	modelMatrix = glm::rotate(modelMatrix, glm::radians(this->rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(this->rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	modelMatrix = glm::rotate(modelMatrix, glm::radians(this->rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

	modelMatrix = glm::scale(modelMatrix, glm::vec3(this->scale));

	return modelMatrix;
}

void old::Object::step(float timeStep)
{
	float rotSpeed = 60.0f;
	/*float speed = 0.1f;

	if (GLFWKeyManager::keyboardState[GLFW_KEY_D]) this->position.x += speed * timeStep;
	if (GLFWKeyManager::keyboardState[GLFW_KEY_A]) this->position.x -= speed * timeStep;
	if (GLFWKeyManager::keyboardState[GLFW_KEY_W]) this->position.y += speed * timeStep;
	if (GLFWKeyManager::keyboardState[GLFW_KEY_S]) this->position.y -= speed * timeStep;*/

	if (old::GLFWKeyManager::keyboardState[GLFW_KEY_Q]) this->rotation.x += rotSpeed * timeStep;
	if (old::GLFWKeyManager::keyboardState[GLFW_KEY_E]) this->rotation.x -= rotSpeed * timeStep;
}