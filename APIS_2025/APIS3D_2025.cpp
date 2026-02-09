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
    System::setParameters("MO OpenGL Renderer v5.0", 640, 480);
    System::initSystem(MO_RENDER_ENGINE_TYPE_GL4, MO_INPUT_MANAGER_TYPE_GLFW);

    auto camera = std::make_shared<CameraKeyboard>(
        MO_PROJECTION_TYPE_PERSPECTIVE,       // tipo
        glm::vec3(0.6, 1, 0.9),         // posicion
        glm::vec3(0, 1, 0),             // up
        glm::vec3(-0.54, -0.93, -1)     // lookAt
    );
    
    System::getWorld()->addCamera(camera);

    auto center = glm::vec4(0);
    float radius = 10.0f;
    float speed = 2.0f;

    System::getWorld()->setAmbient(0.2f);
    
    auto light = std::make_shared<OrbitalLight>(
        MO_LIGHT_TYPE_POINT,
        glm::vec4(-10, 0, 0, 1),
        glm::vec4(1, 0, 0, 1),
        glm::vec4(0, -1, 0, 0),
        center,
        radius,
        speed,
        0.2f
    );
    
    auto light2 = std::make_shared<Light>(
        MO_LIGHT_TYPE_DIRECTIONAL,
        glm::vec4(0, 0, 0, 1),
        glm::vec4(1, 1, 1, 1),
        glm::vec4(0, 1, -1, 0)
    );
    
    System::getWorld()->addLight(light);
    System::getWorld()->addLight(light2);
    
    auto feng_shui = std::make_shared<Object3D>();
    feng_shui->loadDataFromMshFile("data/feng_shui/Feng_Shui.msh");
    feng_shui->setScale(glm::vec4(0.005f));
    
    System::addObject(feng_shui);
    
    System::mainLoop();

	return 0;
}