///
/// OV-OpenGL-Renderer
/// Oscar Viudez
/// Miguel Gutierrez
/// 2026
/// 

#pragma once

#include <string_view>
#include <map>

#include "common.h"
#include "ov/BufferObject.h"
#include "ov/Render.h"
#include "ov/Camera.h"

class GL4Render : public Render
{

private: // Const data members

	static constexpr int OV_GL_MAJOR_VERSION = 4;
	static constexpr int OV_GL_MINOR_VERSION = 0;

	static inline std::string WINDOW_NAME = "OV OpenGL Renderer v5.0";

private: // Data members

	std::map<int, bufferObject_t> m_bufferObjectMap;

public: // Constructors & Destructor

	GL4Render(std::string windowName, const int& width, const int& height);

	~GL4Render();

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

	// Clear buffers
	void clearBuffers() override;
	
	// Swap buffers
	void swapBuffers() override;
	
	// Render if window should close
	bool isClosed() override;

private: // Member functions

	GLFWwindow* createGLFWWindow(const int& width, const int& height);
};