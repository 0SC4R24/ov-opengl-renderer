#include "GLSLMaterial.h"
#include "System.h"
#include "World.h"
#include "Camera.h"

void GLSLMaterial::loadPrograms(std::vector<std::string> shaderFileNames)
{
	for (auto& s : shaderFileNames)
	{
		m_program->addProgram(s);
	}

	m_program->linkProgram();
}

void GLSLMaterial::prepare()
{
	m_program->use();

	std::shared_ptr<Camera> activeCamera = System::getWorld()->getActiveCamera();
	glm::mat4 M = System::getModelMatrix();
	glm::mat4 V = activeCamera->getViewMatrix();
	glm::mat4 P = activeCamera->getProjectionMatrix();
	glm::mat4 MVP = P * V * M;

	m_program->setMatrix("MVP", MVP);
}