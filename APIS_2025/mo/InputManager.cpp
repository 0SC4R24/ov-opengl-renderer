///
/// MO-OpenGL-Renderer
/// Oscar Viudez
/// Miguel Gutierrez
/// 2026
/// 

#include "InputManager.h"

bool InputManager::isKeyPressed(int keyCode)
{
	// Return key state if found in dictionary
	auto it = m_keyStateDictionary.find(keyCode);
	if (it != m_keyStateDictionary.end())
	{
		return it->second;
	}
	return false;
}
