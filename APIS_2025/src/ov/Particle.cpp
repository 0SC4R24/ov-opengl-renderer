#include "Particle.h"

Particle::Particle(std::string mshFile, const glm::vec3& velocity, float spinVelocity, double lifeTime, bool autoFade)
    : Billboard(mshFile, spinVelocity)
{
    m_velocity = glm::vec4(velocity,0 );
    m_lifeTime = lifeTime;
    m_autoFade = autoFade;
}

float Particle::getRemainingLifetime() const
{
    return m_lifeTime;
}