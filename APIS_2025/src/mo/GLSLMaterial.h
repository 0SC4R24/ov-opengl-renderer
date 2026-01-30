///
/// MO-OpenGL-Renderer
/// Oscar Viudez
/// Miguel Gutierrez
/// 2026
/// 

#pragma once

#include "Material.h"
#include "GLSLProgram.h"

class GLSLMaterial : public Material
{
public: // Constructor
	GLSLMaterial() { m_program = new GLSLProgram(); }

public: // Virtual methods
	void loadPrograms(std::vector<std::string> shaderFileNames) override;
	void prepare() override;
};