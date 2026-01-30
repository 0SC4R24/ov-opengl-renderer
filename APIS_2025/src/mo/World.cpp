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

std::list<ObjectPtr>& World::getObjectList()
{
	return m_objectList;
}

ObjectPtr World::getObject(size_t index)
{
	std::list<ObjectPtr>::iterator it = m_objectList.begin();
	for (size_t i = 0; i < index; i++) it++;
	ObjectPtr obj = *it;
	return obj;
}

void World::step(const float& deltaTime)
{
	for (auto& objectPtr : m_objectList)
	{
		objectPtr->step(deltaTime);
	}
}

