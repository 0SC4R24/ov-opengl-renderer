///
/// MO-OpenGL-Renderer
/// Oscar Viudez
/// Miguel Gutierrez
/// 2026
/// 

#pragma once

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

	// Returns key pressed state
	static bool isKeyPressed(int keyCode);

};