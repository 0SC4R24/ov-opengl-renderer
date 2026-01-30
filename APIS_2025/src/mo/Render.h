///
/// MO-OpenGL-Renderer
/// Oscar Viudez
/// Miguel Gutierrez
/// 2026
/// 

#pragma once

#include <list>
#include <memory>

// Forward declarations
class Object;

// Aliases
using ObjectPtr = std::shared_ptr<Object>;

/// <summary>
/// Render Interface
/// </summary>
class Render
{

protected: // Data members

	int m_width  { 1920 };
	int m_height { 1080 };

public: // Get - Set

	const int& getWidth() const
	{ return m_width; }

	const int& getHeight() const
	{ return m_height; }

	void setWidth(int& width)
	{ m_width = width; }

	void setHeight(int& height)
	{ m_height = height; }

public: // Member functions

	// Initialize render libraries
	virtual void init() = 0;

	// Set up object
	virtual void setupObject(std::shared_ptr<Object> objectPtr) = 0;

	// Remove object
	virtual void removeObject(std::shared_ptr<Object> objectPtr) = 0;

	// Draw object list
	virtual void drawObjects(std::list<ObjectPtr>& objectVectorPtr) = 0;

	// Draw single object
	virtual void drawObject(std::shared_ptr<Object> objectPtr) = 0;

	// Return if window should close
	virtual bool isClosed() = 0;

};
