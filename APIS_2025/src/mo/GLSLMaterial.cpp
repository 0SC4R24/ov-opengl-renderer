#include "GLSLMaterial.h"
#include "System.h"
#include "World.h"
#include "Camera.h"
#include "GLTexture.h"

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
	m_program->setMatrix("M", M);

	m_program->setVec4("vColor", m_colorRGBA);

	if (m_colorTexture != nullptr)
	{
		auto glTexture = std::dynamic_pointer_cast<GLTexture>(m_colorTexture);
		glTexture->update();

		m_program->setColorTextureEnable();
		m_program->bindColorTextureSampler(glTexture->getGLTextureID(), m_colorTexture);
		
		// TODO: Get from material and light
		m_program->setInt("material.shiny", 70);
		
		glm::vec4 lightPos = glm::vec4(2, 2, 2, 1);
		glm::vec4 lightDir = glm::vec4(-2, -2, -2, 0);
		m_program->setVec4("light.position", lightPos);
		m_program->setVec4("light.color", glm::vec4(1, 1, 1, 1));
		m_program->setVec4("light.direction", lightDir);
		m_program->setInt("light.type", 0);
		m_program->setInt("light.enabled", 1);
		
		m_program->setVec4("eyePos", activeCamera->getPosition());
	}
	else
	{
		m_program->setColorTextureEnable();
	}
}