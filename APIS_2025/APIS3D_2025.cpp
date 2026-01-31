#define GLAD_BIN

#include "mapi/common.h"
#include "mo/System.h"
#include "mo/TrianguloRot.h"

int main(int argc, char** argv)
{
    System::initSystem(MO_RENDER_ENGINE_TYPE_GL4, MO_INPUT_MANAGER_TYPE_GLFW);
    System::addObject(std::make_shared<TrianguloRot>());
    System::mainLoop();

	return 0;
}