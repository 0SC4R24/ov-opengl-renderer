///
/// OV-OpenGL-Renderer
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

protected: // Structs

	struct Mouse
	{
		double xPos;
		double yPos;
		std::map<int, bool> buttonState;
	};

protected: // Data members

	static inline Mouse m_mouse;

	// Key state dictionary
	static std::map<int, bool> m_keyStateDictionary;

protected: // Member functions

	// Initialize input
	virtual void init() = 0;

public: // Member functions

	virtual void updateEvents() = 0;

	// Returns mouse position
	static glm::vec2 getMousePosition();

	// Returns key pressed state
	static bool isKeyPressed(int keyCode);

};