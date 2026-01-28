#include "GLSLProgram.h"

void GLSLProgram::setVertexAttrib(std::string name, GLsizei stride, void* offset, GLint count, GLenum type)
{
	if (m_varList.find(name) != m_varList.end()) 
	{
		unsigned int location = m_varList[name];
		glEnableVertexAttribArray(location);
		glVertexAttribPointer(location, count, type, GL_FALSE, stride, offset);
	}
	else 
	{
		std::cout << "[ERROR] " << name << " not found in shader\n" << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << "\n";
	}
}

void GLSLProgram::setInt(std::string name, int value)
{
	if (m_varList.find(name) != m_varList.end())
	{
		glUniform1i(m_varList[name], value);
	}
	else
	{
		std::cout << "[ERROR] " << name << " not found in shader\n" << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << "\n";
	}
}

void GLSLProgram::setFloat(std::string name, float value)
{
	if (m_varList.find(name) != m_varList.end())
	{
		glUniform1f(m_varList[name], value);
	}
	else
	{
		std::cout << "[ERROR] " << name << " not found in shader\n" << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << "\n";
	}
}

void GLSLProgram::setVec3(std::string name, const glm::vec3& vector3)
{
	if (m_varList.find(name) != m_varList.end())
	{
		glUniform3f(m_varList[name], vector3.x, vector3.y, vector3.z);
	}
	else
	{
		std::cout << "[ERROR] " << name << " not found in shader\n" << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << "\n";
	}
}

void GLSLProgram::setVec4(std::string name, const glm::vec4& vector4)
{
	if (m_varList.find(name) != m_varList.end())
	{
		glUniform4f(m_varList[name], vector4.x, vector4.y, vector4.z, vector4.w);
	}
	else
	{
		std::cout << "[ERROR] " << name << " not found in shader\n" << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << "\n";
	}
}

void GLSLProgram::setMatrix(std::string name, const glm::mat4& matrix)
{
	if (m_varList.find(name) != m_varList.end()) 
	{
		glUniformMatrix4fv(m_varList[name], 1, GL_FALSE, &matrix[0][0]);
	}
	else 
	{
		std::cout << "[ERROR] " << name << " not found in shader\n" << __FILE__ << ":" << __LINE__ << " " << __FUNCTION__ << "\n";
	}
}

unsigned int GLSLProgram::getVarLocation(std::string varName)
{
	if (m_varList.find(varName) != m_varList.end())
	{
		return m_varList[varName];
	}
	else
	{
		std::cerr << "[ERROR] Variable " << varName << " not found in shader\n";
		return -1;
	}
}

void GLSLProgram::readVarList()
{
	int numAttributes = 0;
	int numUniforms = 0;

	glGetProgramiv(m_idRenderProgram, GL_ACTIVE_ATTRIBUTES, &numAttributes);
	for (int i = 0; i < numAttributes; i++)
	{
		char varName[100];
		int bufSize = 100, length = 0, size = 0;
		GLenum type = -1;
		glGetActiveAttrib(m_idRenderProgram, (GLuint)i, bufSize, &length, &size, &type, varName);
		m_varList[std::string(varName)] = glGetAttribLocation(m_idRenderProgram, varName);
	}

	glGetProgramiv(m_idRenderProgram, GL_ACTIVE_UNIFORMS, &numUniforms);
	for (int i = 0; i < numUniforms; i++)
	{
		char varName[100];
		int bufSize = 100, length = 0, size = 0;
		GLenum type = -1;
		glGetActiveUniform(m_idRenderProgram, (GLuint)i, bufSize, &length, &size, &type, varName);
		m_varList[std::string(varName)] = glGetUniformLocation(m_idRenderProgram, varName);
	}
}

void GLSLProgram::addProgram(std::string fileName)
{
	m_shaders.push_back(new GLSLShader(fileName));
}

void GLSLProgram::linkProgram()
{
	m_idRenderProgram = glCreateProgram();

	for (auto& s : m_shaders)
	{
		glAttachShader(m_idRenderProgram, s->getProgramID());
	}

	glLinkProgram(m_idRenderProgram);
	checkLinkerErrors();
	readVarList();
}

void GLSLProgram::use()
{
	glUseProgram(m_idRenderProgram);
}

void GLSLProgram::checkLinkerErrors()
{
	GLint program_linked;
	glGetProgramiv(m_idRenderProgram, GL_LINK_STATUS, &program_linked);

	if (program_linked != GL_TRUE) 
	{
		GLsizei log_length = 0;
		GLchar message[1024];
		glGetProgramInfoLog(m_idRenderProgram, 1024, &log_length, message);
		std::cout << "[ERROR] " << message << "\n\n";
	}
}

void GLSLProgram::clean()
{
	for (auto& s : m_shaders)
	{
		s->clean();
	}
}