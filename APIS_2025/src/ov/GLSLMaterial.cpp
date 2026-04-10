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

	prepareCamera();
	prepareLights();
	prepareTextures();

	// Set blend mode
	switch (m_blendMode)
	{
	case OV_BLEND_MODE_ALPHA:
	case OV_BLEND_MODE_ADD:
	case OV_BLEND_MODE_MULTIPLY:
	case OV_BLEND_MODE_NONE:
	default:
		std::cout << "[ERROR] Blend mode activation not implemented\n";
		break;
	}
	
	// Set culling face
	if (m_culling) glEnable(GL_CULL_FACE);
	else		   glDisable(GL_CULL_FACE);
	
	// Set depth write
	glDepthMask(m_depthWrite ? GL_TRUE : GL_FALSE);
}

void GLSLMaterial::prepareCamera()
{
	std::shared_ptr<Camera> activeCamera = System::getWorld()->getActiveCamera();
	glm::mat4 M = System::getModelMatrix();
	glm::mat4 V = activeCamera->getViewMatrix();
	glm::mat4 P = activeCamera->getProjectionMatrix();
	glm::mat4 MVP = P * V * M;

	m_program->setMatrix("MVP", MVP);
	m_program->setMatrix("M", M);
}

void GLSLMaterial::prepareLights()
{
	auto lights = System::getWorld()->getLights();
	
	m_program->setInt("activeLights", std::min((int)lights.size(), 8));
	m_program->setInt("material.shiny", m_shininess);
	m_program->setFloat("ambiental", System::getWorld()->getAmbient());
	m_program->setVec4("eyePos", System::getWorld()->getActiveCamera()->getPosition());
	
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
		}
		else
		{
			m_program->setInt("lights[" + strI + "].enabled", 0);
		}
	}
}

void GLSLMaterial::prepareTextures()
{
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