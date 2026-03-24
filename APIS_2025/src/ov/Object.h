///
/// OV-OpenGL-Renderer
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

using Mesh3DPtr = std::shared_ptr<Mesh3D>;

/// <summary>
/// Object Interface
/// </summary>
class Object : public Entity
{
protected: // Attributes
	std::vector<Mesh3DPtr> m_meshes;
	OV_ObjectType_e m_type = OV_OBJECT_TYPE_OBJECT;

public: // Getters & Setters
	Mesh3DPtr getMesh(int position)
	{ return m_meshes[position]; }

	std::vector<Mesh3DPtr>& getMeshes()
	{ return m_meshes; }

	void addMesh(Mesh3DPtr mesh)
	{ m_meshes.push_back(mesh); }

	const OV_ObjectType_e& getObjectType()
	{ return m_type; }

public: // Methods

	virtual void loadDataFromMshFile(std::string file) = 0;
};