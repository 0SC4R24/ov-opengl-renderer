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

class Mesh3D
{
private: // Static counter
	static inline int m_MeshIDCounter = 0;

private: // Attributes
	int m_meshID;
	glm::vec4 m_colorRGBA;
	std::vector<vertex_t>* m_vVertList;

	Material* m_material = nullptr;
	std::vector<glm::uint32>* m_vTriangleIdxList;

	void loadTriangle();
	void loadSquare();

public: // Constructor
	Mesh3D();

public: // Getters & Setters
	const int& getMeshID()
	{ return m_meshID; }

	const glm::vec4& getColor()
	{ return m_colorRGBA; }

	std::vector<vertex_t>* getVertList()
	{ return m_vVertList; }

	Material* getMaterial()
	{ return m_material; }

	std::vector<glm::uint32>* getVTriangleIdxList()
	{ return m_vTriangleIdxList; }

	void setColor(glm::vec4 color);

	void setMaterial(Material* material)
	{ m_material = material; }

	void setVTriangleIdxList(std::vector<glm::uint32>* vTriangleIdxList)
	{ m_vTriangleIdxList = vTriangleIdxList; }

public: // Methods
	void addVertex(vertex_t vertex);
	void addTriangle(glm::uint32 vId1, glm::uint32 vId2, glm::uint32 vId3);
};