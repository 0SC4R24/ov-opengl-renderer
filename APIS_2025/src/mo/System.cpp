#include "System.h"
#include "World.h"
#include "Render.h"
#include "FactoryEngine.h"

RenderPtr System::getRender()
{
	return m_render;
}

InputManagerPtr System::getInputManager()
{
	return m_inputManager;
}

WorldPtr System::getWorld()
{
	return m_world;
}

bool System::getEnd()
{
	return m_end;
}

glm::mat4 System::getModelMatrix()
{
	return m_modelMatrix;
}

void System::setModelMatrix(glm::mat4 modelMatrix)
{
	m_modelMatrix = modelMatrix;
}

void System::initSystem()
{
	FactoryEngine::setRenderEngineType(MO_RENDER_ENGINE_TYPE_GL4);
	FactoryEngine::setInputManagerType(MO_INPUT_MANAGER_TYPE_GLFW);

	m_render = FactoryEngine::getNewRender();
	m_inputManager = FactoryEngine::getNewInputManager();
}

void System::addObject(ObjectPtr obj)
{
	m_world->addObject(obj);
}

void System::exit()
{
	m_end = true;
}

void System::mainLoop()
{
	for (auto& obj : m_world->getObjectList())
	{
		m_render->setupObject(obj);
	}

	while (!m_end)
	{
		newTime = static_cast<float>(glfwGetTime());
		deltaTime = newTime - lastTime;
		lastTime = newTime;

		m_world->step(deltaTime);

		m_render->drawObjects(m_world->getObjectList());
	}
}
