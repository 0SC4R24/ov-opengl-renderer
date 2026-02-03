#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture()
{
	m_textID = m_TextureIDCounter++;
}

Texture::Texture(std::string fileName) : Texture()
{
	m_fileName = fileName;
	load(fileName);
}

void Texture::load(std::string fileName)
{
	int comp = 0;
	unsigned char* data = stbi_load(fileName.c_str(), &m_width, &m_height, &comp, 4);

	if (!data)
	{
		std::cerr << "[ERROR] File " << fileName << " not found\n";
		return;
	}

	m_texBytes.resize(m_width * m_height);
	memcpy(m_texBytes.data(), data, m_width * m_height * 4);

	stbi_image_free(data);
}
