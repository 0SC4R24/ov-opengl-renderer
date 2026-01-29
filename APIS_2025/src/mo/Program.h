///
/// MO-OpenGL-Renderer
/// Oscar Viudez
/// Miguel Gutierrez
/// 2026
/// 

#pragma once

#include "common.h"
#include "Shader.h"

namespace old
{
	class Program
	{
	private:
		std::vector<std::string> shaderList;
		unsigned int programID;
		std::map<std::string, unsigned int> varList;
		bool linked = false;
	public:
		Program() { this->programID = -1; }
		void addShader(std::string fileName) { this->shaderList.push_back(fileName); }
		void linkProgram();
		void readVarList();
		void activate() { glUseProgram(programID); }

		void setAttributeMetaData(std::string attribName, GLint size, GLenum type, 
			GLboolean normalized, GLsizei stride, const GLvoid* pointer);
		void setMVP(glm::mat4 m);
	};
};

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
		m_idProgram = -1;
	}

	virtual void readFile() = 0;
	virtual void compile() = 0;
	virtual void checkErrors() = 0;
	virtual void clean() = 0;
};