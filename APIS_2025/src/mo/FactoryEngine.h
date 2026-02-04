///
/// MO-OpenGL-Renderer
/// Oscar Viudez
/// Miguel Gutierrez
/// 2026
/// 

#pragma once

#include "common.h"
#include "InputManager.h"
#include "Render.h"
#include "Material.h"

/// <summary>
/// Enum to select InputManager
/// </summary>
static enum MO_InputManagerType_e
{
	MO_INPUT_MANAGER_TYPE_GLFW
};

/// <summary>
/// Enum to select Render
/// </summary>
static enum MO_RenderEngineType_e
{
	MO_RENDER_ENGINE_TYPE_GL1,
	MO_RENDER_ENGINE_TYPE_GL2,
	MO_RENDER_ENGINE_TYPE_GL3,
	MO_RENDER_ENGINE_TYPE_GL4
};

/// <summary>
/// Class acting as a factory for different rendering backends
/// </summary>
static class FactoryEngine
{
protected: // Static data members
	static inline MO_InputManagerType_e m_selectedInputManager;
	static inline MO_RenderEngineType_e m_selectedRenderEngine;
	static inline std::shared_ptr<Render> m_render;

public: // Getters & Setters
	static MO_InputManagerType_e getInputManagerType()
	{ return m_selectedInputManager; }

	static MO_RenderEngineType_e getRenderEngineType()
	{ return m_selectedRenderEngine; }

	static void setInputManagerType(MO_InputManagerType_e selectedInputManagerType)
	{ m_selectedInputManager = selectedInputManagerType; }

	static void setRenderEngineType(MO_RenderEngineType_e selectedRenderEngineType)
	{ m_selectedRenderEngine = selectedRenderEngineType; }

public: // Public static methods
	static std::shared_ptr<Render> getNewRender();
	static std::shared_ptr<InputManager> getNewInputManager();
	static Material* getNewMaterial();
	static std::shared_ptr<Texture> getNewTexture();
	static bool isClosed();
};