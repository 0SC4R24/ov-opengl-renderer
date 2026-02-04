///
/// MO-OpenGL-Renderer
/// Oscar Viudez
/// Miguel Gutierrez
/// 2026
/// 

#pragma once

#include "common.h"

/// <summary>
/// Program Type Enumerator
/// </summary>
typedef enum
{
	MO_PROGRAM_TYPE_VERTEX,
	MO_PROGRAM_TYPE_FRAGMENT
} MO_ProgramType_e;

/// <summary>
/// Program abstract class
/// </summary>
class Program
{
protected: // Attributes
	MO_ProgramType_e m_type = MO_PROGRAM_TYPE_VERTEX; // Inicialización por defecto
	std::string m_fileName;
	std::string m_sourceCode;
	unsigned int m_idProgram;

	void initialize()
	{
		readFile();
		compile();
		checkErrors();
	}

public: // Getters & Setters
	const unsigned int& getProgramID()
	{ return m_idProgram; }

public: // Methods
	Program(std::string fileName) : m_fileName(fileName) 
	{
		if (fileName.ends_with(".vert")) m_type = MO_PROGRAM_TYPE_VERTEX;
		else if (fileName.ends_with(".frag")) m_type = MO_PROGRAM_TYPE_FRAGMENT;
		else std::cerr << "[ERROR] Shader type not supported\n";
		m_idProgram = -1;
	}

	virtual void readFile() = 0;
	virtual void compile() = 0;
	virtual void checkErrors() = 0;
	virtual void clean() = 0;
};