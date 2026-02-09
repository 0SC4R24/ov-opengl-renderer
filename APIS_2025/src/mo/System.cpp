#include "System.h"

#include <utility>
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

void System::setParameters(std::string window_name, int width, int height)
{
	FactoryEngine::setParameters(window_name, width, height);
}

void System::setModelMatrix(glm::mat4 modelMatrix)
{
	m_modelMatrix = modelMatrix;
}

void System::initSystem(MO_RenderEngineType_e renderEngineType, MO_InputManagerType_e inputManagerType)
{
	FactoryEngine::setRenderEngineType(renderEngineType);
	FactoryEngine::setInputManagerType(inputManagerType);

	// Always instantiate render first, then input manager
	m_render = FactoryEngine::getNewRender();
	m_inputManager = FactoryEngine::getNewInputManager();

	m_world = std::make_shared<World>();

	m_newTime = static_cast<float>(glfwGetTime());
	m_deltaTime = 0;
	m_lastTime = m_newTime;

	m_end = false;
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

	while (!m_end && !m_render->isClosed() && !m_inputManager->isKeyPressed(GLFW_KEY_ESCAPE))
	{
		m_newTime = static_cast<float>(glfwGetTime());
		m_deltaTime = m_newTime - m_lastTime;
		m_lastTime = m_newTime;

		m_world->step(m_deltaTime);

		m_render->drawObjects(m_world->getObjectList());

		m_inputManager->updateEvents();
	}
}
