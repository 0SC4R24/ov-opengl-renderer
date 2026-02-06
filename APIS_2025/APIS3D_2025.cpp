#define GLAD_BIN

#include "mapi/common.h"
#include "mo/System.h"
#include "mo/World.h"
#include "mo/CameraKeyboard.h"
#include "mo/TrianguloRot.h"
#include "mo/CubeTex.h"
#include "mo/OrbitalLight.h"

int main(int argc, char** argv)
{
    System::initSystem(MO_RENDER_ENGINE_TYPE_GL4, MO_INPUT_MANAGER_TYPE_GLFW);

    auto camera = std::make_shared<CameraKeyboard>(
        MO_PROJECTION_TYPE_PERSPECTIVE, // tipo
        glm::vec3(1, 1, 3),       // posicion
        glm::vec3(0, 1, 0),       // up
        glm::vec3(0, 0, 0)        // lookAt
    );
    
    System::getWorld()->addCamera(camera);

    auto light = std::make_shared<Light>(
        MO_LIGHT_TYPE_POINT,
        glm::vec4(-2, 2, 0, 1),
        glm::vec4(1, 0, 0, 1),
        glm::vec4(0, -1, 0, 0)
    );
    
    auto light2 = std::make_shared<Light>(
        MO_LIGHT_TYPE_POINT,
        glm::vec4(2, 2, 0, 1),
        glm::vec4(0, 1, 0, 1),
        glm::vec4(0, -1, 0, 0)
    );
    
    System::getWorld()->addLight(light);
    System::getWorld()->addLight(light2);
    
    auto cube = std::make_shared<CubeTex>();

    auto asianTown = std::make_shared<Object3D>();
    asianTown->loadDataFromMshFile("data/asian_town.msh");
    asianTown->setScale(glm::vec4(100));
    
    // System::addObject(cube);
    System::addObject(asianTown);
    
    System::mainLoop();

	return 0;
}