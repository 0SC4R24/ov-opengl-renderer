#include "FactoryEngine.h"
#include "GL4Render.h"
#include "GLFWInputManager.h"
#include "GLSLMaterial.h"
#include "GLTexture.h"

void FactoryEngine::setParameters(std::string window_name, int width, int height)
{
	m_windowName = window_name;
	m_width = width;
	m_height = height;
}

std::shared_ptr<Render> FactoryEngine::getNewRender()
{
	switch (m_selectedRenderEngine)
	{
	case OV_RENDER_ENGINE_TYPE_GL4:
		m_render = std::make_shared<GL4Render>(m_windowName, m_width, m_height);
		return m_render;
	default:
		std::cerr << "[ERROR] Selected Render Engine Not Found\n";
		break;
	}
}

std::shared_ptr<InputManager> FactoryEngine::getNewInputManager()
{
	switch (m_selectedInputManager)
	{
	case OV_INPUT_MANAGER_TYPE_GLFW:
		return std::make_shared<GLFWInputManager>();
	default:
		std::cerr << "[ERROR] Selected Input Manager Not Found\n";
		break;
	}
}

std::shared_ptr<Material> FactoryEngine::getNewMaterial()
{
	switch (m_selectedRenderEngine)
	{
	case OV_RENDER_ENGINE_TYPE_GL4:
		return std::make_shared<GLSLMaterial>();
	default:
		std::cerr << "[ERROR] No material found for Render Engine type OpenGL" << (m_selectedRenderEngine + 1) << "\n";
		break;
	}
}

std::shared_ptr<Texture> FactoryEngine::getNewTexture()
{
	switch (m_selectedRenderEngine)
	{
	case OV_RENDER_ENGINE_TYPE_GL4:
		return std::make_shared<GLTexture>();
	default:
		std::cerr << "[ERROR] No texture found for Render Engine type OpenGL" << (m_selectedRenderEngine + 1) << "\n";
		break;
	}
}

bool FactoryEngine::isClosed()
{
	return m_render->isClosed();
}
