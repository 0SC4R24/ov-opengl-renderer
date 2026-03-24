///
/// OV-OpenGL-Renderer
/// Oscar Viudez
/// Miguel Gutierrez
/// 2026
/// 

#pragma once

#include "Light.h"

class OrbitalLight : public Light
{
private: // Attributes
    glm::vec4 m_center;
    float m_radius;
    float m_speed;
    
public: // Getters & Setters
    const glm::vec4& getCenter() const
    { return m_center; }

    void setCenter(const glm::vec4 center)
    { m_center = center; }

    float getRadius() const
    { return m_radius; }

    void setRadius(const float radius)
    { m_radius = radius; }

    float getSpeed() const
    { return m_speed; }

    void setSpeed(const float speed)
    { m_speed = speed; }
    
public: // Constructor
    OrbitalLight(OV_LightType_e type, glm::vec4 position, glm::vec4 color, glm::vec4 direction, 
        glm::vec4 center, float radius, float speed, float linearAttenuation = 1.0f, bool enabled = true);

public: // Virtual methods
    void step(double deltaTime) override;
    
};