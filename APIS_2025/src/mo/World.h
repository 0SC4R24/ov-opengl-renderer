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
class old::Object;

// Aliases
using ObjectPtr = std::shared_ptr<old::Object>;

class World
{	

private: // Data members

	std::list<ObjectPtr> m_objectList;

public: // Constructors

	World() = default;

public: // Member functions

	void addObject(const ObjectPtr& objectPtr);

	void removeObject(const ObjectPtr& objectPtr);

	size_t getObjectCount() const;

	const std::list<ObjectPtr>& getObjectList() const;

	void step(const float& deltaTime);

};
