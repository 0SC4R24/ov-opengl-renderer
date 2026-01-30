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

private: // Data members

	GLFWwindow* m_window;

public: // Constructors

	GLFWInputManager();
	GLFWInputManager(GLFWwindow* window);

public: // Getters & Setters

	GLFWwindow* getWindow()
	{ return m_window; }

	void setWindow(GLFWwindow* window);

public: // Member functions

	void updateEvents();

protected: // Member functions

	// Initialize input
	void init() override;

private: // Static member functions

	static void windowKeyboardEvent(GLFWwindow* window, int key, int scancode, int action, int mods);

};