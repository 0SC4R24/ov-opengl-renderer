///
/// MO-OpenGL-Renderer
/// Oscar Viudez
/// Miguel Gutierrez
/// 2026
/// 

#pragma once

#include "Texture.h"

class GLTexture : public Texture
{
private: // Attributes
	GLuint m_glTextID;

public: // Getters & Setters
	GLuint getGLTextureID()
	{ return m_glTextID; }

	void setGLTextureID(GLuint glTextID)
	{ m_glTextID = glTextID; }

public: // Constructor
	GLTexture();
	GLTexture(std::string fileName);

public: // Virtual methods
	virtual void update() override;
};