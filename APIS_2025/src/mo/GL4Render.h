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

#include "mo/Render.h"

class GL4Render : Render
{

private: // Const data members

	static constexpr int MO_GL_MAJOR_VERSION = 4;
	static constexpr int MO_GL_MINOR_VERSION = 0;

	static constexpr std::string_view WINDOW_NAME = "MO OpenGL Renderer";

private: // Data members

	GLFWwindow* m_window;

	std::map<int, bufferObject_t> m_bufferObjectMap;

public: // Constructors

	GL4Render(const int& width, const int& height);

public: // Get - Set

	GLFWwindow* getWindow()
	{ return m_window; }

public: // Member functions

	// Render init
	void init() override;

	// Render set up object
	void setupObject(std::shared_ptr<old::Object> objectPtr) override;

	// Render remove object
	void removeObject(std::shared_ptr<old::Object> objectPtr) override;

	// Render draw objects
	void drawObjects(std::vector<ObjectPtr>* objectVectorPtr) override;

private: // Member functions

	GLFWwindow* createGLFWWindow(const int& width, const int& height);
};