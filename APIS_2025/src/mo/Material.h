///
/// MO-OpenGL-Renderer
/// Oscar Viudez
/// Miguel Gutierrez
/// 2026
/// 

#pragma once

#include "RenderProgram.h"
#include "Texture.h"
#include <memory>

using RenderProgramPtr = std::shared_ptr<RenderProgram>;
using TexturePtr = std::shared_ptr<Texture>;

/// <summary>
/// Material abstract class
/// </summary>
class Material
{
protected: // Attributes
	RenderProgramPtr m_program = nullptr;
	TexturePtr m_colorTexture = nullptr;

	glm::vec4 m_colorRGBA;

public: // Getters & Setters
	RenderProgramPtr getRenderProgram()
	{ return m_program; }

	TexturePtr getColorTexture()
	{ return m_colorTexture; }

	const glm::vec4& getColor()
	{ return m_colorRGBA; }

	void setColorTexture(TexturePtr colorTexture)
	{ m_colorTexture = colorTexture; }

	void setColor(glm::vec4 color)
	{ m_colorRGBA = color; }

	void setRenderProgram(RenderProgramPtr program)
	{ m_program = program; }

public: // Virtual methods
	virtual void loadPrograms(std::vector<std::string> shaderFileNames) = 0;
	virtual void prepare() = 0;
};
