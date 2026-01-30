#include "FactoryEngine.h"
#include "GL4Render.h"
#include "GLFWInputManager.h"
#include "GLSLMaterial.h"

MO_InputManagerType_e FactoryEngine::m_selectedInputManager = MO_INPUT_MANAGER_TYPE_GLFW;
MO_RenderEngineType_e FactoryEngine::m_selectedRenderEngine = MO_RENDER_ENGINE_TYPE_GL4;
std::shared_ptr<Render> FactoryEngine::m_render = nullptr;

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

std::shared_ptr<Material> FactoryEngine::getNewMaterial()
{
	switch (m_selectedRenderEngine)
	{
	case MO_RENDER_ENGINE_TYPE_GL4:
		return std::make_shared<GLSLMaterial>();
	default:
		std::cerr << "[ERROR] No material found for Render Engine type OpenGL" << (m_selectedRenderEngine + 1) << "\n";
		break;
	}
}

bool FactoryEngine::isClosed()
{
	return m_render->isClosed();
}
