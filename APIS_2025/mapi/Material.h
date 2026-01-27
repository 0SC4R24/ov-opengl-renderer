///
/// MO-OpenGL-Renderer
/// Oscar Viudez
/// Miguel Gutierrez
/// 2026
/// 

#pragma once

#include "RenderProgram.h"

/// <summary>
/// Material abstract class
/// </summary>
class Material
{
protected: // Attributes
	RenderProgram* m_program = nullptr;

public: // Virtual methods
	virtual void loadPrograms(std::vector<std::string> shaderFileNames) = 0;
	virtual void prepare() = 0;
};
