///
/// MO-OpenGL-Renderer
/// Oscar Viudez
/// Miguel Gutierrez
/// 2026
/// 

#include "GLFWInputManager.h"
#include "System.h"

GLFWInputManager::GLFWInputManager()
{
	init();
}

void GLFWInputManager::updateEvents()
{
	glfwPollEvents();
}

void GLFWInputManager::init()
{
	glfwSetKeyCallback(System::getRender()->getWindow(), windowKeyboardEvent);
}

void GLFWInputManager::windowKeyboardEvent(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	switch (action)
	{
		case GLFW_PRESS:
		{
			m_keyStateDictionary[key] = true;
		} 
		break;
		case GLFW_RELEASE:
		{
			m_keyStateDictionary[key] = false;
		}
		break;
		default:
		break;
	}
}
