#include "Emitter.h"

Emitter::Emitter(const std::string& mshFile, float emissionRate, glm::vec4 position, bool autoFade)
{
    m_mshFile = mshFile;
    m_emissionRateMin = emissionRate; m_emissionRateMax = emissionRate;
    m_position = position;
    m_autoFade = autoFade;
}

void Emitter::step(double deltaTime)
{
    if (!m_emit) return;
    
    // Calculate number of particles to emit
    
    // Iterate through the number of particles to emit
        // Add particles to the particleList
    
    // Sort the particles based on their distance to the camera
}