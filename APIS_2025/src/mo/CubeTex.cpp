#include "CubeTex.h"

#include "FactoryEngine.h"
#include "Mesh3D.h"
#include "GLTexture.h"

CubeTex::CubeTex()
{
	m_position = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	m_rotation = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	m_scale = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	m_type = MO_OBJECT_TYPE_OBJECT;

	Mesh3D* mesh1 = new Mesh3D();
	Mesh3D* mesh2 = new Mesh3D();

	// Mesh 1 - Front face
	mesh1->addVertex({
		glm::vec4(0.5f, 0.5f, 0.5f, 1.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
		glm::vec2(1, 1)
		});
	mesh1->addVertex({
		glm::vec4(-0.5f, 0.5f, 0.5f, 1.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
		glm::vec2(0, 1)
		});
	mesh1->addVertex({
		glm::vec4(-0.5f, -0.5f, 0.5f, 1.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
		glm::vec2(0, 0)
		});
	mesh1->addVertex({
		glm::vec4(0.5f, -0.5f, 0.5f, 1.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
		glm::vec2(1, 0)
		});

	// Mesh 1 - Back face
	mesh1->addVertex({
		glm::vec4(0.5f, 0.5f, -0.5f, 1.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
		glm::vec2(0, 1)
		});
	mesh1->addVertex({
		glm::vec4(-0.5f, 0.5f, -0.5f, 1.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
		glm::vec2(1, 1)
		});
	mesh1->addVertex({
		glm::vec4(-0.5f, -0.5f, -0.5f, 1.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
		glm::vec2(1, 0)
		});
	mesh1->addVertex({
		glm::vec4(0.5f, -0.5f, -0.5f, 1.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
		glm::vec2(0, 0)
		});

	// Mesh 2 - Top face
	mesh2->addVertex({
		glm::vec4(0.5f, 0.5f, -0.5f, 1.0f),   // Back-right
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
		glm::vec2(1, 1)
		});
	mesh2->addVertex({
		glm::vec4(-0.5f, 0.5f, -0.5f, 1.0f),  // Back-left
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
		glm::vec2(0, 1)
		});
	mesh2->addVertex({
		glm::vec4(-0.5f, 0.5f, 0.5f, 1.0f),   // Front-left
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
		glm::vec2(0, 0)
		});
	mesh2->addVertex({
		glm::vec4(0.5f, 0.5f, 0.5f, 1.0f),    // Front-right
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
		glm::vec2(1, 0)
		});

	// Mesh 2 - Bottom face
	mesh2->addVertex({
		glm::vec4(0.5f, -0.5f, 0.5f, 1.0f),   // Front-right
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
		glm::vec2(1, 1)
		});
	mesh2->addVertex({
		glm::vec4(-0.5f, -0.5f, 0.5f, 1.0f),  // Front-left
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
		glm::vec2(0, 1)
		});
	mesh2->addVertex({
		glm::vec4(-0.5f, -0.5f, -0.5f, 1.0f), // Back-left
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
		glm::vec2(0, 0)
		});
	mesh2->addVertex({
		glm::vec4(0.5f, -0.5f, -0.5f, 1.0f),  // Back-right
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
		glm::vec2(1, 0)
		});

	// Front face
	mesh1->addTriangle(2, 1, 0);
	mesh1->addTriangle(2, 0, 3);

	// Back face
	mesh1->addTriangle(4, 5, 6);
	mesh1->addTriangle(4, 6, 7);

	// Right face
	mesh1->addTriangle(3, 0, 4);
	mesh1->addTriangle(3, 4, 7);

	// Left face
	mesh1->addTriangle(6, 5, 1);
	mesh1->addTriangle(6, 1, 2);

	// Top face
	mesh2->addTriangle(0, 1, 2);
	mesh2->addTriangle(0, 2, 3);

	// Bottom face
	mesh2->addTriangle(4, 5, 6);
	mesh2->addTriangle(4, 6, 7);

	auto texture1 = FactoryEngine::getNewTexture();
	texture1->load("data/cubeTextures/top.png");

	auto texture2 = FactoryEngine::getNewTexture();
	texture2->load("data/cubeTextures/front.png");

	mesh1->getMaterial()->setColorTexture(texture1);
	mesh2->getMaterial()->setColorTexture(texture2);

	m_meshes.push_back(mesh1);
	m_meshes.push_back(mesh2);

	computeModelMatrix();
}