#include "TrianguloRot.h"

#include "System.h"

TrianguloRot::TrianguloRot() : Object3D()
{
    auto mesh = std::make_shared<Mesh3D>();
	mesh->addVertex({
		glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f),
		glm::vec4(0.5f, 0.0f, 0.0f, 1.0f)
	});
	mesh->addVertex({
		glm::vec4(0.5f, -0.5f, 0.0f, 1.0f),
		glm::vec4(0.0f, 0.5f, 0.0f, 1.0f)
	});
	mesh->addVertex({
		glm::vec4(0.0f, 0.5f, 0.0f, 1.0f),
		glm::vec4(0.0f, 0.0f, 0.5f, 1.0f)
	});

	mesh->addTriangle(0, 1, 2);

	mesh->setMaterial(FactoryEngine::getNewMaterial());
	mesh->getMaterial()->loadPrograms({ "data/shader.vert", "data/shader.frag" });

    m_meshes.push_back(mesh);
}

void TrianguloRot::step(double deltaTime)
{
    m_rotation.y += 90.0 * deltaTime;
    auto inputManager = System::getInputManager();
    if (inputManager->isKeyPressed(GLFW_KEY_E)) System::exit();
}