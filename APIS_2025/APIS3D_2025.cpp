#define GLAD_BIN

#include "mapi/common.h"
#include "ov/System.h"
#include "ov/World.h"
#include "ov/CameraKeyboard.h"
#include "ov/CameraFPS.h"
#include "ov/TrianguloRot.h"
#include "ov/CubeTex.h"
#include "ov/OrbitalLight.h"

int main(int argc, char** argv)
{
    System::setParameters("OV OpenGL Renderer v5.0", 640, 480);
    System::initSystem(OV_RENDER_ENGINE_TYPE_GL4, OV_INPUT_MANAGER_TYPE_GLFW);

    auto camera = std::make_shared<CameraFPS>(
        OV_PROJECTION_TYPE_PERSPECTIVE,        // tipo
        glm::vec3(0.6f, 1.0f, 0.9f),     // posicion
        glm::vec3(0, 1, 0),              // up
        glm::vec3(-0.54f, -0.93f, -1.0f) // lookAt
    );
    
    System::getWorld()->addCamera(camera);

    // auto cube = std::make_shared<CubeTex>();
    auto center = glm::vec4(0);
    float radius = 10.0f;
    float speed = 2.0f;

    System::getWorld()->setAmbient(0.2f);
    
    auto light = std::make_shared<OrbitalLight>(
        OV_LIGHT_TYPE_POINT,
        glm::vec4(-10, 0, 0, 1),
        glm::vec4(1, 0, 0, 1),
        glm::vec4(0, -1, 0, 0),
        center,
        radius,
        speed,
        0.2f
    );
    
    auto light2 = std::make_shared<Light>(
        OV_LIGHT_TYPE_DIRECTIONAL,
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
    // System::addObject(cube);
    
    System::mainLoop();

	return 0;
}