#include "TrianguloRot.h"

#include "System.h"

void TrianguloRot::step(double deltaTime)
{
    m_rotation.y += 90.0 * deltaTime;
    if (System::getInputManager()->isKeyPressed(GLFW_KEY_E)) System::exit();
}