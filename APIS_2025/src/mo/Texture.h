///
/// MO-OpenGL-Renderer
/// Oscar Viudez
/// Miguel Gutierrez
/// 2026
/// 

#pragma once

#include "common.h"

/// <summary>
/// Texture Interface
/// </summary>
class Texture
{
private: // Static counter
	static inline int m_TextureIDCounter = 0;

protected: // Attributes
	std::uint32_t m_textID;
	glm::ivec2 m_size;
	bool m_cubemap = false;
	std::vector<unsigned char> m_texBytes;
	std::string m_fileName;
	bool m_bilinear = false;
	bool m_repeat = true;

	int m_width;
	int m_height;

public: // Getters & Setters
	std::uint32_t getTextID()
	{ return m_textID; }

	glm::ivec2 getSize()
	{ return m_size; }

	bool isCubemap()
	{ return m_cubemap; }

	std::vector<unsigned char>& getTexBytes()
	{ return m_texBytes; }

	std::string getFileName()
	{ return m_fileName; }

	bool isBilinear()
	{ return m_bilinear; }

	bool isRepeat()
	{ return m_repeat; }
	
	int getWidth()
	{ return m_width; }
	
	int getHeight()
	{ return m_height; }

	void setTextID(std::uint32_t textID)
	{ m_textID = textID; }

	void setSize(glm::ivec2 size)
	{ m_size = size; }

	void setIsCubemap(bool cubemap)
	{ m_cubemap = cubemap; }

	void setTexBytes(std::vector<unsigned char> texBytes)
	{ m_texBytes = texBytes; }

	void setFileName(std::string fileName)
	{ m_fileName = fileName; }

	void setIsBilinear(bool bilinear)
	{ m_bilinear = bilinear; }

	void setIsRepeat(bool repeat)
	{ m_repeat = repeat; }

	void setWidth(int width)
	{ m_width = width; }

	void setHeight(int height)
	{ m_height = height; }

public: // Constructor
	Texture();
	Texture(std::string fileName);

public: // Methods
	void load(std::string fileName);

public: // Virtual methods
	virtual void update() = 0;

};