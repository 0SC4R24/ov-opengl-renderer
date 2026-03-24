///
/// OV-OpenGL-Renderer
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
/// Class acting as a factory for different rendering backends
/// </summary>
static class FactoryEngine
{
protected: // Static data members
	static inline OV_InputManagerType_e m_selectedInputManager;
	static inline OV_RenderEngineType_e m_selectedRenderEngine;
	static inline std::shared_ptr<Render> m_render;
	
	static inline int m_width = 640;
	static inline int m_height = 480;
	static inline std::string m_windowName = "MO OpenGL Renderer v5.0";

public: // Getters & Setters
	static OV_InputManagerType_e getInputManagerType()
	{ return m_selectedInputManager; }

	static OV_RenderEngineType_e getRenderEngineType()
	{ return m_selectedRenderEngine; }
	
	static void setParameters(std::string window_name, int width, int height);

	static void setInputManagerType(OV_InputManagerType_e selectedInputManagerType)
	{ m_selectedInputManager = selectedInputManagerType; }

	static void setRenderEngineType(OV_RenderEngineType_e selectedRenderEngineType)
	{ m_selectedRenderEngine = selectedRenderEngineType; }

public: // Public static methods
	static std::shared_ptr<Render> getNewRender();
	static std::shared_ptr<InputManager> getNewInputManager();
	static std::shared_ptr<Material> getNewMaterial();
	static std::shared_ptr<Texture> getNewTexture();
	static bool isClosed();
};