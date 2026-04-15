///
/// OV-OpenGL-Renderer
/// Oscar Viudez
/// Miguel Gutierrez
/// 2026
/// 

#pragma once

#include "Billboard.h"

class Particle : public Billboard
{
private: // Attributes
    glm::vec4 m_velocity;
    double m_lifeTime;
    bool m_autoFade;
    
public: // Constructor
    Particle(std::string mshFile, const glm::vec3& velocity, float spinVelocity, double lifeTime, bool autoFade);
    
public: // Methods
    float getRemainingLifetime() const;
    
public: // Virtual Methods
    virtual void step(double deltaTime) override;
};