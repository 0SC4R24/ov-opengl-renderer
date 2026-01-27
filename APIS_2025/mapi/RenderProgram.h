///
/// MO-OpenGL-Renderer
/// Oscar Viudez
/// Miguel Gutierrez
/// 2026
/// 

#pragma once

#include "common.h"
#include "Program.h"

/// <summary>
/// RenderProgram abstract class
/// </summary>
class RenderProgram
{
protected: // Attributes
	std::vector<Program*> m_shaders;
	std::map<std::string, unsigned int> m_varList;

public: // Getters & Setters
	virtual void setVertexAttrib(std::string name, GLsizei stride, void* offset, GLint count, GLenum type) = 0;
	virtual void setInt(std::string name, int value) = 0;
	virtual void setFloat(std::string name, float value) = 0;
	virtual void setVec3(std::string name, const glm::vec3& vector3) = 0;
	virtual void setVec4(std::string name, const glm::vec4& vector4) = 0;
	virtual void setMatrix(std::string name, const glm::mat4& matrix) = 0;

public: // Virtual methods
	virtual void addProgram(std::string fileName) = 0;
	virtual void linkProgram() = 0;
	virtual void use() = 0;
	virtual void checkLinkerErrors() = 0;
};