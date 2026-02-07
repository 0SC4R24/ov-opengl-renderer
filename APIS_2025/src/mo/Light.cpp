#include "Light.h"

Light::Light(MO_LightType_e type, glm::vec4 position, glm::vec4 color, glm::vec4 direction, float linearAttenuation,
    bool enabled) : m_type(type), m_color(color), m_direction(direction), m_linearAttenuation(linearAttenuation),
    m_enabled(enabled)
{
    m_position = position;
}
