///
/// OV-OpenGL-Renderer
/// Oscar Viudez
/// Miguel Gutierrez
/// 2026
/// 

#pragma once

#include "Particle.h"

using ParticlePtr = std::shared_ptr<Particle>;

class Emitter : public Entity
{
protected: // Attributes
    std::string m_mshFile;
    
    float m_emissionRateMin;
    float m_emissionRateMax;
    bool m_autoFade;
    
    glm::vec3 m_velocityMin;
    glm::vec3 m_velocityMax;
    float m_spinVelocityMin;
    float m_spinVelocityMax;
    float m_particleScaleMin;
    float m_particleScaleMax;
    float m_lifetimeMin;
    float m_lifetimeMax;
    glm::vec4 m_colorMin;
    glm::vec4 m_colorMax;
    
    bool m_emit;
    
    std::list<ParticlePtr> m_particleList;
    
public: // Constructor
    Emitter(const std::string& mshFile, float emissionRate, glm::vec4 position, bool autoFade);
    
public: // Getters & Setters
    void setRateRange(float min, float max)
    { m_emissionRateMin = min; m_emissionRateMax = max; }
    
    void setVelocityRange(const glm::vec3& min, const glm::vec3& max)
    { m_velocityMin = min; m_velocityMax = max; }
    
    void setSpinVelocityRange(float min, float max)
    { m_spinVelocityMin = min; m_spinVelocityMin = max; }
    
    void setScaleRange(float min, float max)
    { m_particleScaleMin = min; m_particleScaleMax = max; }
    
    void setLifetimeRange(float min, float max)
    { m_lifetimeMin = min; m_lifetimeMax = max; }
    
    void setColorRange(const glm::vec4& min, const glm::vec4& max)
    { m_colorMin = min; m_colorMax = max; }
    
    bool isEmitting() const
    { return m_emit; }
    
    std::list<ParticlePtr>& getParticleList()
    { return m_particleList; }
    
    float getEmissionRate() const
    { return glm::linearRand(m_emissionRateMin, m_emissionRateMax); }
    
    glm::vec3 getVelocity() const
    {
        return {
            glm::linearRand(m_velocityMin.x, m_velocityMax.x),
            glm::linearRand(m_velocityMin.y, m_velocityMax.y),
            glm::linearRand(m_velocityMin.z, m_velocityMax.z),
        };
    }
    
    float getSpinVelocity() const
    { return glm::linearRand(m_spinVelocityMin, m_spinVelocityMax); }
    
    float getParticleScale() const
    { return glm::linearRand(m_particleScaleMin, m_particleScaleMax); }
    
    float getLifetime() const
    { return glm::linearRand(m_lifetimeMin, m_lifetimeMax); }
    
    glm::vec4 getColor() const
    {
        return {
            glm::linearRand(m_colorMin.x, m_colorMax.x),
            glm::linearRand(m_colorMin.y, m_colorMax.y),
            glm::linearRand(m_colorMin.z, m_colorMax.z),
            glm::linearRand(m_colorMin.w, m_colorMax.w),
        };
    }
    
public: // Public Methods
    void emit(bool enable)
    { m_emit = enable; }
    
public: // Virtual methods
    virtual void step(double deltaTime) override;
};