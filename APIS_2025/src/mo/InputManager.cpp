///
/// MO-OpenGL-Renderer
/// Oscar Viudez
/// Miguel Gutierrez
/// 2026
/// 

#include "InputManager.h"

std::map <int, bool> InputManager::m_keyStateDictionary;

glm::vec2 InputManager::getMousePosition()
{
	return glm::vec2(m_mouse.xPos, m_mouse.yPos);
}

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
