#include "OrbitalLight.h"

#include "System.h"

OrbitalLight::OrbitalLight(OV_LightType_e type, glm::vec4 position, glm::vec4 color, glm::vec4 direction,
    glm::vec4 center, float radius, float speed, float linearAttenuation, bool enabled)
        : Light(type, position, color, direction, linearAttenuation, enabled), m_center(center),
        m_radius(radius), m_speed(speed)
{
}

void OrbitalLight::step(double deltaTime)
{
    if (System::getInputManager()->isKeyPressed(GLFW_KEY_L)) m_enabled = !m_enabled;
    
    if (!m_enabled) return;
    
    const float angle = std::atan2(m_position.z - m_center.z, m_position.x - m_center.x);
    const float newAngle = angle + static_cast<float>(m_speed * deltaTime);
     
    m_position.x = m_center.x + m_radius * std::cos(newAngle);
    m_position.z = m_center.z + m_radius * std::sin(newAngle);
}