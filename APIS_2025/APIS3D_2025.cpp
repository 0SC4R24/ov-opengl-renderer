#define GLAD_BIN

#include "mapi/common.h"
#include "mapi/GLFWKeyManager.h"
#include "mo/Object.h"
#include "mo/Object3D.h"
#include "mo/GLSLMaterial.h"
#include "mapi/Camera.h"
#include "mapi/vertex.h"

#include "mo/GL4Render.h"
#include "mo/GLFWInputManager.h"
#include "mo/System.h"

int main(int argc, char** argv)
{
    GL4Render render{ 640, 480 };

    auto window = render.getWindow();

	GLFWInputManager inputManager(window);

    float newTime = static_cast<float>(glfwGetTime());
    float deltaTime = 0;
    float lastTime = newTime;

    old::Camera cam(glm::vec4(0, 0, 3, 1), glm::vec4(0, 0, 0, 1));
	render.setCamera(&cam);

    cam.cameraView = glm::lookAt(glm::vec3(cam.position), glm::vec3(cam.lookAt), glm::vec3(0, 1, 0));
    
    std::list<std::shared_ptr<Object>> objectPtrList;
    std::vector<std::string> shaders = { "data/shader.vert", "data/shader.frag" };

    auto ground = std::make_shared<Object3D>();
    glm::vec4 groundRot = glm::vec4(90.0f, 0.0f, 0.0f, 0.0f);
    ground->setRotation(groundRot);
    glm::vec4 groundScale = glm::vec4(1000);
    ground->setScale(groundScale);
    glm::vec4 groundPosition = glm::vec4(0.0f, -1.5f, 0.0f, 0.0f);
    ground->setPosition(groundPosition);
    ground->getMesh()->setColor({ 0,0.5f,0,1 });
    ground->getMesh()->setMaterial(new GLSLMaterial());
    ground->getMesh()->getMaterial()->loadPrograms(shaders);

    auto square = std::make_shared<Object3D>();
    square->getMesh()->setColor({ 0.5f,0,0,1 });
    square->getMesh()->setMaterial(new GLSLMaterial());
    square->getMesh()->getMaterial()->loadPrograms(shaders);

    objectPtrList.push_back(ground);
    objectPtrList.push_back(square);

    for (auto& obj : objectPtrList)
    {
        render.setupObject(obj);
    }
    
    while (!glfwWindowShouldClose(window) && !InputManager::isKeyPressed(GLFW_KEY_ESCAPE))
    {
        newTime = static_cast<float>(glfwGetTime());
        deltaTime = newTime - lastTime;
        lastTime = newTime;

		cam.step(deltaTime);
        render.drawObjects(objectPtrList);

		inputManager.updateEvents();
    }

    glfwTerminate();

	return 0;
}