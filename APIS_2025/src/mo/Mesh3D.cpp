#include "Mesh3D.h"

#include "FactoryEngine.h"

void Mesh3D::loadTriangle()
{
	m_vVertList = new std::vector<vertex_t>
	{
		{
			glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f),
			glm::vec4(0.5f, 0.0f, 0.0f, 1.0f)
		},
		{
			glm::vec4(0.5f, -0.5f, 0.0f, 1.0f),
			glm::vec4(0.0f, 0.5f, 0.0f, 1.0f)
		},
		{
			glm::vec4(0.0f, 0.5f, 0.0f, 1.0f),
			glm::vec4(0.0f, 0.0f, 0.5f, 1.0f)
		}
	};

	m_vTriangleIdxList = new std::vector<glm::uint32>{ 0, 1, 2 };
}

void Mesh3D::loadSquare()
{
	m_vVertList = new std::vector<vertex_t>
	{
		{
			glm::vec4(0.5f, 0.5f, 0.0f, 1.0f),
			glm::vec4(0.5f, 0.0f, 0.0f, 1.0f)
		},
		{
			glm::vec4(-0.5f, 0.5f, 0.0f, 1.0f),
			glm::vec4(0.0f, 0.5f, 0.0f, 1.0f)
		},
		{
			glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f),
			glm::vec4(0.0f, 0.0f, 0.5f, 1.0f)
		},
		{
			glm::vec4(0.5f, -0.5f, 0.0f, 1.0f),
			glm::vec4(0.5f, 0.0f, 0.5f, 1.0f)
		}
	};

	m_vTriangleIdxList = new std::vector<glm::uint32>{ 2, 1, 0, 2, 0, 3 };
}

Mesh3D::Mesh3D()
{
	m_meshID = m_MeshIDCounter++;
	
	loadTriangle();

	m_material = FactoryEngine::getNewMaterial();
	m_material->loadPrograms({ "data/shader.vert", "data/shader.frag" });
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
