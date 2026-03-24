///
/// OV-OpenGL-Renderer
/// Oscar Viudez
/// Miguel Gutierrez
/// 2026
/// 

#pragma once

#include "common.h"
#include "FactoryEngine.h"

// Forward declarations
class Render;
class InputManager;
class World;
class Object;

// Aliases
using RenderPtr = std::shared_ptr<Render>;
using InputManagerPtr = std::shared_ptr<InputManager>;
using WorldPtr = std::shared_ptr<World>;
using ObjectPtr = std::shared_ptr<Object>;

/// <summary>
/// Class system to rule all execution
/// </summary>
class System
{
private: // Attributes
	static inline RenderPtr m_render;
	static inline InputManagerPtr m_inputManager;
	static inline WorldPtr m_world;
	static inline bool m_end;

	static inline float m_deltaTime, m_newTime, m_lastTime;

	static inline glm::mat4 m_modelMatrix;

public: // Getters & Setters
	static RenderPtr getRender();
	static InputManagerPtr getInputManager();
	static WorldPtr getWorld();
	static bool getEnd();
	static glm::mat4 getModelMatrix();

	static void setParameters(std::string window_name = "OV OpenGL Renderer v5.0", int width = 640, int height = 480);
	static void setModelMatrix(glm::mat4 modelMatrix);

public: // Static methods
	static void initSystem(OV_RenderEngineType_e renderEngineType, OV_InputManagerType_e inputManagerType);
	static void addObject(ObjectPtr obj);
	static void exit();
	static void mainLoop();
};