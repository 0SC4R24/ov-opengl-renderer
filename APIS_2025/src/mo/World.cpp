///
/// MO-OpenGL-Renderer
/// Oscar Viudez
/// Miguel Gutierrez
/// 2026
/// 

#include "World.h"
#include "Object.h"
#include "Camera.h"
#include "Light.h"

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

void World::addCamera(const CameraPtr& cameraPtr)
{
	m_cameraList.push_back(cameraPtr);
}

void World::removeCamera(const CameraPtr& cameraPtr)
{
	m_cameraList.remove(cameraPtr);
}

size_t World::getCamerasCount() const
{
	return m_cameraList.size();
}

std::list<CameraPtr>& World::getCameraList()
{
	return m_cameraList;
}

CameraPtr World::getCamera(size_t index)
{
	std::list<CameraPtr>::iterator it = m_cameraList.begin();
	for (size_t i = 0; i < index; i++) it++;
	CameraPtr cam = *it;
	return cam;
}

CameraPtr World::getActiveCamera()
{
	std::list<CameraPtr>::iterator it = m_cameraList.begin();
	for (size_t i = 0; i < m_activeCamera; i++) it++;
	CameraPtr cam = *it;
	return cam;
}

int World::getActiveCameraIndex()
{
	return m_activeCamera;
}

void World::setActiveCameraIndex(int activeCamera)
{
	m_activeCamera = activeCamera;
}

std::list<LightPtr>& World::getLights()
{
	return m_lightList;
}

LightPtr World::getLight(size_t index)
{
	std::list<LightPtr>::iterator it = m_lightList.begin();
	for (size_t i = 0; i < index; i++) it++;
	LightPtr light = *it;
	return light;
}

void World::addLight(LightPtr light)
{
	m_lightList.push_back(light);
}

void World::deleteLight(size_t index)
{
	m_lightList.remove(getLight(index));
}

void World::step(const float& deltaTime)
{
	for (auto& cameraPtr : m_cameraList)
	{
		cameraPtr->step(deltaTime);
		// cameraPtr->computeProjectionMatrix();
		cameraPtr->computeViewMatrix();
	}

	for (auto& objectPtr : m_objectList)
	{
		objectPtr->step(deltaTime);
		objectPtr->computeModelMatrix();
	}
	
	for (auto& lightPtr : m_lightList)
	{
		lightPtr->step(deltaTime);
	}
}

