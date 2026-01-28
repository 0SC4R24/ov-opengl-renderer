#include "Mesh3D.h"

Mesh3D::Mesh3D()
{
	m_meshID = m_ObjectCounter++;
	m_colorRGBA = glm::vec4(0, 0, 0, 1);
	
	m_vVertList->clear();
	m_vTriangleIdxList->clear();
}

void Mesh3D::addVertex(vertex_t vertex)
{
	m_vVertList->push_back(vertex);
}

void Mesh3D::addTriangle(glm::uint32 vId1, glm::uint32 vId2, glm::uint32 vId3)
{
	m_vTriangleIdxList->push_back(vId1);
	m_vTriangleIdxList->push_back(vId2);
	m_vTriangleIdxList->push_back(vId3);
}
