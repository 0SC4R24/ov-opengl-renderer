///
/// MO-OpenGL-Renderer
/// Oscar Viudez
/// Miguel Gutierrez
/// 2026
/// 

#pragma once

#include <memory>

#include "InputManager.h"
#include "Render.h"

/// <summary>
/// Class acting as a factory for different rendering backends
/// </summary>
class FactoryEngine
{

public: // Static data members

	static std::shared_ptr<InputManager> selectedInputManager;
	static std::shared_ptr<Render> selectedRenderEngine;

};
