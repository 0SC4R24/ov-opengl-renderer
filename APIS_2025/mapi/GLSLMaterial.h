///
/// MO-OpenGL-Renderer
/// Oscar Viudez
/// Miguel Gutierrez
/// 2026
/// 

#pragma once

#include "Material.h"

class GLSLMaterial : Material
{
public: // Virtual methods
	void loadPrograms(std::vector<std::string> shaderFileNames) override;
	void prepare() override;
};