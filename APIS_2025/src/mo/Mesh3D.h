///
/// MO-OpenGL-Renderer
/// Oscar Viudez
/// Miguel Gutierrez
/// 2026
/// 

#pragma once

#include "common.h"
#include "vertex.h"
#include "Material.h"

using MaterialPtr = std::shared_ptr<Material>;

class Mesh3D
{
private: // Static counter
	static inline int m_MeshIDCounter = 0;

private: // Attributes
	int m_meshID;
	std::shared_ptr<std::vector<vertex_t>> m_vVertList;

	MaterialPtr m_material = nullptr;
	std::shared_ptr<std::vector<glm::uint32>> m_vTriangleIdxList;

	void loadTriangle();
	void loadSquare();

public: // Constructor
	Mesh3D();

public: // Getters & Setters
	const int& getMeshID()
	{ return m_meshID; }

	const std::shared_ptr<std::vector<vertex_t>>& getVertList() const
	{ return m_vVertList; }

	MaterialPtr getMaterial()
	{ return m_material; }

	const std::shared_ptr<std::vector<glm::uint32>>& getVTriangleIdxList() const
	{ return m_vTriangleIdxList; }

	void setMaterial(MaterialPtr material)
	{ m_material = material; }

	void setVertList(std::shared_ptr<std::vector<vertex_t>> vertList)
	{
		m_vVertList = vertList;
	}

	void setVTriangleIdxList(std::shared_ptr<std::vector<glm::uint32>> vTriangleIdxList)
	{ m_vTriangleIdxList = vTriangleIdxList; }

public: // Methods
	void addVertex(vertex_t vertex);
	void addTriangle(glm::uint32 vId1, glm::uint32 vId2, glm::uint32 vId3);
};