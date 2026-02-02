///
/// MO-OpenGL-Renderer
/// Oscar Viudez
/// Miguel Gutierrez
/// 2026
/// 

#pragma once

#include "common.h"
#include "vertex.h"
#include "Program.h"
#include "Entity.h"
#include "Mesh3D.h"

/// <summary>
/// Object Type Enumerator
/// </summary>
typedef enum
{
	MO_OBJECT_TYPE_OBJECT,
	MO_OBJECT_TYPE_CAMERA,
	MO_OBJECT_TYPE_LIGHT
} MO_ObjectType_e;

/// <summary>
/// Object Interface
/// </summary>
class Object : public Entity
{
protected: // Attributes
	Mesh3D* m_mesh = nullptr;
	MO_ObjectType_e m_type = MO_OBJECT_TYPE_OBJECT;

public: // Getters & Setters
	Mesh3D* getMesh()
	{ return m_mesh; }

	const MO_ObjectType_e& getObjectType()
	{ return m_type; }

public: // Methods
	virtual void loadDataFromFile(std::string file) = 0;
};