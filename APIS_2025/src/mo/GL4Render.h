///
/// MO-OpenGL-Renderer
/// Oscar Viudez
/// Miguel Gutierrez
/// 2026
/// 

#pragma once

#include <string_view>
#include <map>

#include "common.h"
#include "mo/BufferObject.h"
#include "mapi/Camera.h"

#include "mo/Render.h"

class GL4Render : public Render
{

private: // Const data members

	static constexpr int MO_GL_MAJOR_VERSION = 4;
	static constexpr int MO_GL_MINOR_VERSION = 0;

	static constexpr std::string_view WINDOW_NAME = "MO OpenGL Renderer";

private: // Data members

	GLFWwindow* m_window;

	old::Camera* m_camera;

	std::map<int, bufferObject_t> m_bufferObjectMap;

public: // Constructors & Destructor

	GL4Render(const int& width, const int& height);

	~GL4Render();

public: // Get - Set

	GLFWwindow* getWindow()
	{ return m_window; }

	void setCamera(old::Camera* camera)
	{ m_camera = camera; }

public: // Member functions

	// Render init
	void init() override;

	// Render set up object
	void setupObject(std::shared_ptr<Object> objectPtr) override;

	// Render remove object
	void removeObject(std::shared_ptr<Object> objectPtr) override;

	// Render draw objects
	void drawObjects(std::list<ObjectPtr>& objectVectorPtr) override;

	// Render draw object
	void drawObject(std::shared_ptr<Object> objectPtr) override;

	// Render if window should close
	bool isClosed() override;

private: // Member functions

	GLFWwindow* createGLFWWindow(const int& width, const int& height);
};