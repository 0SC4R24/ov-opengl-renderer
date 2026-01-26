#include "GLFWKeyManager.h"

void old::GLFWKeyManager::initKeyManager(GLFWwindow* window)
{
	old::GLFWKeyManager::window = window;

	glfwSetKeyCallback(window, old::GLFWKeyManager::windowKeyboardEvent);
	glfwSetCursorPosCallback(window, old::GLFWKeyManager::mousePosEvent);
	glfwSetMouseButtonCallback(window, old::GLFWKeyManager::mouseButtonEvent);
	
	old::GLFWKeyManager::setCursorPos(0, 0);
}

void old::GLFWKeyManager::windowKeyboardEvent(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	switch (action)
	{
	case GLFW_PRESS:
	{
		keyboardState[key] = true;
	} break;
	case GLFW_RELEASE:
	{
		keyboardState[key] = false;
	} break;
	}
}

void old::GLFWKeyManager::mousePosEvent(GLFWwindow* window, double xPos, double yPos)
{
	mouseState.xPos = xPos;
	mouseState.yPos = yPos;
}

void old::GLFWKeyManager::mouseButtonEvent(GLFWwindow* window, int button, int action, int mods)
{
	switch (action)
	{
	case GLFW_PRESS:
	{
		mouseState.buttonState[button] = true;
	} break;
	case GLFW_RELEASE:
	{
		mouseState.buttonState[button] = false;
	} break;
	}
}

void old::GLFWKeyManager::updateEvents()
{
	glfwPollEvents();
}

void old::GLFWKeyManager::setCursorPos(double x, double y)
{
	mouseState.xPos = x;
	mouseState.yPos = y;
	glfwSetCursorPos(window, x, y);
}