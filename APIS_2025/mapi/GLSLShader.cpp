#include "GLSLShader.h"

void GLSLShader::readFile()
{
	std::ifstream f(m_fileName);

	if (!f.is_open())
	{
		std::cerr << "[ERROR] File Not Found " << __FILE__ << ":" << __LINE__ << " " << m_fileName << "\n";
		return;
	}

	m_sourceCode = std::string(std::istreambuf_iterator<char>(f), {});
	f.close();
}

void GLSLShader::compile()
{
	unsigned int glType;
	if (m_type = MO_PROGRAM_TYPE_VERTEX) glType = GL_VERTEX_SHADER;
	else if (m_type = MO_PROGRAM_TYPE_FRAGMENT) glType = GL_FRAGMENT_SHADER;

	m_idProgram = glCreateShader(glType);
	const char* source = m_sourceCode.c_str();
	glShaderSource(m_idProgram, 1, &source, nullptr);
	glCompileShader(m_idProgram);
}

void GLSLShader::checkErrors()
{
	GLint fragment_compiled;
	glGetShaderiv(m_idProgram, GL_COMPILE_STATUS, &fragment_compiled);

	if (fragment_compiled != GL_TRUE)
	{
		GLsizei log_length = 0;
		GLchar message[1024];
		glGetShaderInfoLog(m_idProgram, 1024, &log_length, message);
		std::cerr << "[ERROR] " << m_fileName << "\n" << message << "\n\n";
	}
}
