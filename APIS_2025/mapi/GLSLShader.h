///
/// MO-OpenGL-Renderer
/// Oscar Viudez
/// Miguel Gutierrez
/// 2026
/// 

#pragma once

#include "common.h"
#include "Program.h"

class GLSLShader : public Program
{
public:
	GLSLShader(std::string fileName) : Program(fileName) { initialize(); }

	void readFile() override;
	void compile() override;
	void checkErrors() override;
	void clean() override;
};