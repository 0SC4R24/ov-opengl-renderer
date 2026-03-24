///
/// OV-OpenGL-Renderer
/// Oscar Viudez
/// Miguel Gutierrez
/// 2026
/// 

#pragma once

#include "Entity.h"

/// <summary>
/// Light class
/// </summary>
class Light : public Entity
{
protected: // Attributes
    OV_LightType_e m_type = OV_LIGHT_TYPE_POINT;
    glm::vec4 m_color;
    glm::vec4 m_direction;
    float m_linearAttenuation = 1.0f;
    bool m_enabled = true;
    
public: // Getters & Setters
    const OV_LightType_e& getType() const
    { return m_type; }
    
    void setType(const OV_LightType_e type)
    { m_type = type; }
    
    const glm::vec4& getColor() const
    { return m_color; }

    void setColor(const glm::vec4 color)
    { m_color = color; }

    const glm::vec4& getDirection() const
    { return m_direction; }

    void setDirection(const glm::vec4 direction)
    { m_direction = direction; }

    float getLinearAttenuation() const
    { return m_linearAttenuation; }

    void setLinearAttenuation(const float linearAttenuation)
    { m_linearAttenuation = linearAttenuation; }

    bool isEnabled() const
    { return m_enabled; }

    void setEnabled(const bool enabled)
    { m_enabled = enabled; }
    
public: // Constructor
    Light(OV_LightType_e type, glm::vec4 position, glm::vec4 color, glm::vec4 direction, 
        float linearAttenuation = 1.0f, bool enabled = true);
    
public: // Virtual methods
    virtual void step(double deltaTime);
};