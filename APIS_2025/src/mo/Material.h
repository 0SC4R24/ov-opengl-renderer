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

/// <summary>
/// Material abstract class
/// </summary>
class Material
{
protected: // Attributes
	RenderProgram* m_program = nullptr;
	std::shared_ptr<Texture> m_colorTexture = nullptr;

	glm::vec4 m_colorRGBA;

public: // Getters & Setters
	RenderProgram* getRenderProgram()
	{ return m_program; }

	std::shared_ptr<Texture> getColorTexture()
	{ return m_colorTexture; }

	const glm::vec4& getColor()
	{ return m_colorRGBA; }

	void setColorTexture(std::shared_ptr<Texture> colorTexture)
	{ m_colorTexture = colorTexture; }

	void setColor(glm::vec4 color)
	{ m_colorRGBA = color; }

	void setRenderProgram(RenderProgram* program)
	{ m_program = program; }

public: // Virtual methods
	virtual void loadPrograms(std::vector<std::string> shaderFileNames) = 0;
	virtual void prepare() = 0;
};
