///
/// MO-OpenGL-Renderer
/// Oscar Viudez
/// Miguel Gutierrez
/// 2026
/// 

#include "GLFWInputManager.h"
#include "commapi.h"
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
	auto window = System::getRender()->getWindow();

	glfwSetKeyCallback(window, windowKeyboardEvent);
	glfwSetMouseButtonCallback(window, mouseButtonEvent);
	glfwSetCursorPosCallback(window, mousePosEvent);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPos(window, 0, 0);
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

void GLFWInputManager::mousePosEvent(GLFWwindow* window, double xpos, double ypos)
{
	m_mouse.xPos = xpos;
	m_mouse.yPos = ypos;
}

void GLFWInputManager::mouseButtonEvent(GLFWwindow* window, int button, int action, int mods)
{
	switch (action)
	{
		case GLFW_PRESS:
		{
			m_mouse.buttonState[button] = true;
		}
		break;
		case GLFW_RELEASE:
		{
			m_mouse.buttonState[button] = false;
		}
		break;
		default:
		break;
	}
}
