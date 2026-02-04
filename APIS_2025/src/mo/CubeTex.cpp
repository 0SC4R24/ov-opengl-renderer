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

	Mesh3D* mesh = new Mesh3D();

	mesh->addVertex({
		glm::vec4(1.0f, 1.0f, 0.0f, 1.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
		glm::vec2(1, 1)
		});
	mesh->addVertex({
		glm::vec4(-1.0f, 1.0f, 0.0f, 1.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
		glm::vec2(0, 1)
		});
	mesh->addVertex({
		glm::vec4(-1.0f, -1.0f, 0.0f, 1.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
		glm::vec2(0, 0)
		});
	mesh->addVertex({
		glm::vec4(1.0f, -1.0f, 0.0f, 1.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
		glm::vec2(1, 0)
		});

	mesh->addTriangle(2, 1, 0);
	mesh->addTriangle(2, 0, 3);

	auto texture = FactoryEngine::getNewTexture();
	texture->load("data/cubeTextures/top.png");
	mesh->getMaterial()->setColorTexture(texture);

	m_meshes.push_back(mesh);

	computeModelMatrix();
}