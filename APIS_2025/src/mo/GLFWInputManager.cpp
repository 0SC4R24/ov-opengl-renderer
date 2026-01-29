///
/// MO-OpenGL-Renderer
/// Oscar Viudez
/// Miguel Gutierrez
/// 2026
/// 

#include "GLFWInputManager.h"

GLFWInputManager::GLFWInputManager(GLFWwindow* window)
	: m_window{ window }
{ 
	init();
}

void GLFWInputManager::updateEvents()
{
	glfwPollEvents();
}

void GLFWInputManager::init()
{
	glfwSetKeyCallback(m_window, windowKeyboardEvent);
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
