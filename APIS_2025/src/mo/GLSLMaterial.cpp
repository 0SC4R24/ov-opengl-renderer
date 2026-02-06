#include "GLSLMaterial.h"
#include "System.h"
#include "World.h"
#include "Camera.h"
#include "GLTexture.h"
#include "Light.h"

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
	
	auto lights = System::getWorld()->getLights();
	
	m_program->setInt("activeLights", lights.size());
	
	m_program->setInt("material.shiny", m_shininess);
	
	for (size_t i = 0; i < lights.size(); i++)
	{
		auto light = System::getWorld()->getLight(i);
		std::string strI = std::to_string(i);
		
		if (light != nullptr)
		{
			m_program->setVec4("lights[" + strI + "].position", light->getPosition());
			m_program->setVec4("lights[" + strI + "].color", light->getColor());
			m_program->setVec4("lights[" + strI + "].direction", light->getDirection());
			m_program->setInt("lights[" + strI + "].type", light->getType());
			m_program->setInt("lights[" + strI + "].enabled", light->isEnabled());
			
			m_program->setVec4("eyePos", activeCamera->getPosition());
		}
		else
		{
			m_program->setInt("lights[" + strI + "].enabled", 0);
		}
	}
	
	if (m_colorTexture != nullptr)
	{
		auto glTexture = std::dynamic_pointer_cast<GLTexture>(m_colorTexture);
		glTexture->update();

		m_program->setColorTextureEnable();
		m_program->bindColorTextureSampler(glTexture->getGLTextureID(), m_colorTexture);
	}
	else
	{
		m_program->setColorTextureDisable();
	}
}