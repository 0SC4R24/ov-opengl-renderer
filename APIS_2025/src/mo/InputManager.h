///
/// MO-OpenGL-Renderer
/// Oscar Viudez
/// Miguel Gutierrez
/// 2026
/// 

#pragma once

#include "common.h"
#include <map>

/// <summary>
/// Input Manager Interface
/// </summary>
class InputManager
{

protected: // Data members

	// Key state dictionary
	static std::map<int, bool> m_keyStateDictionary;

protected: // Member functions

	// Initialize input
	virtual void init() = 0;

public: // Member functions

	virtual void updateEvents() = 0;

	virtual void setWindow(GLFWwindow* window) = 0;

	// Returns key pressed state
	static bool isKeyPressed(int keyCode);

};