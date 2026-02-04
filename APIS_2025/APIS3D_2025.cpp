#define GLAD_BIN

#include "mapi/common.h"
#include "mo/System.h"
#include "mo/World.h"
#include "mo/CameraKeyboard.h"
#include "mo/TrianguloRot.h"
#include "mo/CubeTex.h"

int main(int argc, char** argv)
{
    System::initSystem(MO_RENDER_ENGINE_TYPE_GL4, MO_INPUT_MANAGER_TYPE_GLFW);

    auto camera = std::make_shared<CameraKeyboard>(
        MO_PROJECTION_TYPE_PERSPECTIVE, // tipo
        glm::vec3(1, 1, 3),             // posición
        glm::vec3(0, 1, 0),             // up
        glm::vec3(0, 0, 0)              // lookAt
    );
    
    System::getWorld()->addCamera(camera);

    auto cube = std::make_shared<CubeTex>();
    //auto triangle = std::make_shared<TrianguloRot>();

    //auto newPos = glm::vec4(1, 0, 0, 1);
    //triangle->setPosition(newPos);

    System::addObject(cube);
    //System::addObject(triangle);

    System::mainLoop();

	return 0;
}