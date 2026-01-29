///
/// MO-OpenGL-Renderer
/// Oscar Viudez
/// Miguel Gutierrez
/// 2026
/// 

#include "Object.h"

#include "World.h"

void World::addObject(const ObjectPtr& objectPtr)
{
	m_objectList.push_back(objectPtr);
}

void World::removeObject(const ObjectPtr& objectPtr)
{
	m_objectList.remove(objectPtr);
}

size_t World::getObjectCount() const
{
	return m_objectList.size();
}

const std::list<ObjectPtr>& World::getObjectList() const
{
	return m_objectList;
}

void World::step(const float& deltaTime)
{
	for (auto& objectPtr : m_objectList)
	{
		objectPtr->step(deltaTime);
	}
}

