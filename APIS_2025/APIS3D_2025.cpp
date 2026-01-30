#define GLAD_BIN

#include "mapi/common.h"
#include "mo/System.h"
#include "mo/TrianguloRot.h"
#include "mapi/Camera.h"

int main(int argc, char** argv)
{
    System::initSystem(MO_RENDER_ENGINE_TYPE_GL4, MO_INPUT_MANAGER_TYPE_GLFW);

    old::Camera cam(glm::vec4(0, 0, 3, 1), glm::vec4(0, 0, 0, 1));
    System::getRender()->setCamera(&cam);

    auto triangulo = std::make_shared<TrianguloRot>();
    triangulo->getMesh()->setColor({ 0.5f,0,0,1 });

    System::addObject(triangulo);

    System::mainLoop();

	return 0;
}