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
class Camera;
class Light;

// Aliases
using ObjectPtr = std::shared_ptr<Object>;
using CameraPtr = std::shared_ptr<Camera>;
using LightPtr = std::shared_ptr<Light>;

class World
{	

private: // Data members

	std::list<ObjectPtr> m_objectList;
	std::list<CameraPtr> m_cameraList;
	std::list<LightPtr> m_lightList;
	
	int m_activeCamera = 0;
	float ambient = 0.25f;
	
public: // Constructors

	World() = default;

public: // Member functions

	void addObject(const ObjectPtr& objectPtr);

	void removeObject(const ObjectPtr& objectPtr);

	size_t getObjectCount() const;

	std::list<ObjectPtr>& getObjectList();

	ObjectPtr getObject(size_t index);
	
	void addCamera(const CameraPtr& cameraPtr);

	void removeCamera(const CameraPtr& cameraPtr);

	size_t getCamerasCount() const;

	std::list<CameraPtr>& getCameraList();

	CameraPtr getCamera(size_t index);

	CameraPtr getActiveCamera();

	int getActiveCameraIndex();

	void setActiveCameraIndex(int activeCamera);
	
	const float getAmbient() const;
	
	void setAmbient(float ambient);
	
	std::list<LightPtr>& getLights();
	
	LightPtr getLight(size_t index);
	
	void addLight(LightPtr light);
	
	void deleteLight(size_t index);

	void step(const float& deltaTime);

};
