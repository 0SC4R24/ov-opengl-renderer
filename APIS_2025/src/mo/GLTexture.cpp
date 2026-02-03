#include "GLTexture.h"

GLTexture::GLTexture() : Texture()
{
	glGenTextures(1, &m_glTextID);
}

GLTexture::GLTexture(std::string fileName) : Texture(fileName)
{
	glGenTextures(1, &m_glTextID);
}

void GLTexture::update()
{
	glBindTexture(GL_TEXTURE_2D, m_glTextID);

	if (m_bilinear)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}

	if (m_repeat)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_texBytes.data());

	glGenerateMipmap(GL_TEXTURE_2D);
}