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

	glm::vec4 color(1.0f, 1.0f, 1.0f, 1.0f);
	float h = 0.5f;

	auto mesh1 = std::make_shared<Mesh3D>();
	auto mesh2 = std::make_shared<Mesh3D>();

	mesh1->setMaterial(FactoryEngine::getNewMaterial());
	mesh2->setMaterial(FactoryEngine::getNewMaterial());
	
	int shininess = 70;
	mesh1->getMaterial()->setShininess(shininess);
	mesh2->getMaterial()->setShininess(shininess);

	mesh1->getMaterial()->loadPrograms({"data/shader.vert", "data/shader.frag"});
	mesh2->getMaterial()->setRenderProgram(mesh1->getMaterial()->getRenderProgram());
	
	auto addV1 = [&](const glm::vec4 &pos, const glm::vec2 &uv, const glm::vec4 &n)
	{
		mesh1->addVertex({ pos, color, uv, n });
	};
	auto addV2 = [&](const glm::vec4 &pos, const glm::vec2 &uv, const glm::vec4 &n)
	{
		mesh2->addVertex({ pos, color, uv, n });
	};

    // FRONT (Z+), in mesh1
    glm::vec4 nF(0.0f, 0.0f, 1.0f, 0.0f);
    addV1({  h,  h,  h, 1.0f }, {1, 1}, nF); // 0
    addV1({ -h,  h,  h, 1.0f }, {0, 1}, nF); // 1
    addV1({ -h, -h,  h, 1.0f }, {0, 0}, nF); // 2
    addV1({  h, -h,  h, 1.0f }, {1, 0}, nF); // 3

    // BACK (Z-), in mesh1
    glm::vec4 nB(0.0f, 0.0f, -1.0f, 0.0f);
    addV1({  h,  h, -h, 1.0f }, {0, 1}, nB); // 4
    addV1({ -h,  h, -h, 1.0f }, {1, 1}, nB); // 5
    addV1({ -h, -h, -h, 1.0f }, {1, 0}, nB); // 6
    addV1({  h, -h, -h, 1.0f }, {0, 0}, nB); // 7

    // RIGHT (X+), in mesh1
    glm::vec4 nR(1.0f, 0.0f, 0.0f, 0.0f);
    addV1({  h,  h,  h, 1.0f }, {0, 1}, nR); // 8
    addV1({  h,  h, -h, 1.0f }, {1, 1}, nR); // 9
    addV1({  h, -h, -h, 1.0f }, {1, 0}, nR); // 10
    addV1({  h, -h,  h, 1.0f }, {0, 0}, nR); // 11

    // LEFT (X-), in mesh1
    glm::vec4 nL(-1.0f, 0.0f, 0.0f, 0.0f);
    addV1({ -h,  h,  h, 1.0f }, {1, 1}, nL); // 12
    addV1({ -h,  h, -h, 1.0f }, {0, 1}, nL); // 13
    addV1({ -h, -h, -h, 1.0f }, {0, 0}, nL); // 14
    addV1({ -h, -h,  h, 1.0f }, {1, 0}, nL); // 15

    // TOP (Y+), in mesh2
    glm::vec4 nT(0.0f, 1.0f, 0.0f, 0.0f);
    addV2({  h,  h,  h, 1.0f }, {1, 1}, nT); // 16
    addV2({ -h,  h,  h, 1.0f }, {0, 1}, nT); // 17
    addV2({ -h,  h, -h, 1.0f }, {0, 0}, nT); // 18
    addV2({  h,  h, -h, 1.0f }, {1, 0}, nT); // 19

    // BOTTOM (Y-), in mesh2
    glm::vec4 nBo(0.0f, -1.0f, 0.0f, 0.0f);
    addV2({  h, -h,  h, 1.0f }, {1, 0}, nBo); // 20
    addV2({ -h, -h,  h, 1.0f }, {0, 0}, nBo); // 21
    addV2({ -h, -h, -h, 1.0f }, {0, 1}, nBo); // 22
    addV2({  h, -h, -h, 1.0f }, {1, 1}, nBo); // 23

    // ---------- Indices for triangles (if your Mesh3D needs them) ----------
    // Front
    mesh1->addTriangle(0, 1, 2);  mesh1->addTriangle(0, 2, 3);
    // Back
    mesh1->addTriangle(4, 6, 5);  mesh1->addTriangle(4, 7, 6);
    // Right
    mesh1->addTriangle(8, 10, 9);  mesh1->addTriangle(8, 11, 10);
    // Left
    mesh1->addTriangle(12, 13, 14); mesh1->addTriangle(12, 14, 15);

    // Top (mesh2)
    mesh2->addTriangle(0, 1, 2); mesh2->addTriangle(0, 2, 3);
    // Bottom (mesh2)
    mesh2->addTriangle(4, 5, 6); mesh2->addTriangle(4, 6, 7);
	
	auto texture1 = FactoryEngine::getNewTexture();
	auto texture2 = FactoryEngine::getNewTexture();

	texture1->load("data/cubeTextures/top.png");
	texture2->load("data/cubeTextures/front.png");
	texture1->setup();
	texture2->setup();

	mesh1->getMaterial()->setColorTexture(texture1);
	mesh2->getMaterial()->setColorTexture(texture2);
	
	addMesh(mesh1);
	addMesh(mesh2);
}