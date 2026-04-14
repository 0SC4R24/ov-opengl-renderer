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
    Billboard(std::string fileName, float spin);
    
public: // Getters & Setters
    float getSpin() const
    { return m_spin; }
    
    void setSpin(float spin)
    { m_spin = spin; }
    
public: // Methods
    void loadDataFromObjFile(std::string file, MaterialPtr material);
    void recomputeNormals();
    
public: // Virtual Methods
    void loadDataFromMshFile(std::string file) override;
    void computeModelMatrix() override;
    virtual void step(double deltaTime) = 0;
};