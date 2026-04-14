///
/// OV-OpenGL-Renderer
/// Oscar Viudez
/// Miguel Gutierrez
/// 2026
/// 

#pragma once

#include "common.h"
#include "Object.h"

/// <summary>
/// Billboard Interface
/// </summary>
class Billboard : Object
{
protected: // Attributes
    float m_spin;
    
public: // Constructor
    Billboard();
    
public: // Getters & Setters
    float getSpin() const
    { return m_spin; }
    
    void setSpin(float spin)
    { m_spin = spin; }
    
public: // Virtual Methods
    virtual void computeModelMatrix() override;
    virtual void step(double deltaTime) = 0;
};