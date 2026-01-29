#include "GLFWKeyManager.h"

namespace old
{
	void GLFWKeyManager::initKeyManager(GLFWwindow* window)
	{
		GLFWKeyManager::window = window;

		glfwSetKeyCallback(window, GLFWKeyManager::windowKeyboardEvent);
		glfwSetCursorPosCallback(window, GLFWKeyManager::mousePosEvent);
		glfwSetMouseButtonCallback(window, GLFWKeyManager::mouseButtonEvent);

		GLFWKeyManager::setCursorPos(0, 0);
	}

	void GLFWKeyManager::windowKeyboardEvent(GLFWwindow* window, int key, int scancode, int action, int mods)
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

	void GLFWKeyManager::mousePosEvent(GLFWwindow* window, double xPos, double yPos)
	{
		mouseState.xPos = xPos;
		mouseState.yPos = yPos;
	}

	void GLFWKeyManager::mouseButtonEvent(GLFWwindow* window, int button, int action, int mods)
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

	void GLFWKeyManager::updateEvents()
	{
		glfwPollEvents();
	}

	void GLFWKeyManager::setCursorPos(double x, double y)
	{
		mouseState.xPos = x;
		mouseState.yPos = y;
		glfwSetCursorPos(window, x, y);
	}
}