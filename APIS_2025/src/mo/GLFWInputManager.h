///
/// MO-OpenGL-Renderer
/// Oscar Viudez
/// Miguel Gutierrez
/// 2026
/// 

#pragma once

#include <common.h>

#include "InputManager.h"

class GLFWInputManager : public InputManager
{

public: // Constructors

	GLFWInputManager();

public: // Member functions

	void updateEvents() override;

protected: // Member functions

	// Initialize input
	void init() override;

private: // Static member functions

	static void windowKeyboardEvent(GLFWwindow* window, int key, int scancode, int action, int mods);

	static void mousePosEvent(GLFWwindow* window, double xpos, double ypos);

	static void mouseButtonEvent(GLFWwindow* window, int button, int action, int mods);

};