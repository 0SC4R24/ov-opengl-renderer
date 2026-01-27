///
/// MO-OpenGL-Renderer
/// Oscar Viudez
/// Miguel Gutierrez
/// 2026
/// 

#pragma once

#include "RenderProgram.h"

class GLSLProgram : public RenderProgram
{
public: // Constructor
	GLSLProgram() : RenderProgram() {}

public: // Getters & Setters
	void setVertexAttrib(std::string name, GLsizei stride, void* offset, GLint count, GLenum type) override;
	void setInt(std::string name, int value) override;
	void setFloat(std::string name, float value) override;
	void setVec3(std::string name, const glm::vec3& vector3) override;
	void setVec4(std::string name, const glm::vec4& vector4) override;
	void setMatrix(std::string name, const glm::mat4& matrix) override;

public: // Virtual methods
	void addProgram(std::string fileName) override;
	void linkProgram() override;
	void use() override;
	void checkLinkerErrors() override;
};