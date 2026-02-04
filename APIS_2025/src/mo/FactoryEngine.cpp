#include "FactoryEngine.h"
#include "GL4Render.h"
#include "GLFWInputManager.h"
#include "GLSLMaterial.h"
#include "GLTexture.h"

std::shared_ptr<Render> FactoryEngine::getNewRender()
{
	switch (m_selectedRenderEngine)
	{
	case MO_RENDER_ENGINE_TYPE_GL4:
		m_render = std::make_shared<GL4Render>(640, 480);
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
	case MO_INPUT_MANAGER_TYPE_GLFW:
		return std::make_shared<GLFWInputManager>();
	default:
		std::cerr << "[ERROR] Selected Input Manager Not Found\n";
		break;
	}
}

Material* FactoryEngine::getNewMaterial()
{
	switch (m_selectedRenderEngine)
	{
	case MO_RENDER_ENGINE_TYPE_GL4:
		return new GLSLMaterial();
	default:
		std::cerr << "[ERROR] No material found for Render Engine type OpenGL" << (m_selectedRenderEngine + 1) << "\n";
		break;
	}
}

std::shared_ptr<Texture> FactoryEngine::getNewTexture()
{
	switch (m_selectedRenderEngine)
	{
	case MO_RENDER_ENGINE_TYPE_GL4:
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
